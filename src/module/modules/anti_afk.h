#pragma once

#include "structs.h"
#include "../module.h"

class AntiAfkModule : public Module {
public:
    AntiAfkModule();

    uintptr_t idleWatcherObj;

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool GetIdleWatcher();
};
