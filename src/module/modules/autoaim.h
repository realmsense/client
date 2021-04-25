#pragma once

#include "structs.h"
#include "../module.h"

class AutoAimModule : public Module {
public:
    AutoAimModule(std::string name, bool enabled, ModuleCategory category);

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onGetMousePos(CDataPack* dp);
};
