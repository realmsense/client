#pragma once
#include "module.h"
#include "module_list.h"

void LoadModules();
void UnloadModules();
std::vector<Module*> GetAllModules();
bool CallEvent(ModuleEvent event, CDataPack* dp);

//template<class T>
template<typename T, typename std::enable_if<std::is_base_of<Module, T>::value>::type* = nullptr>
T* GetModule(ModuleList type)
{
    std::vector<Module*> modules = GetAllModules();
    for (auto& module : modules)
    {
        if (module->type == type)
        {
            return (T*)module;
        }
    }

    return nullptr;
}
