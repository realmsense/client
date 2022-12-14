#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "disable_fog.h"

DisableFogModule::DisableFogModule()
    : Module()
{
    this->name = "Disable Fog";
    this->enabled = false;
    this->type = ModuleList::DisableFog;
    this->category = ModuleCategory::VIEW;
    this->hasGuiElements = false;

    this->ready();
}

void DisableFogModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;

    if (g_pMapViewHelper)
        DisableFog(g_pMapViewHelper);
}

void DisableFogModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;

    if (g_pMapViewHelper)
        EnableFog(g_pMapViewHelper);
}

void DisableFogModule::renderGUI()
{

}

bool DisableFogModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        this->onMainLoop();
    default:
        return true;
    }
}


bool DisableFogModule::onMainLoop()
{
    static uintptr_t old_MapViewHelper = 0;

    if (old_MapViewHelper != g_pMapViewHelper)
    {
        if (this->enabled)
            this->onEnable();
        // no need to call onDisable, as fog is disabled by default.
    }

    old_MapViewHelper = g_pMapViewHelper;
    return true;
}
