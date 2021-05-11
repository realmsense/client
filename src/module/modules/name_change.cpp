#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "name_change.h"
#include "imgui/imgui.h" // for colors

NameChangeModule::NameChangeModule()
    : Module()
{
    this->name = "Name Change";
    this->enabled = false;
    this->type = ModuleList::NameChange;
    this->category = ModuleCategory::OTHER;
    this->hasGuiElements = true;

    this->charInfoObj = 0;
    this->input_focused = false;

    this->customPlayerName = "";
    this->originalPlayerName = "\0";

    this->customGuildName = "";
    this->originalGuildName = "\0";

    Color white{ 1.0f, 1.0f, 1.0f, 1.0f };
    this->rainbowName = false;
    this->customNameColor = white;

    this->ready();
}

void NameChangeModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void NameChangeModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;

    // Reset to original names / color
    if (this->originalPlayerName != "\0")
        this->ChangePlayerName(this->originalPlayerName.c_str());

    if (this->originalGuildName != "\0")
        this->ChangeGuildName(this->originalGuildName.c_str());

    this->rainbowName = false;
    Color white{ 1.0f, 1.0f, 1.0f, 1.0f };
    this->ChangeNameColor(white);
}

void NameChangeModule::renderGUI()
{
    bool input_focused = false;

    static char customPlayerName[128] = "";
    if (ImGui::InputText("Custom Player Name", customPlayerName, IM_ARRAYSIZE(customPlayerName)))
        this->ChangePlayerName(customPlayerName);
    if (ImGui::IsItemFocused()) input_focused = true;

    if (ImGui::Checkbox("Rainbow Name", &this->rainbowName))
        this->ToggleRainbowName(this->rainbowName);

    static char customGuildName[128] = "";
    if (ImGui::InputText("Custom Guild Name", customGuildName, IM_ARRAYSIZE(customGuildName)))
        this->ChangeGuildName(customGuildName);
    if (ImGui::IsItemFocused()) input_focused = true;

    this->input_focused = input_focused;
}

bool NameChangeModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    case ModuleEvent::GetKeyDown:
        return this->onGetKeyDown();
    case ModuleEvent::MapChange:
        return this->onMapChange();
    case ModuleEvent::TMP_SetText:
        return this->onTMPSetText(dp);
    default:
        return true;
    }
}

bool NameChangeModule::onMainLoop()
{
    this->enabled =
        this->rainbowName
        || strlen(this->customPlayerName) != 0
        || strlen(this->customGuildName) != 0;

    if (this->rainbowName)
    {
        static float hue = 1.0f;
        static float speed = 0.0035f;
        hue += speed;
        if (hue > 360.0f) hue = 1.0f;
        ImVec4 rainbow = (ImVec4)(ImColor)ImColor::HSV(hue, 1.0f, 1.0f);

        this->customNameColor = { rainbow.x, rainbow.y, rainbow.z, 1.0f };
        this->ChangeNameColor(this->customNameColor);
    }

    return true;
}

bool NameChangeModule::onGetKeyDown()
{
    return !this->input_focused; // block inputs if input focused
}

bool NameChangeModule::onMapChange()
{
    if (strlen(this->customPlayerName))
        this->ChangePlayerName(this->customPlayerName);

    if (strlen(this->customGuildName))
        this->ChangeGuildName(this->customGuildName);

    this->ChangeNameColor(this->customNameColor);
    return true;
}

