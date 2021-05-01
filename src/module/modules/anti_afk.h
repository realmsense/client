#pragma once

#include "structs.h"
#include "../module.h"

class AntiAfkModule : public Module {
public:
    AntiAfkModule(std::string name, bool enabled, ModuleCategory category);

    uintptr_t idleWatcherObj;

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool GetIdleWatcher();
};
