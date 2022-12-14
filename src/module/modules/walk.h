#pragma once

#include "structs.h"
#include "../module.h"

class WalkModule : public Module {
public:
    WalkModule();

    float walkModifier;
    float oldSpeed;

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onMainLoop();
};
