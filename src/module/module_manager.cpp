#include "pch.h"
#include "module.h"
#include "module_list.h"

std::vector<Module*> modules;

/**
 * @brief Start loading cheat modules, dependant on the saved settings or module type
 *
 * @note example: we can save and load a username change on startup, using the module config
 * @note example: noclip cannot be enabled by default or the game will break
 */
void load_modules()
{
    // TODO: use settings to enable/disable modules - BUT some modules (such as noclip) cannot be enabled at startup

<<<<<<< Updated upstream
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
    modules.push_back(new NameChangeModule());
=======
    /* ---- Viewport or rendering ---- */

    auto* disable_fog_module = new DisableFogModule(
        "Disable fog",
        true,
        ModuleCategory::VIEW);
    modules.insert(std::pair<Module*, ModuleList>(disable_fog_module, ModuleList::DisableFogModule));

    auto* unlimited_zoom_module = new UnlimitedZoomModule(
        "Unlimited zoom",
        true,
        ModuleCategory::VIEW);
    modules.insert(std::pair<Module*, ModuleList>(unlimited_zoom_module, ModuleList::UnlimitedZoom));

    auto* anti_lag_module = new AntiLagModule(
        "Anti-lag",
        true,
        ModuleCategory::VIEW);
    modules.insert(std::pair<Module*, ModuleList>(anti_lag_module, ModuleList::AntiLag));


    /* ---- Player movement or action ---- */


    auto* noclip_module = new NoclipModule(
        "Noclip",
        false,
        ModuleCategory::MOVEMENT);
    modules.insert(std::pair<Module*, ModuleList>(noclip_module, ModuleList::NoclipModule));

    auto* walk_module = new WalkModule(
        "Walk",
        false,
        ModuleCategory::MOVEMENT);
    modules.insert(std::pair<Module*, ModuleList>(walk_module, ModuleList::WalkModule));

    auto* auto_aim = new AutoAimModule(
        "Auto Aim",
        false,
        ModuleCategory::AUTO);
    modules.insert(std::pair<Module*, ModuleList>(auto_aim, ModuleList::AutoAimModule));


    /* ---- Other ---- */


    auto* name_changer = new NameChangeModule(
        "Name changer",
        false,
        ModuleCategory::OTHER);
    modules.insert(std::pair<Module*, ModuleList>(name_changer, ModuleList::NameChange));

    auto* anti_afk = new AntiAfkModule(
        "Anti AFK",
        false,
        ModuleCategory::OTHER);
    modules.insert(std::pair<Module*, ModuleList>(anti_afk, ModuleList::AntiAFK));
>>>>>>> Stashed changes
}

/**
 * @brief Unload every currently loaded module
 *
 * @note use this if you want to gracefully uninject from the game
 */
void unload_modules()
{
<<<<<<< Updated upstream
    for (auto& module : modules)
    {
=======
    // loops over a deferenced pointer to each module
    // disables it, then deletes it
    for (auto& x : modules)
    {
        auto* module = x.first;
>>>>>>> Stashed changes
        module->setEnabled(false, false);
        delete module;
    }
}

<<<<<<< Updated upstream
std::vector<Module*> GetAllModules()
=======
/**
 * @brief  Returns an unordered map of all modules
 *
 * @return std::unordered_map<Module*, ModuleList>
 */
std::unordered_map<Module*, ModuleList> get_all_modules()
>>>>>>> Stashed changes
{
    return modules;
}

<<<<<<< Updated upstream
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
=======
/**
 * @brief  Fire an event inside of a module
 *
 * @param  event : The type of event to fire
 * @param  dp : Pointer to a data stream passed for the event
 *
 * @return bool : true or false whether the call should continue
 */
bool call_event(ModuleEvent event, CDataPack* dp)
{
    auto returnValue = true;
    for (auto& x : modules)
    {
        auto* module = x.first;
>>>>>>> Stashed changes
        if (!module->onEvent(event, dp))
            returnValue = false;
    }

    return returnValue;
}

/* TODO: create a configuration structure for each module. i.e for noclip, one config would be to
   TODO         block the player turning off noclip on an unwalkable tile */
