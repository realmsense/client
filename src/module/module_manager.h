#pragma once

#include "module.h"

namespace ModuleManager
{
	extern std::vector<Module*> modules;
	void LoadModules();
	void UnloadModules();

    template<typename T, typename std::enable_if<std::is_base_of<Module, T>::value>::type* = nullptr>
    T* FindModule(ModuleList type)
    {
        for (Module* module : modules)
        {
            if (module->type == type)
            {
                return (T*)module;
            }
        }
        return nullptr;
    }
}