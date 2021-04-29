#include "pch.h"
#include "module.h"
#include "module_list.h"

std::unordered_map<Module*, ModuleList> modules;

void LoadModules()
{
    // TODO: use settings to enable/disable modules
    // some modules (such as noclip) should stay disabled though

    // View
    DisableFogModule* disableFogModule = new DisableFogModule("Disable Fog", true, ModuleCategory::VIEW);
    modules.insert(std::pair<Module*, ModuleList>(disableFogModule, ModuleList::DisableFogModule));

    UnlimitedZoomModule* unlimitedZoomModule = new UnlimitedZoomModule("Unlimited Zoom", true, ModuleCategory::VIEW);
    modules.insert(std::pair<Module*, ModuleList>(unlimitedZoomModule, ModuleList::UnlimitedZoom));

    // Movement
    NoclipModule* noclipModule = new NoclipModule("Noclip", false, ModuleCategory::MOVEMENT);
    modules.insert(std::pair<Module*, ModuleList>(noclipModule, ModuleList::NoclipModule));

    WalkModule* walkModule = new WalkModule("Walk", false, ModuleCategory::MOVEMENT);
    modules.insert(std::pair<Module*, ModuleList>(walkModule, ModuleList::WalkModule));

    // Auto
    AutoAimModule* autoAimModule = new AutoAimModule("Auto Aim", false, ModuleCategory::AUTO);
    modules.insert(std::pair<Module*, ModuleList>(autoAimModule, ModuleList::AutoAimModule));

    // Other
    NameChangeModule* nameChangeModule = new NameChangeModule("Name Change", false, ModuleCategory::OTHER);
    modules.insert(std::pair<Module*, ModuleList>(nameChangeModule, ModuleList::NameChange));
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

std::unordered_map<Module*, ModuleList> GetAllModules()
{
    return modules;
}

// Return value is if the function should continue
bool CallEvent(ModuleEvent event, CDataPack* dp)
{
    bool returnValue = true;
    for (auto& x : modules)
    {
        Module* module = x.first;
        if (!module->onEvent(event, dp))
            returnValue = false;
    }

    return returnValue;
}
