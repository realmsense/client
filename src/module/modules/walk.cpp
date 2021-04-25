#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "Walk.h"

WalkModule::WalkModule(std::string name, bool enabled, ModuleCategory category)
    : Module(name, enabled, category)
{
    this->oldSpeed = 0.0f;
    this->walkModifier = 2.0f;
}

void WalkModule::onEnable()
{
    if (!g_pPlayer) return;

    std::cout << this->name << " enabled" << std::endl;
    this->oldSpeed = g_pPlayer->speed;
    g_pPlayer->speed /= this->walkModifier;
}

void WalkModule::onDisable()
{
    if (!g_pPlayer) return;

    std::cout << this->name << " disabled" << std::endl;
    g_pPlayer->speed = oldSpeed;
}

bool WalkModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    default:
        return true;
    }
}

bool WalkModule::onMainLoop()
{
    // LShift - on press, toggle on
    if (GetAsyncKeyState(VK_LSHIFT) < 0 && !this->enabled)
    {
        this->setEnabled(true, true);
    }

    // LShift - on release, toggle off
    if (GetAsyncKeyState(VK_LSHIFT) == 0 && this->enabled)
    {
        this->setEnabled(false, true);
    }

    return true;
}
