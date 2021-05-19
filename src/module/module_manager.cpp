#include "pch.h"
#include "module.h"
#include "module_list.h"

namespace ModuleManager
{
	std::vector<Module*> modules;

	void LoadModules()
	{
		std::cout << "Loading Modules..." << std::endl;
		modules.push_back(new NoclipModule());
	}

	void UnloadModules()
	{
		std::cout << "Unloading Modules..." << std::endl;
	}
}