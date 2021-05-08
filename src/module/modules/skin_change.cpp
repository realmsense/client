#include "pch.h"
#include "gui.h"
#include "../module.h"
#include "../module_manager.h"

#include "imgui/imgui.h"
#include "skin_change.h"

SkinChangeModule::SkinChangeModule()
    : Module()
{
    this->name = "Skin Change";
    this->enabled = false;
    this->type = ModuleList::SkinChange;
    this->category = ModuleCategory::VIEW;
    this->hasGuiElements = true;

    this->skin_id = 0;

    this->ready();
}

void SkinChangeModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void SkinChangeModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void SkinChangeModule::renderGUI()
{
    static int img_size = 30;
    ImGui::SliderInt("Icon Size", &img_size, 0, 100);

    // move to another function, where we #include "skins.h"
    static std::map<ClassList, std::vector<Skin*>> skinList;
    static bool init = false;
    if (!init)
    {
        #include "../../other/skins.h"
        init = true;
    }

    const char* class_names[] = { "Any", "Rogue", "Archer", "Wizard", "Priest", "Warrior", "Knight", "Paladin", "Assassin", "Necromancer", "Huntress", "Mystic", "Trickster", "Sorcerer", "Ninja", "Samurai", "Bard", "Summoner" };
    static ClassList active_class = ClassList(0);

    for (int i = 0; i < (int)ClassList::Count; i++)
    {
        ClassList current_class = ClassList(i);
        const char* class_name = class_names[i];

        if (ImGui::Button(class_name))
        {
            active_class = current_class;
        }

        GUI_WrapInLoop(i, (int)ClassList::Count);
    }

    for (int i = 0; i < skinList[active_class].size(); i++)
    {
        Skin* skin = skinList[active_class][i];

        void* texture_id = (void*)skin->Load();
        ImVec2 image_size((float)img_size, (float)img_size);
        if (ImGui::ImageButton(texture_id, image_size))
        {
            this->ChangeSkin(skin->skin_id);
            this->log.floatingText = false;
            this->log << "Change Skin to: " << skin->skin_id << std::endl;
            this->setEnabled(true, false);
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(skin->name.c_str());
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }

        GUI_WrapInLoop(i, skinList[active_class].size());
    }

}

bool SkinChangeModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    default:
        return true;
    }
}

bool SkinChangeModule::onMainLoop()
{
    static uintptr_t old_player_addr;
    if (old_player_addr != (uintptr_t)g_pPlayer)
    {
        if (this->enabled)
            this->ChangeSkin(this->skin_id);
    }

    old_player_addr = (uintptr_t)g_pPlayer;
    return true;
}

void SkinChangeModule::ChangeSkin(int skin_id)
{
    if (g_pPlayer)
    {
        this->skin_id = skin_id;
        g_pPlayer->skinID = skin_id;
    }
}


Skin::Skin(std::string name, std::string file_name, int skin_id)
    : Image(file_name)
{
    this->name = name;
    this->skin_id = skin_id;
}
