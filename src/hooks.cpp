#include "pch.h"
#include "helpers.h"
#include "minhook/include/MinHook.h"
#include "module/module_manager.h"

// function typdef _FunctionName
#define DO_APP_FUNC(a, r, n, p) typedef r (* _ ## n) p;
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

// Original_ pointer
#define DO_APP_FUNC(a, r, n, p) _ ## n Original_ ## n = nullptr;
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

bool Detour_DKMLMKFGPCC_NAGLHCDBGIM(DKMLMKFGPCC* __this, float EOOJAMLJAOM, float JDEKCEFBJFP, MethodInfo* method)
{
	bool override = false;
	bool ret = ModuleManager::CallEvent(ModuleEvent::Check_TileWalkable, override);

	if (override)
		return ret;
	
	return Original_DKMLMKFGPCC_NAGLHCDBGIM(__this, EOOJAMLJAOM, JDEKCEFBJFP, method);
}

bool InitHooks()
{
	bool ret = true;
	uintptr_t baseAddress = GetBaseAddress();

	if (MH_CreateHook(DKMLMKFGPCC_NAGLHCDBGIM, Detour_DKMLMKFGPCC_NAGLHCDBGIM, reinterpret_cast<LPVOID*>(&Original_DKMLMKFGPCC_NAGLHCDBGIM)) != MH_OK)
	{
		std::cout << "Failed to Detour DKMLMKFGPCC_NAGLHCDBGIM" << std::endl;
		ret = false;
	}

	// TODO: generate hooks automatically
	// use #define DO_APP_FUNC and #include "il2cpp-functions.h" to generate

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		std::cout << "Failed to initialize hooks" << std::endl;
		ret = false;
	}

	return ret;
}

void RemoveHooks()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}