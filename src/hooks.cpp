#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

typedef void* (__cdecl* _UnityThread_Update)(void* __this);
_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(void* __this)
{
    if (g_bNoclip) {
        return nullptr;
    }
    return Original_UnityThread_Update(__this);
}

typedef void* (__cdecl* TileSetColor)(void* __this, Color value);
TileSetColor Original_Tile_SetColor = nullptr;
void* Detour_Tile_SetColor(void* __this, Color value)
{
    // don't change the tile color if it is being darkened
    if (g_bDisableFog
        && (value.r != 1 || value.g != 1 || value.b != 1 || value.a != 1)
    ) {
        return nullptr;
    }

    return Original_Tile_SetColor(__this, value);
}

bool InitHooks()
{
    // TODO: Use sig scan here

    void* UnityThread_Update = (void*)(g_pBaseAddress + 0x1C0FA00);
    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour UnityThread_Update", "RotMGInternal", MB_OK);
        return false;
    }

    void* SpriteRenderer_SetColor = (void*)(g_pBaseAddress + 0xCCF0C0);
    if (MH_CreateHook(SpriteRenderer_SetColor, Detour_Tile_SetColor, reinterpret_cast<LPVOID*>(&Original_Tile_SetColor)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SpriteRenderer_SetColor", "RotMGInternal", MB_OK);
        return false;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(NULL, "Faild To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }

    return true;
}
