#include "pch.h"
#include "module.h"

#include "module_list.h"

std::unordered_map<Module*, ModuleList> modules;

void LoadModules()
{
    // TODO: use settings to enable/disable modules
    // some modules (such as noclip) should stay disabled though

}

void UnloadModules()
{
    for (auto& x : modules)
    {
        Module* module = x.first;
        module->setEnabled(false, false);
        delete module;
    }
}

Module* GetModule(std::string name)
{
    for (auto& x : modules)
    {
        Module* module = x.first;
        if (module->name == name)
            return module;
    }

    return nullptr;
}

Module* GetModule(ModuleList type)
{
    for (auto& x : modules)
    {
        if (x.second == type)
            return x.first;
    }

    return nullptr;
}

// Return value is if the function should continue
bool CallEvent(ModuleEvent event)
{
    bool returnValue = true;
    for (auto& x : modules)
    {
        Module* module = x.first;
        if (!module->onEvent(event, NULL))
            returnValue = false;
    }

    return returnValue;
}