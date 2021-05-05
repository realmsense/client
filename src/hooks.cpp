#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

#include "module/module_manager.h"

_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(uintptr_t __this)
{
    if (!CallEvent(ModuleEvent::UnityThread_Update, nullptr))
        return nullptr;

    return Original_UnityThread_Update(__this);
}

_PlayerUpdate Original_PlayerUpdate = nullptr;
void* Detour_PlayerUpdate(Entity player)
{
    if (&player != g_pPlayer)
    {
        // changed map, clear stuff
        g_aEnemyList.clear();
    }

    g_pPlayer = &player;

    //std::cout << std::hex << *(uintptr_t*)&player << std::endl;
    return Original_PlayerUpdate(player);
}

_EntityUpdate Original_EntityUpdate = nullptr;
void* Detour_EntityUpdate(Entity entity)
{
    // ignore if this is our player
    if (&entity == g_pPlayer)
    {
        return Detour_EntityUpdate(entity);
    }

    // TODO: we should probably be using one std::map?
    // to store one large entity list but the enum EntityType

    // Weird naming by DECA, but "Character" is really an enemy
    if (entity.entityType == EntityType::Character)
    {
        g_aEnemyList.insert(&entity);
    }

    return Original_EntityUpdate(entity);
}

_TileSetColor Original_Tile_SetColor = nullptr;
void* Detour_Tile_SetColor(uintptr_t __this, Color value)
{
    CDataPack dp;
    dp.PackFloat(value.r);
    dp.PackFloat(value.g);
    dp.PackFloat(value.b);
    dp.PackFloat(value.a);

    if (!CallEvent(ModuleEvent::Tile_SetColor, &dp))
        return nullptr;

    dp.Reset();
    value.r = dp.ReadFloat();
    value.g = dp.ReadFloat();
    value.b = dp.ReadFloat();
    value.a = dp.ReadFloat();
    return Original_Tile_SetColor(__this, value);
}

_CameraManagerUpdate Original_CameraManager_Update = nullptr;
void* Detour_CameraManager_Update(uintptr_t cameraManager)
{
    g_pCameraManager = cameraManager;

    if (!CallEvent(ModuleEvent::CameraManager_Update, NULL))
        return nullptr;

    return Original_CameraManager_Update(cameraManager);
}

_Input_GetMousePos Original_Input_GetMousePos = nullptr;
Vector3 Detour_Input_GetMousePos(uintptr_t __this)
{
    Vector3 mousePos = Original_Input_GetMousePos(__this);

    CDataPack dp;
    dp.PackFloat(mousePos.x);
    dp.PackFloat(mousePos.y);

    CallEvent(ModuleEvent::GetMousePos, &dp);

    dp.Reset();
    mousePos.x = dp.ReadFloat();
    mousePos.y = dp.ReadFloat();
    return mousePos;
}

_PetUpdate Original_PetUpdate = nullptr;
void* Detour_PetUpdate(Entity pet, bool AMKOONDPFBD)
{
    Vector3 scale = { 1.0f, 1.0f, 1.0f };

    CDataPack dp;
    dp.PackFloat(scale.x);
    dp.PackFloat(scale.y);
    dp.PackFloat(scale.z);

    CallEvent(ModuleEvent::Pet_Update, &dp);

    dp.Reset();
    scale.x = dp.ReadFloat();
    scale.y = dp.ReadFloat();
    scale.z = dp.ReadFloat();

    uintptr_t contentTransform = (uintptr_t)pet.viewHandler->contentTransform;
    uintptr_t shadowTransform = (uintptr_t)pet.viewHandler->shadowTransform;
    Transform_set_localScale(contentTransform, scale);
    Transform_set_localScale(shadowTransform, scale);

    // TODO: Optimise this
    // we shouldn't be updating transforms every tick

    return Original_PetUpdate(pet, AMKOONDPFBD);
}

_SocketManager_Connect Original_SocketManager_Connect = nullptr;
void Detour_SocketManager_Connect(uintptr_t __this, String* address, int port, String* OUTGOING_KEY, String* INCOMING_KEY)
{
    std::string addr = ReadUnityString(address);
    CDataPack dp;
    dp.PackCell(addr.length());
    dp.PackString(addr.c_str());

    if (!CallEvent(ModuleEvent::SocketManager_Connect, &dp))
        return;

    dp.Reset();
    size_t addrLen = dp.ReadCell();
    const char* addr2 = dp.ReadString(&addrLen);
    address = il2cpp_string_new(addr2);

    // too fucking difficult to move this to a module
    // TODO: display a timer on screen with a button to skip this

    std::cout << "Connecting to " << ReadUnityString(address) << ":" << std::dec << port << std::endl;
    if (g_iReconDelay > 0)
    {
        std::cout << "Delaying for " << g_iReconDelay << " seconds..." << std::endl;
        Sleep(g_iReconDelay * 1000);
    }
    
    return Original_SocketManager_Connect(__this, address, port, OUTGOING_KEY, INCOMING_KEY);
}

