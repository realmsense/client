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

    this->ready();
}

void SkinChangeModule::onEnable()
{
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void SkinChangeModule::onDisable()
{
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void SkinChangeModule::renderGUI()
{
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

    return true;
}
