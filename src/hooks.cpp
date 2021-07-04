#include "pch.h"
#include "helpers.h"
#include "module/module_manager.h"
#include "thirdparty/minhook/include/MinHook.h"

// function typdef _FunctionName
#define DO_APP_FUNC_METHODINFO(a, n) extern struct MethodInfo ** n // unused

#define DO_APP_FUNC(a, r, n, p) typedef r (* _ ## n) p;
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

// Original_ pointer
#define DO_APP_FUNC(a, r, n, p) _ ## n Original_ ## n = nullptr;
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

#undef DO_APP_FUNC_METHODINFO

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
			if (__this->fields.BEHCPLKDAFD->fields.isEnemy)
			{
				g_aEnemyList.insert((Character*)__this);
			}
			break;
		}
	}

	return Original_BasicObject_Init(__this, method);
}

void Detour_SpriteShader_UpdateMask(SpriteShader* __this, CGPOGAAKLFL* DLNMEAOOHKA, int32_t large_cloth, int32_t small_cloth, MethodInfo* method)
{
	for (Module* module : ModuleManager::modules)
		module->onSpriteShader_UpdateMask(__this, large_cloth, small_cloth);

	return Original_SpriteShader_UpdateMask(__this, DLNMEAOOHKA, large_cloth, small_cloth, nullptr);
}


bool Detour_ChatFilter_Validate(ChatFilter* __this, String* message, MethodInfo* method)
{
	bool filter = Original_ChatFilter_Validate(__this, message, method);

	for (Module* module : ModuleManager::modules)
		module->onChatFilterValidate(filter);

	return filter;
}

void Detour_GameController_FixedUpdate(GameController* __this, MethodInfo* method)
{
	for (Module* module : ModuleManager::modules)
		module->onFixedUpdate();

	return Original_GameController_FixedUpdate(__this, method);
}

bool InitHooks()
{
	bool ret = true;
	uintptr_t baseAddress = GetBaseAddress();
	std::cout << "GameAssembly.dll at " << std::hex << baseAddress << std::dec << std::endl;

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


	if (MH_CreateHook(SpriteShader_UpdateMask, Detour_SpriteShader_UpdateMask, reinterpret_cast<LPVOID*>(&Original_SpriteShader_UpdateMask)) != MH_OK)
	{
		std::cout << "Failed to Detour SpriteShader_UpdateMask" << std::endl;
		ret = false;
	}

	if (MH_CreateHook(ChatFilter_Validate, Detour_ChatFilter_Validate, reinterpret_cast<LPVOID*>(&Original_ChatFilter_Validate)) != MH_OK)
	{
		std::cout << "Failed to Detour ChatFilter_Validate" << std::endl;
		ret = false;
	}

	if (MH_CreateHook(GameController_FixedUpdate, Detour_GameController_FixedUpdate, reinterpret_cast<LPVOID*>(&Original_GameController_FixedUpdate)) != MH_OK)
	{
		std::cout << "Failed to Detour GameController_FixedUpdate" << std::endl;
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