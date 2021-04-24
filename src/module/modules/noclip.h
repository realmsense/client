#pragma once

#include "structs.h"
#include "../module.h"

class NoclipModule : public Module {
public:
    //using Module::Module; // use Module's constructor

    NoclipModule(std::string name, bool enabled, ModuleCategory category);

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, void* args);

private:
    bool onMainLoop();
    bool onUnityThreadUpdate();
};
