#include "pch.h"
#include "module.h"
#include "module_list.h"

std::vector<Module*> modules;

void LoadModules()
{
    // TODO: use settings to enable/disable modules
    // some modules (such as noclip) should stay disabled though

    // View
    modules.push_back(new DisableFogModule());
    modules.push_back(new UnlimitedZoomModule());
    modules.push_back(new AntiLagModule());

    // Movement
    modules.push_back(new NoclipModule());
    modules.push_back(new WalkModule());

    // Auto
    modules.push_back(new AutoAimModule());
    
    // Other
    modules.push_back(new AntiAfkModule());
}

void UnloadModules()
{
    for (auto& module : modules)
    {
        module->setEnabled(false, false);
        delete module;
    }
}

std::vector<Module*> GetAllModules()
{
    return modules;
}

std::vector<Module*> GetModules(ModuleCategory category)
{
    std::vector<Module*> ret;
    for (auto module : modules)
    {
        if (module->category == category)
            ret.push_back(module);
    }
    return ret;
}

// Return value is if the function should continue
bool CallEvent(ModuleEvent event, CDataPack* dp)
{
    bool returnValue = true;
    for (auto& module : modules)
    {
        if (!module->onEvent(event, dp))
            returnValue = false;
    }

    return returnValue;
}
