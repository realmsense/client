#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "disable_fog.h"

DisableFogModule::DisableFogModule(std::string name, bool enabled, ModuleCategory category)
    : Module(name, enabled, category)
{

}

void DisableFogModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void DisableFogModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

bool DisableFogModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::Tile_SetColor:
        return this->onTileSetColor(dp);
    default:
        return true;
    }
}

bool DisableFogModule::onTileSetColor(CDataPack* dp)
{
    if (!this->enabled)
        return true;

    Color color;
    dp->Reset();
    color.r = dp->ReadFloat();
    color.g = dp->ReadFloat();
    color.b = dp->ReadFloat();
    color.a = dp->ReadFloat();

    // Don't change the tile's color if it is being darkened
    if (color.r != 1 || color.g != 1 || color.b != 1 || color.a != 1)
        return false;

    return true;
}
