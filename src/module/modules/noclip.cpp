#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "noclip.h"

NoclipModule::NoclipModule()
    : Module()
{
    this->name = "Noclip";
    this->enabled = false;
    this->type = ModuleList::NoclipModule;
    this->category = ModuleCategory::MOVEMENT;

    this->noclipSpeed = 1.0f;

    this->ready();
}

void NoclipModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void NoclipModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void NoclipModule::renderGUI()
{

}

bool NoclipModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    case ModuleEvent::UnityThread_Update:
        return this->onUnityThreadUpdate();
    default:
        return true;
    }
}

bool NoclipModule::onMainLoop()
{
    if (!this->enabled)
        return true;

    if (g_pPlayer)
    {
        if (GetAsyncKeyState(0x57)) g_pPlayer->pos.y -= 0.01f * this->noclipSpeed; // w - up
        if (GetAsyncKeyState(0x41)) g_pPlayer->pos.x -= 0.01f * this->noclipSpeed; // a - left
        if (GetAsyncKeyState(0x53)) g_pPlayer->pos.y += 0.01f * this->noclipSpeed; // s - down
        if (GetAsyncKeyState(0x44)) g_pPlayer->pos.x += 0.01f * this->noclipSpeed; // d - right
    }

    return true;
}


bool NoclipModule::onUnityThreadUpdate()
{
    return !this->enabled;
}
