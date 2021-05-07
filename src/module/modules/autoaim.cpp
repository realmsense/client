#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "imgui/imgui.h"
#include "autoAim.h"

AutoAimModule::AutoAimModule()
    : Module()
{
    this->name = "Auto Aim";
    this->enabled = false;
    this->type = ModuleList::AutoAim;
    this->category = ModuleCategory::AUTO;
    this->hasGuiElements = true;

    // TODO: load the target option from config or default to closest mouse
    this->target = AutoAimTarget::ClosestMouse;
    this->ready();
}

void AutoAimModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void AutoAimModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void AutoAimModule::renderGUI()
{
    const char* aim_targets[] =
    {
        "Closest to Mouse",     // AutoAimTarget::ClosestMouse
        "Closest to Player",    // AutoAimTarget::ClosestPos
        "Highest Defense",      // AutoAimTarget::HighestDef
        "Highest Max HP (Boss)" // AutoAimTarget::HighestMaxHP
    };

    static int selected_target = 1;
    ImGui::SetNextItemWidth(ImGui::GetTextLineHeightWithSpacing() * strlen(aim_targets[3]) / 2); // set width to the widest string
    if (ImGui::Combo("Auto Aim Target", &selected_target, aim_targets, IM_ARRAYSIZE(aim_targets), IM_ARRAYSIZE(aim_targets)))
    {
        this->target = static_cast<AutoAimTarget>(selected_target);
        this->log.floatingText = false;
        this->log << "Auto Aim Target: " << aim_targets[selected_target] << std::endl;
    }
}

bool AutoAimModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    if (!this->enabled)
        return true;

    switch (event)
    {
    case ModuleEvent::GetMousePos:
        return this->onGetMousePos(dp);
    default:
        return true;
    }
}

bool AutoAimModule::onGetMousePos(CDataPack* dp)
{
    dp->Reset();
    Vector3 mouse_pos{};
    mouse_pos.x = dp->ReadFloat();
    mouse_pos.y = dp->ReadFloat();

    Entity* chosen_enemy = nullptr;

    for (auto& enemy : g_aEnemyList)
    {
        if (chosen_enemy == nullptr)
        {
            chosen_enemy = enemy;
            continue;
        }

        if (this->target == AutoAimTarget::ClosestPos)
        {
            const float chosen_distance = CalculateDistance(chosen_enemy->pos, g_pPlayer->pos);
            const float current_distance = CalculateDistance(enemy->pos, g_pPlayer->pos);

            if (current_distance < chosen_distance)
                chosen_enemy = enemy;
        }
        else if (this->target == AutoAimTarget::ClosestMouse)
        {
            const Vector3 mouse_world_pos3 = ScreenToWorld(g_pMainCamera, mouse_pos);
            const Vector2 mouse_world_pos = { mouse_world_pos3.x, mouse_world_pos3.y * -1 };

            const float chosen_distance = CalculateDistance(chosen_enemy->pos, mouse_world_pos);
            const float currentdistance = CalculateDistance(enemy->pos, mouse_world_pos);

            if (currentdistance < chosen_distance) 
                chosen_enemy = enemy;

        }
        else if (this->target == AutoAimTarget::HighestDef)
        {
            // TODO: what happens if the enemy is armor broken?
            // (abrn) I don't think this matters because the defense itself doesn't change on armor break
            const int chosen_def = chosen_enemy->defense;
            const int current_defense = enemy->defense;

            if (current_defense > chosen_def)
                chosen_enemy = enemy;
        }
        else if (this->target == AutoAimTarget::HighestMaxHP)
        {
            const int chosen_hp = chosen_enemy->max_hp;
            const int current_hp = enemy->max_hp;
            if (chosen_hp > current_hp)
                chosen_enemy = enemy;
        }
        else
            chosen_enemy = enemy;

        if (chosen_enemy != nullptr)
            break;
    }

    if (chosen_enemy)
    {
        const Vector3 enemy_pos = { chosen_enemy->pos.x, (chosen_enemy->pos.y) * -1, 0.0f };
        const Vector3 enemy_screen_pos = WorldToScreen(g_pMainCamera, enemy_pos);

        dp->Reset();
        dp->PackFloat(enemy_screen_pos.x);
        dp->PackFloat(enemy_screen_pos.y);
    }

    //std::cout << mousePos.x << "," << mousePos.y << std::endl;

    return true;
}
