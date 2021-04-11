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

typedef void* (__cdecl* _GetPlayer)(Player2 __this);
_GetPlayer Original_GetPlayer = nullptr;
void* Detour_GetPlayer(Player2 player)
{
    g_pPlayer = &player;
    return Original_GetPlayer(player);
}

//typedef void* (__cdecl* _TileSetColor)(void* __this, Color value);
//_TileSetColor Original_Tile_SetColor = nullptr;
//void* Detour_Tile_SetColor(void* __this, Color value)
//{
//    // don't change the tile color if it is being darkened
//    if (g_bDisableFog
//        && (value.r != 1 || value.g != 1 || value.b != 1 || value.a != 1)
//    ) {
//        return nullptr;
//    }
//
//    return Original_Tile_SetColor(__this, value);
//}
//
//typedef void* (__cdecl* _HitDetection)(void*, void*);
//_HitDetection Original_HitDetection = nullptr;
//void* Detour_HitDetection(void* EGHLCCGKEDH, void* FLOOLAPDMHC)
//{
//    //std::cout << EGHLCCGKEDH << "," << FLOOLAPDMHC << std::endl;
//    return Original_HitDetection(EGHLCCGKEDH, FLOOLAPDMHC);
//}
//
//typedef void* (__cdecl* _CameraManagerUpdate)(void* cameraManager);
//_CameraManagerUpdate Original_CameraManager_Update = nullptr;
//void* Detour_CameraManager_Update(void* cameraManager)
//{
//    g_pCameraManager = (uintptr_t*)cameraManager;
//    return Original_CameraManager_Update(cameraManager);
//}
//
////public MiniMapObject AddDynamicObjectToMap(float EOOJAMLJAOM, float JDEKCEFBJFP, Color HNDHLEHECGE, GJLIMCBOCJG ICNKNPLOOKN) { }
//
//typedef void* (__cdecl* _AddDynamicObjectToMap)(void* __this, float x, float y, void* color, uintptr_t* entity);
//_AddDynamicObjectToMap Original_AddDynamicObjectToMap = nullptr;
//void* Detour_AddDynamicObjectToMap(void* __this, float x, float y, void* color, uintptr_t* entity)
//{
//    if (entity) {
//        float x1 = *(float*)(entity + 0x3C);
//        float y1 = *(float*)(entity + 0x40);
//        float z1 = *(float*)(entity + 0x44);
//
//        //
//        //std::cout << x << "," << y << "," << z << std::endl;
//        //g_aEntityList.push_back(entity);
//    }
//    return Original_AddDynamicObjectToMap(__this, x, y, color, entity);
//}


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
    
    void* GetPlayer = (void*)(g_pBaseAddress + OFFSET_GETPLAYER);
    if (MH_CreateHook(GetPlayer, Detour_GetPlayer, reinterpret_cast<LPVOID*>(&Original_GetPlayer)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPlayer", "RotMGInternal", MB_OK);
        return false;
    }

    //void* SpriteRenderer_SetColor = (void*)(g_pBaseAddress + 0xCCF0C0);
    //if (MH_CreateHook(SpriteRenderer_SetColor, Detour_Tile_SetColor, reinterpret_cast<LPVOID*>(&Original_Tile_SetColor)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour SpriteRenderer_SetColor", "RotMGInternal", MB_OK);
    //    return false;
    //}
    //
    ////LCGEAFDKJDM.CDKKNNAJIBG 0x1372F60
    ////boolean CDKKNNAJIBG (EGHLCCGKEDH, FLOOLAPDMHC)
    //void* HitDetection = (void*)(g_pBaseAddress + 0x1372F60);
    //if (MH_CreateHook(HitDetection, Detour_HitDetection, reinterpret_cast<LPVOID*>(&Original_HitDetection)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour HitDetection", "RotMGInternal", MB_OK);
    //    return false;
    //}
    //
    ////CameraPerspectiveEditor 0x27bd950
    //// 0x15a3120
    //void* CameraManager_Update = (void*)(g_pBaseAddress + 0x15a3120);
    //if (MH_CreateHook(CameraManager_Update, Detour_CameraManager_Update, reinterpret_cast<LPVOID*>(&Original_CameraManager_Update)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour CameraManager_Update", "RotMG Internal", MB_OK);
    //    return 1;
    //}

    //void* AddDynamicObjectToMap = (void*)(g_pBaseAddress + 0x22fd0c0);
    //if (MH_CreateHook(AddDynamicObjectToMap, Detour_AddDynamicObjectToMap, reinterpret_cast<LPVOID*>(&Original_AddDynamicObjectToMap)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour AddDynamicObjectToMap", "RotMG Internal", MB_OK);
    //    return 1;
    //}

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
