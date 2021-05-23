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
	bool walkable = Original_DKMLMKFGPCC_NAGLHCDBGIM(__this, EOOJAMLJAOM, JDEKCEFBJFP, method);

	for (Module* module : ModuleManager::modules)
		module->onCheckTileWalkable(walkable);

	return walkable;
}

void Detour_GJLIMCBOCJG_GPIMPPOPDJO(GJLIMCBOCJG* __this, MethodInfo* method)
{
	switch (__this->fields.CDNHIOHCAIB)
	{
		case OMIPCDPIAOC__Enum::Character: // enemy
		{
			g_aEnemyList.insert((COEDKELBKMI*)__this);
			break;
		}
	}

	return Original_GJLIMCBOCJG_GPIMPPOPDJO(__this, method);
}

bool InitHooks()
{
	bool ret = true;
	uintptr_t baseAddress = GetBaseAddress();
	std::cout << "GameAssembly.dll at " << std::hex << baseAddress << std::endl;

	if (MH_CreateHook(DKMLMKFGPCC_NAGLHCDBGIM, Detour_DKMLMKFGPCC_NAGLHCDBGIM, reinterpret_cast<LPVOID*>(&Original_DKMLMKFGPCC_NAGLHCDBGIM)) != MH_OK)
	{
		std::cout << "Failed to Detour DKMLMKFGPCC_NAGLHCDBGIM" << std::endl;
		ret = false;
	}

	if (MH_CreateHook(GJLIMCBOCJG_GPIMPPOPDJO, Detour_GJLIMCBOCJG_GPIMPPOPDJO, reinterpret_cast<LPVOID*>(&Original_GJLIMCBOCJG_GPIMPPOPDJO)) != MH_OK)
	{
		std::cout << "Failed to Detour GJLIMCBOCJG_GPIMPPOPDJO" << std::endl;
		ret = false;
	}

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