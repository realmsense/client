#pragma once

#include "structs.h"
#include "../module.h"

class NoclipModule : public Module {
public:
    NoclipModule(std::string name, bool enabled, ModuleCategory category);

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onMainLoop();
    bool onUnityThreadUpdate();
};
