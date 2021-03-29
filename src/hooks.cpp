#include "pch.h"
#include "il2cpp-helpers.h"
#include <iostream>
#include "minhook/include/MinHook.h"
#include "globals.h"

using namespace app;

//DO_APP_FUNC(0x02124A40, void, SpriteRenderer_set_color, (SpriteRenderer * __this, Color value, MethodInfo * method));
typedef void* (__cdecl* TileSetColor)(SpriteRenderer* __this, Color value, MethodInfo* method);
TileSetColor Original_Tile_SetColor = nullptr;
void* Detour_Tile_SetColor(SpriteRenderer* __this, Color value, MethodInfo* method)
{
    // don't change the tile color if it is being darkened
    if (g_bDisableFog
        && (value.r != 1 || value.g != 1 || value.b != 1 || value.a != 1)
    ) {
        return nullptr;
    }

    return Original_Tile_SetColor(__this, value, method);
}

//DO_APP_FUNC(0x002DC7B0, void, CameraManager_Update, (CameraManager * __this, MethodInfo * method));
typedef void* (__cdecl* CameraManagerUpdate)(CameraManager* __this, MethodInfo* method);
CameraManagerUpdate Original_CameraManager_Update = nullptr;
void* Detour_CameraManager_Update(CameraManager* __this, MethodInfo* method)
{
    if (g_pCameraManager == nullptr)
    {
        g_pCameraManager = __this;
    }
    return Original_CameraManager_Update(__this, method);
}

//DO_APP_FUNC(0x008D6CA0, void, UnityThread_Update, (UnityThread * __this, MethodInfo * method));
typedef void* (__cdecl* _UnityThread_Update)(UnityThread* __this, MethodInfo* method);
_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(UnityThread* __this, MethodInfo* method)
{
    if (g_bNoclip)
    {
        return nullptr;
    }
    return Original_UnityThread_Update(__this, method);
}

bool InitHooks()
{
    if (MH_CreateHook(SpriteRenderer_set_color, Detour_Tile_SetColor, reinterpret_cast<LPVOID*>(&Original_Tile_SetColor)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SpriteRenderer_set_color", "RotMGInternal", MB_OK);
        return false;
    }

    if (MH_CreateHook(CameraManager_Update, Detour_CameraManager_Update, reinterpret_cast<LPVOID*>(&Original_CameraManager_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour CameraManager_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour UnityThread_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(NULL, "Faild To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }

    return true;
}