bool NameChangeModule::onTMPSetText(CDataPack* dp)
{
    dp->Reset();
    size_t txtLen = dp->ReadCell();
    const char* txt2 = dp->ReadString(&txtLen);
    std::string text(txt2);

    // Replace instances of our original player/guild name with our custom name

    if (
        strlen(this->customPlayerName)                          // we have a custom name
        && this->originalPlayerName != "\0"                     // old name is set
        && this->customPlayerName != this->originalPlayerName   // custom name is not our old name
    ) {
        std::string::size_type n = 0;
        while ((n = text.find(this->originalPlayerName, n)) != std::string::npos)
        {
            text.replace(n, this->originalPlayerName.size(), this->customPlayerName);
            n += strlen(this->customPlayerName);
        }
    }

    if (
        strlen(this->customGuildName)                           // we have a custom guild name
        && this->originalGuildName != "\0"                      // old guild name is set
        && this->customGuildName != this->originalGuildName     // custom guild name is not our actual guild name
    ) {
        std::string::size_type n = 0;
        while ((n = text.find(this->originalGuildName, n)) != std::string::npos)
        {
            text.replace(n, this->originalGuildName.size(), this->customGuildName);
            n += strlen(this->customGuildName);
        }
    }

    dp->Reset();
    dp->PackCell(text.length());
    dp->PackString(text.c_str());
    return true;
}

void NameChangeModule::ToggleRainbowName(bool enabled)
{
    this->rainbowName = enabled;
    if (!this->rainbowName)
    {
        // Reset name back to white text
        Color white{ 1.0f, 1.0f, 1.0f, 1.0f };
        this->ChangeNameColor(white);
    }
}

void NameChangeModule::ChangeNameColor(Color color)
{
    this->customNameColor = color;

    if (!this->GetCharInfoObject()) return;
    if (!g_pPlayer) return;

    uintptr_t accountName = (uintptr_t)this->charInfoObj->account_name_tmp;
    TMPText_SetColor(accountName, color);
}

void NameChangeModule::ChangePlayerName(const char* name)
{
    this->customPlayerName = name;

    if (!this->GetCharInfoObject()) return;
    if (!g_pPlayer) return;

    uintptr_t accountName_TMP = (uintptr_t)this->charInfoObj->account_name_tmp;
    if (this->originalPlayerName == "\0")
        this->originalPlayerName = ReadUnityString(g_pPlayer->name);

    String* str = il2cpp_string_new(name);
    TMPText_SetText(accountName_TMP, str, true);

    this->log.floatingText = false;
    this->log << "[" << this->name << "] Player name set to: " << name << std::endl;
}

void NameChangeModule::ChangeGuildName(const char* name)
{
    this->customGuildName = name;

    if (!this->GetCharInfoObject())
        return;

    uintptr_t guildInfo_Obj = (uintptr_t)this->charInfoObj->guild_info_obj;
    uintptr_t guildName_TMP = (uintptr_t)this->charInfoObj->guild_name_tmp;

    uintptr_t guildInfo_Transform = GameObject_GetTransform(guildInfo_Obj);
    String* guildName_str = il2cpp_string_new("Guildname");
    uintptr_t guildName_Obj = Component_GetGameObject(Transform_Find(guildInfo_Transform, guildName_str));

    if (this->originalGuildName == "\0")
    {
        String* guildName_txt = *(String**)(guildName_TMP + 0xc8); // m_text, too lazy to make TMPro_Text in reclass for just 1 prop
        this->originalGuildName = ReadUnityString(guildName_txt);
    }

    String* str = il2cpp_string_new(this->customGuildName);
    TMPText_SetText(guildName_TMP, str, true);

    bool showGuildName = strlen(this->customGuildName) != 0;
    GameObject_SetActive(guildInfo_Obj, showGuildName);
    GameObject_SetActive(guildName_Obj, showGuildName);

    this->log.floatingText = false;
    this->log << "[" << this->name << "] Changed guild name to: " << name << std::endl;
}

bool NameChangeModule::GetCharInfoObject()
{
    if (this->charInfoObj)
        return true; // pointer is persistent

    uintptr_t charInfoObj = FindObjectByQualifiedName("DecaGames.RotMG.UI.GUI.CharacterInfo, Assembly-CSharp, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null");
    if (charInfoObj)
    {
        this->charInfoObj = (CharacterInfo_GUI*)charInfoObj;
        return true;
    }

    return false;
}
