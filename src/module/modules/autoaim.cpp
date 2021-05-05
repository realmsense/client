#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "AutoAim.h"

AutoAimModule::AutoAimModule()
    : Module()
{
    this->name = "Auto Aim";
    this->enabled = false;
    this->type = ModuleList::AutoAimModule;
    this->category = ModuleCategory::AUTO;

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
    Vector3 mousePos;
    mousePos.x = dp->ReadFloat();
    mousePos.y = dp->ReadFloat();

    Entity* chosenEnemy = nullptr;
    for (auto& enemy : g_aEnemyList)
    {
        if (chosenEnemy == nullptr)
        {
            chosenEnemy = enemy;
            continue;
        }

        if (this->target == AutoAimTarget::ClosestPos)
        {
            float chosenDistance = CalculateDistance(chosenEnemy->pos, g_pPlayer->pos);
            float currentDistance = CalculateDistance(enemy->pos, g_pPlayer->pos);
            if (currentDistance < chosenDistance)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (this->target == AutoAimTarget::ClosestMouse)
        {
            Vector3 mouseWorldPos3 = ScreenToWorld(g_pMainCamera, mousePos);
            Vector2 mouseWorldPos = { mouseWorldPos3.x, mouseWorldPos3.y * -1 };
            float chosenDistance = CalculateDistance(chosenEnemy->pos, mouseWorldPos);
            float currentdistance = CalculateDistance(enemy->pos, mouseWorldPos);
            if (currentdistance < chosenDistance)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (this->target == AutoAimTarget::HighestDef)
        {
            // TODO: what happens if the enemy is armor broken?
            int chosenDef = chosenEnemy->defense;
            int currentDefense = enemy->defense;
            if (currentDefense > chosenDef)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (this->target == AutoAimTarget::HighestMaxHP)
        {
            int chosenHP = chosenEnemy->maxHP;
            int currentHP = enemy->maxHP;
            if (chosenHP > currentHP)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else
        {
            chosenEnemy = enemy;
            break;
        }
    }

    if (chosenEnemy)
    {
        Vector3 enemyPos = { chosenEnemy->pos.x, (chosenEnemy->pos.y) * -1, 0.0f };
        Vector3 enemyScreenPos = WorldToScreen(g_pMainCamera, enemyPos);

        dp->Reset();
        dp->PackFloat(enemyScreenPos.x);
        dp->PackFloat(enemyScreenPos.y);
    }

    //std::cout << mousePos.x << "," << mousePos.y << std::endl;

    return true;
}
