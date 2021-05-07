#pragma once

#include "structs.h"
#include "../module.h"

class SkinChangeModule : public Module {
public:
    SkinChangeModule();

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onMainLoop();
};
