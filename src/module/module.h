#pragma once

#include "pch.h"

class Module {
public:

    bool enabled;
    std::string name;
    ModuleCategory category;
    // hotkey

    Module(std::string name, bool enabled, ModuleCategory category);

    void setEnabled(bool enabled, bool callHandlers);
    void toggleModule();
    void toggleModule(bool enabled);
    virtual bool onEvent(ModuleEvent event, CDataPack* dp) = 0;

protected:

    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
};
