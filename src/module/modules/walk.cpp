#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "imgui/imgui.h"
#include "walk.h"

WalkModule::WalkModule()
    : Module()
{
    this->name = "Walk";
    this->enabled = false;
    this->type = ModuleList::WalkModule;
    this->category = ModuleCategory::MOVEMENT;
    this->hasGuiElements = true;

    this->oldSpeed = 0.0f;
    this->walkModifier = 2.0f;

    this->ready();
}

void WalkModule::onEnable()
{
    if (!g_pPlayer) return;

    this->log.color = Color32_GREEN;
    this->log.floatingText = false;
    this->log << this->name << " enabled" << std::endl;

    this->oldSpeed = g_pPlayer->speed;
    g_pPlayer->speed /= this->walkModifier;
}

void WalkModule::onDisable()
{
    if (!g_pPlayer) return;

    this->log.color = Color32_RED;
    this->log.floatingText = false;
    this->log << this->name << " disabled" << std::endl;

    g_pPlayer->speed = oldSpeed;
}

void WalkModule::renderGUI()
{
    ImGui::SliderFloat("Walk Modifier", &this->walkModifier, 1.0f, 10.0f);
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
