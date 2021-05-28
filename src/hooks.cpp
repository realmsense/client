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

bool Detour_MapViewService_CheckTileWalkable(MapViewService* __this, float EOOJAMLJAOM, float JDEKCEFBJFP, MethodInfo* method)
{
	bool walkable = Original_MapViewService_CheckTileWalkable(__this, EOOJAMLJAOM, JDEKCEFBJFP, method);

	for (Module* module : ModuleManager::modules)
		module->onCheckTileWalkable(walkable);

	return walkable;
}

void Detour_Player_Shoot(Player* __this, float angle, MethodInfo* method)
{
	for (Module* module : ModuleManager::modules)
		module->onPlayerShoot(__this, angle);

	return Original_Player_Shoot(__this, angle, method);
}

void Detour_BasicObject_Init(BasicObject* __this, MethodInfo* method)
{
	switch (__this->fields.CDNHIOHCAIB)
	{
		case MapObjectType::Character: // enemy
		{
			g_aEnemyList.insert((Character*)__this);
			break;
		}
	}

	return Original_BasicObject_Init(__this, method);
}

bool InitHooks()
{
	bool ret = true;
	uintptr_t baseAddress = GetBaseAddress();
	std::cout << "GameAssembly.dll at " << std::hex << baseAddress << std::endl;

	if (MH_CreateHook(MapViewService_CheckTileWalkable, Detour_MapViewService_CheckTileWalkable, reinterpret_cast<LPVOID*>(&Original_MapViewService_CheckTileWalkable)) != MH_OK)
	{
		std::cout << "Failed to Detour MapViewService_NAGLHCDBGIM" << std::endl;
		ret = false;
	}

	if (MH_CreateHook(BasicObject_Init, Detour_BasicObject_Init, reinterpret_cast<LPVOID*>(&Original_BasicObject_Init)) != MH_OK)
	{
		std::cout << "Failed to Detour BasicObject_Init" << std::endl;
		ret = false;
	}

	if (MH_CreateHook(Player_Shoot, Detour_Player_Shoot, reinterpret_cast<LPVOID*>(&Original_Player_Shoot)) != MH_OK)
	{
		std::cout << "Failed to Detour Player_Shoot" << std::endl;
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