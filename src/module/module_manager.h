#pragma once
#include "module.h"
#include "module_list.h"

void LoadModules();
void UnloadModules();
std::unordered_map<Module*, ModuleList> GetAllModules();
bool CallEvent(ModuleEvent event, CDataPack* dp);

//template<class T>
template<typename T, typename std::enable_if<std::is_base_of<Module, T>::value>::type* = nullptr>
T* GetModule(ModuleList type)
{
    std::unordered_map<Module*, ModuleList> modules = GetAllModules();
    for (auto& x : modules)
    {
        if (x.second == type)
        {
            T* module = (T*)x.first;
            return module;
        }
    }

    return nullptr;
}
