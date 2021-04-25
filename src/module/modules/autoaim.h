#pragma once

#include "structs.h"
#include "../module.h"

enum class AutoAimTarget
{
    ClosestMouse,
    ClosestPos,
    HighestDef,
    HighestMaxHP
};

class AutoAimModule : public Module {
public:
    AutoAimModule(std::string name, bool enabled, ModuleCategory category);

    AutoAimTarget target;

    void onEnable();
    void onDisable();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onGetMousePos(CDataPack* dp);
};