_TMP_Text_SetText_Internal Original_TMP_Text_SetText_Internal = nullptr;
void Detour_TMP_Text_SetText_Internal(uintptr_t __this, String* text, bool syncTextInputBox)
{
    if (text == nullptr)
        return Original_TMP_Text_SetText_Internal(__this, text, syncTextInputBox);
    
    std::string txt = ReadUnityString(text);
    CDataPack dp;
    dp.PackCell(txt.length());
    dp.PackString(txt.c_str());

    CallEvent(ModuleEvent::TMP_SetText, &dp);

    dp.Reset();
    size_t txtLen = dp.ReadCell();
    const char* txt2 = dp.ReadString(&txtLen);
    text = il2cpp_string_new(txt2);

    return Original_TMP_Text_SetText_Internal(__this, text, syncTextInputBox);
}

_Input_GetKey Original_Input_GetKey = nullptr;
bool Detour_Input_GetKey(void* keyCode)
{
    if (g_bGUIBlockInputs && g_bMenuOpen)
        return false;
    else
        return Original_Input_GetKey(keyCode);
}

_Input_GetKey Original_Input_GetKeyDown = nullptr;
bool Detour_Input_GetKeyDown(void* keyCode)
{
    if (g_bGUIBlockInputs && g_bMenuOpen)
        return false;
    else
        return Original_Input_GetKeyDown(keyCode);
}

bool InitHooks()
{
    MH_Initialize();

    //// TODO: Use sig scan here
    void* UnityThread_Update = (void*)(g_pBaseAddress + OFFSET_UNITYTHREAD_UPDATE);
    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour UnityThread_Update", "RotMGInternal", MB_OK);
        return false;
    }
    
    void* PlayerUpdate = (void*)(g_pBaseAddress + OFFSET_PLAYER_UPDATE);
    if (MH_CreateHook(PlayerUpdate, Detour_PlayerUpdate, reinterpret_cast<LPVOID*>(&Original_PlayerUpdate)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour PlayerUpdate", "RotMGInternal", MB_OK);
        return false;
    }
    
    void* EntityUpdate = (void*)(g_pBaseAddress + OFFSET_ENTITY_UPDATE);
    if (MH_CreateHook(EntityUpdate, Detour_EntityUpdate, reinterpret_cast<LPVOID*>(&Original_EntityUpdate)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour EntityUpdate", "RotMG Internal", MB_OK);
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
    
    void* Input_GetMousePos = (void*)(g_pBaseAddress + OFFSET_GET_MOUSEPOS);
    if (MH_CreateHook(Input_GetMousePos, Detour_Input_GetMousePos, reinterpret_cast<LPVOID*>(&Original_Input_GetMousePos)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour Input_GetMousePos", "RotMG Internal", MB_OK);
        return 1;
    }
    
    //void* PetUpdate = (void*)(g_pBaseAddress + OFFSET_PET_UPDATE);
    //if (MH_CreateHook(PetUpdate, Detour_PetUpdate, reinterpret_cast<LPVOID*>(&Original_PetUpdate)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour PetUpdate", "RotMG Internal", MB_OK);
    //    return 1;
    //}
    
    void* SocketManager_Connect = (void*)(g_pBaseAddress + OFFSET_SOCKET_MANAGER_CONNECT);
    if (MH_CreateHook(SocketManager_Connect, Detour_SocketManager_Connect, reinterpret_cast<LPVOID*>(&Original_SocketManager_Connect)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SocketManager_Connect", "RotMG Internal", MB_OK);
        return 1;
    }

    void* TMP_Text_SetText_Internal = (void*)(g_pBaseAddress + OFFSET_TMP_TEXT_SET_TEXT_INTERNAL);
    if (MH_CreateHook(TMP_Text_SetText_Internal, Detour_TMP_Text_SetText_Internal, reinterpret_cast<LPVOID*>(&Original_TMP_Text_SetText_Internal)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour TMP_Text_SetText_Internal", "RotMG Internal", MB_OK);
        return 1;
    }
    
    void* Input_GetKeyDown = (void*)(g_pBaseAddress + OFFSET_GET_KEY_DOWN);
    if (MH_CreateHook(Input_GetKeyDown, Detour_Input_GetKeyDown, reinterpret_cast<LPVOID*>(&Original_Input_GetKeyDown)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour Input_GetKeyDown", "RotMG Internal", MB_OK);
        return 1;
    }
    
    void* Input_GetKey = (void*)(g_pBaseAddress + OFFSET_GET_KEY);
    if (MH_CreateHook(Input_GetKey, Detour_Input_GetKey, reinterpret_cast<LPVOID*>(&Original_Input_GetKey)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour Input_GetKey", "RotMG Internal", MB_OK);
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
