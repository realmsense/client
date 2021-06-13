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
		modules.push_back(new AutoAimModule());
		modules.push_back(new AutoNexusModule());
		modules.push_back(new SkinChangerModule());
		modules.push_back(new CameraSettingsModule());
		modules.push_back(new NameChangeModule());
		modules.push_back(new DebugModule());
	}

	void UnloadModules()
	{
		std::cout << "Unloading Modules..." << std::endl;
	}
}