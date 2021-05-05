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

    this->charInfoObj = 0;

    this->customPlayerName = "";
    this->customGuildName = "";
    this->oldGuildName = "\0";
    this->oldPlayerName = "\0";

    Color white{ 1.0f, 1.0f, 1.0f, 1.0f };
    this->rainbowText = false;
    this->nameColor = white;

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
}

void NameChangeModule::renderGUI()
{

}

bool NameChangeModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    case ModuleEvent::TMP_SetText:
        return this->onTMPSetText(dp);
    default:
        return true;
    }
}

bool NameChangeModule::onMainLoop()
{
    if (this->rainbowText)
    {
        static float hue = 1.0f;
        static float speed = 0.0035f;
        hue += speed;
        if (hue > 360.0f) hue = 1.0f;

        ImVec4 rainbow = (ImVec4)(ImColor)ImColor::HSV(hue, 1.0f, 1.0f);
        this->nameColor = { rainbow.x, rainbow.y, rainbow.z, 1.0f };
        this->ChangeNameColor(this->nameColor);
    }

    return true;
}

bool NameChangeModule::onTMPSetText(CDataPack* dp)
{
    dp->Reset();
    size_t txtLen = dp->ReadCell();
    const char* txt2 = dp->ReadString(&txtLen);
    std::string text(txt2);

    if (
        strlen(this->customPlayerName)                      // we have a custom name
        && this->oldPlayerName != "\0"                      // old name is set
        && this->customPlayerName != this->oldPlayerName    // custom name is not our old name
    ) {
        std::string::size_type n = 0;
        while ((n = text.find(this->oldPlayerName, n)) != std::string::npos)
        {
            text.replace(n, this->oldPlayerName.size(), this->customPlayerName);
            n += strlen(this->customPlayerName);
        }
    }

    if (
        strlen(this->customGuildName)                   // we have a custom guild name
        && this->oldGuildName != "\0"                   // old guild name is set
        && this->customGuildName != this->oldGuildName  // custom guild name is not our actual guild name
    ) {
        std::string::size_type n = 0;
        while ((n = text.find(this->oldGuildName, n)) != std::string::npos)
        {
            text.replace(n, this->oldGuildName.size(), this->customGuildName);
            n += strlen(this->customGuildName);
        }
    }

    dp->Reset();
    dp->PackCell(text.length());
    dp->PackString(text.c_str());
    return true;
}

void NameChangeModule::ChangeNameColor(Color color)
{
    if (!this->GetCharInfoObject())
        return;

    uintptr_t accountName = (uintptr_t)this->charInfoObj->accountName_TMP;
    std::cout << std::hex << accountName << std::endl;
    TMPText_SetColor(accountName, color);
}

void NameChangeModule::ChangePlayerName(const char* name)
{
    this->customPlayerName = name;

    if (!this->GetCharInfoObject())
        return;

    uintptr_t accountName_TMP = (uintptr_t)this->charInfoObj->accountName_TMP;

    if (this->oldPlayerName == "\0")
    {
        //String* accountName_txt = *(String**)(accountName_TMP + 0xc8); // m_text, too lazy to make TMPro_Text in reclass for just 1 prop
        this->oldPlayerName = ReadUnityString(g_pPlayer->name);
    }

    String* str = il2cpp_string_new(name);
    TMPText_SetText(accountName_TMP, str, true);

    std::cout << "[" << this->name << "] Changed player name to: " << name << std::endl;
}

void NameChangeModule::ChangeGuildName(const char* name)
{
    this->customGuildName = name;

    if (!this->GetCharInfoObject())
        return;

    uintptr_t guildInfo_Obj = (uintptr_t)this->charInfoObj->guildInfo_Obj;
    uintptr_t guildName_TMP = (uintptr_t)this->charInfoObj->guildName_TMP;

    uintptr_t guildInfo_Transform = GameObject_GetTransform(guildInfo_Obj);
    String* guildName_str = il2cpp_string_new("Guildname");
    uintptr_t guildName_Obj = Component_GetGameObject(Transform_Find(guildInfo_Transform, guildName_str));

    if (this->oldGuildName == "\0")
    {
        String* guildName_txt = *(String**)(guildName_TMP + 0xc8); // m_text, too lazy to make TMPro_Text in reclass for just 1 prop
        this->oldGuildName = ReadUnityString(guildName_txt);
    }

    String* str = il2cpp_string_new(this->customGuildName);
    TMPText_SetText(guildName_TMP, str, true);

    bool showGuildName = strlen(this->customGuildName) != 0;
    GameObject_SetActive(guildInfo_Obj, showGuildName);
    GameObject_SetActive(guildName_Obj, showGuildName);
    std::cout << "[" << this->name << "] Changed guild name to: " << name << std::endl;
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
