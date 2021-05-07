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
    this->category = ModuleCategory::OTHER;
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
    static int img_size = 52;
    ImGui::SliderInt("Icon Size", &img_size, 0, 100);

    // move to another function, where we #include "skins.h"
    static std::map<ClassList, std::vector<Skin*>> skinList;
    static bool init = false;
    if (!init)
    {
        #include "../../other/skins.h"
        init = true;
    }

    const char* class_names[] = { "All", "Rogue", "Archer", "Wizard", "Priest", "Warrior", "Knight", "Paladin", "Assassin", "Necromancer", "Huntress", "Mystic", "Trickster", "Sorcerer", "Ninja", "Samurai", "Bard", "Summoner" };

    ImGuiStyle& style = ImGui::GetStyle();
    float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    // TODO: wrap tab bar
    if (ImGui::BeginTabBar("Skin Changer"))
    {
        for (int i = 0; i < (int)ClassList::Count; i++)
        {
            ClassList current_class = ClassList(i);
            const char* class_name = class_names[i];
            if (ImGui::BeginTabItem(class_name))
            {
                for (Skin* skin : skinList[current_class])
                {
                    ImGui::PushID(skin->name.c_str());
    
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

                    float last_button_x2 = ImGui::GetItemRectMax().x;
                    float next_button_x2 = last_button_x2 + style.ItemSpacing.x + img_size; // Expected position if next button was on same line
                    if (i + 1 < (int)ClassList::Count && next_button_x2 < window_visible_x2)
                        ImGui::SameLine();

                    ImGui::PopID();
                }

                // add extra height after skins, hotfix for bug with wrapping
                ImGui::Dummy(ImVec2(0.0f, (float)img_size));
                ImGui::EndTabItem();
            }
        }
    
        ImGui::EndTabBar();
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
