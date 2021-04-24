#pragma once
#include "module.h"
#include "module_list.h"

void LoadModules();
void UnloadModules();
Module* GetModule(std::string name);
Module* GetModule(ModuleList type);
bool CallEvent(ModuleEvent event);
