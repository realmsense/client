#pragma once

#include "structs.h"
#include "../module.h"

class DisableFogModule : public Module {
public:
    DisableFogModule();

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onTileSetColor(CDataPack* dp);
};
