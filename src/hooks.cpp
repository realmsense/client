#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

typedef void* (__cdecl* _UnityThread_Update)(uintptr_t __this);
_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(uintptr_t __this)
{
    if (g_bNoclip) {
        return nullptr;
    }
    return Original_UnityThread_Update(__this);
}

typedef void* (__cdecl* _GetPlayer)(Entity __this);
_GetPlayer Original_GetPlayer = nullptr;
void* Detour_GetPlayer(Entity player)
{
    if (&player != g_pPlayer)
    {
        // changed map, clear stuff
        g_aEnemyList.clear();
    }

    g_pPlayer = &player;
    
    //std::cout << std::hex << *(uintptr_t*)&player << std::endl;
    return Original_GetPlayer(player);
}

typedef void* (__cdecl* _GetEnemy)(Entity enemy);
_GetEnemy Original_GetEnemy = nullptr;
void* Detour_GetEnemy(Entity enemy)
{
    if (&enemy == g_pPlayer)
    {
        return Original_GetEnemy(enemy);
    }

    // Probably incorrect naming by DECA
    if (enemy.entityType == EntityType::Character)
    {
        g_aEnemyList.insert(&enemy);
    }

    return Original_GetEnemy(enemy);
}

typedef void* (__cdecl* _TileSetColor)(uintptr_t __this, Color value);
_TileSetColor Original_Tile_SetColor = nullptr;
void* Detour_Tile_SetColor(uintptr_t __this, Color value)
{
    // don't change the tile color if it is being darkened
    if (g_bDisableFog
        && (value.r != 1 || value.g != 1 || value.b != 1 || value.a != 1)
    ) {
        return nullptr;
    }

    return Original_Tile_SetColor(__this, value);
}

typedef void* (__cdecl* _CameraManagerUpdate)(uintptr_t cameraManager);
_CameraManagerUpdate Original_CameraManager_Update = nullptr;
void* Detour_CameraManager_Update(uintptr_t cameraManager)
{
    g_pCameraManager = cameraManager;

    uintptr_t cameraPerspectiveEditor = *(uintptr_t*)(g_pCameraManager + 0x48); // OOJJDIANIBF
    g_bDisablePerspectiveEditor = Behaviour_get_enabled(cameraPerspectiveEditor);

    return Original_CameraManager_Update(cameraManager);
}


typedef void* (__cdecl* _Add_Dynamic_Object)(uintptr_t __this, float x, float y, Color color, uintptr_t entity);
_Add_Dynamic_Object Original_Add_Dynamic_Object = nullptr;
void* Detour_Add_Dynamic_Object(uintptr_t __this, float x, float y, Color color, uintptr_t entity)
{
    if (entity)
    {
        std::cout << x << "," << y << std::endl;
        std::cout << color.r << "," << color.g << "," << color.b << std::endl;
        std::cout << std::hex << entity << std::endl;
        std::cout << std::endl;
    }

    return Original_Add_Dynamic_Object(__this, x, y, color, entity);
}

bool InitHooks()
{
    MH_Initialize();

    // TODO: Use sig scan here
    void* UnityThread_Update = (void*)(g_pBaseAddress + OFFSET_UNITYTHREAD_UPDATE);
    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour UnityThread_Update", "RotMGInternal", MB_OK);
        return false;
    }
    
    void* GetPlayer = (void*)(g_pBaseAddress + OFFSET_GET_PLAYER);
    if (MH_CreateHook(GetPlayer, Detour_GetPlayer, reinterpret_cast<LPVOID*>(&Original_GetPlayer)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPlayer", "RotMGInternal", MB_OK);
        return false;
    }

    void* GetEnemy = (void*)(g_pBaseAddress + OFFSET_GET_ENEMY);
    if (MH_CreateHook(GetEnemy, Detour_GetEnemy, reinterpret_cast<LPVOID*>(&Original_GetEnemy)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetEnemy", "RotMG Internal", MB_OK);
        return 1;
    }

    void* SpriteRenderer_SetColor = (void*)(g_pBaseAddress + OFFSET_SPRITE_SET_COLOR);
    if (MH_CreateHook(SpriteRenderer_SetColor, Detour_Tile_SetColor, reinterpret_cast<LPVOID*>(&Original_Tile_SetColor)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SpriteRenderer_SetColor", "RotMGInternal", MB_OK);
        return false;
    }

    void* CameraManager_Update = (void*)(g_pBaseAddress + OFFSET_CAMERAMANAGER_UPDATE);
    if (MH_CreateHook(CameraManager_Update, Detour_CameraManager_Update, reinterpret_cast<LPVOID*>(&Original_CameraManager_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour CameraManager_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(NULL, "Faild To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }

    return true;
}

void RemoveHooks()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
