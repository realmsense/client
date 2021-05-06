#pragma once
#include "module.h"
#include "module_list.h"

<<<<<<< Updated upstream
void LoadModules();
void UnloadModules();
std::vector<Module*> GetAllModules();
std::vector<Module*> GetModules(ModuleCategory category);
bool CallEvent(ModuleEvent event, CDataPack* dp);
=======
void load_modules();

void unload_modules();

std::unordered_map<Module*, ModuleList> get_all_modules();

bool call_event(ModuleEvent event, CDataPack* dp);
>>>>>>> Stashed changes

//template<class T>
template<typename T, typename std::enable_if<std::is_base_of<Module, T>::value>::type* = nullptr>
T* GetModule(ModuleList type)
{
<<<<<<< Updated upstream
    std::vector<Module*> modules = GetAllModules();
    for (auto& module : modules)
=======
    std::unordered_map<Module*, ModuleList> modules = get_all_modules();
    for (auto& x : modules)
>>>>>>> Stashed changes
    {
        if (module->type == type)
        {
<<<<<<< Updated upstream
            return (T*)module;
=======
            T* module = static_cast<T*>(x.first);
            return module;
>>>>>>> Stashed changes
        }
    }

    return nullptr;
}
