#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

#include "module/module_manager.h"

typedef void* (__cdecl* _UnityThread_Update)(uintptr_t __this);
_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(uintptr_t __this)
{
    if (!CallEvent(ModuleEvent::UnityThread_Update, nullptr))
        return nullptr;

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

typedef void* (__cdecl* _GetEntity)(Entity entity);
_GetEntity Original_GetEntity = nullptr;
void* Detour_GetEntity(Entity entity)
{
    // ignore if this is our player
    if (&entity == g_pPlayer)
    {
        return Detour_GetEntity(entity);
    }

    // TODO: we should probably be using one std::map?
    // to store one large entity list but the enum EntityType

    // Weird naming by DECA, but "Character" is really an enemy
    if (entity.entityType == EntityType::Character)
    {
        g_aEnemyList.insert(&entity);
    }

    return Original_GetEntity(entity);
}

typedef void* (__cdecl* _TileSetColor)(uintptr_t __this, Color value);
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

typedef void* (__cdecl* _CameraManagerUpdate)(uintptr_t cameraManager);
_CameraManagerUpdate Original_CameraManager_Update = nullptr;
void* Detour_CameraManager_Update(uintptr_t cameraManager)
{
    g_pCameraManager = cameraManager;

    if (!CallEvent(ModuleEvent::CameraManager_Update, NULL))
        return nullptr;

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

typedef Vector3 (__cdecl* _Input_GetMousePos)(uintptr_t __this);
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

//typedef void*(__cdecl* _SocketManager_SendMessage)(uintptr_t __this, uintptr_t packet);
//_SocketManager_SendMessage Original_SocketManager_SendMessage = nullptr;
//void* Detour_SocketManager_SendMessage(uintptr_t __this, uintptr_t packet)
//{
//    int packetId = *(int*)(packet + 0x18);
//    if (g_bNoclip
//        && packetId == 42 // move
//    ) {
//        return nullptr;
//    }
//
//    return Original_SocketManager_SendMessage(__this, packet);
//}

typedef void* (__cdecl* _GetPlayerList)(NBJLMDOACBC __this, int EGHLCCGKEDH);
_GetPlayerList Original_GetPlayerList = nullptr;
void* Detour_GetPlayerList(NBJLMDOACBC __this, int EGHLCCGKEDH)
{
    g_pNBJLMDOACBC = &__this;
    return Original_GetPlayerList(__this, EGHLCCGKEDH);
}

typedef void* (__cdecl* _GetPet)(Entity pet, bool AMKOONDPFBD);
_GetPet Original_GetPet = nullptr;
void* Detour_GetPet(Entity pet, bool AMKOONDPFBD)
{
    // TODO: optimise this
    Vector3 newScale;
    if (g_bHidePets)
        newScale = { 0.0f, 0.0f, 1.0f };
    else
        newScale = { 1.0f, 1.0f, 1.0f };
    
    uintptr_t contentTransform = (uintptr_t)pet.viewHandler->contentTransform;
    Transform_set_localScale(contentTransform, newScale);

    return Original_GetPet(pet, AMKOONDPFBD);
}

typedef void* (__cdecl* _IdleWatcher_Update)(uintptr_t __this);
_IdleWatcher_Update Original_IdleWatcher_Update = nullptr;
void* Detour_IdleWatcher_Update(uintptr_t __this)
{
    g_pIdleWatcher = __this;

    std::cout << std::hex << __this << std::endl;

    if (g_bDisableAfkKicker)
        Behaviour_set_enabled(__this, false);

    return Original_IdleWatcher_Update(__this);
}

typedef void* (__cdecl* _SocketManager_Connect)(uintptr_t __this, String address, int port, String OUTGOING_KEY, String INCOMING_KEY);
_SocketManager_Connect Original_SocketManager_Connect = nullptr;
void* Detour_SocketManager_Connect(uintptr_t __this, String address, int port, String OUTGOING_KEY, String INCOMING_KEY)
{
    std::cout << "Connecting to " << ReadUnityString(&address) << ":" << port << std::endl;

    if (g_iReconDelay > 0)
    {
        std::cout << "Delaying for " << g_iReconDelay << " seconds..." << std::endl;
        Sleep(g_iReconDelay * 1000);
    }
    
    return Original_SocketManager_Connect(__this, address, port, OUTGOING_KEY, INCOMING_KEY);
}

typedef void(__cdecl* _TMP_Text_SetText_Internal)(uintptr_t __this, String* text, bool syncTextInputBox);
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

    void* GetEntity = (void*)(g_pBaseAddress + OFFSET_GET_ENEMY);
    if (MH_CreateHook(GetEntity, Detour_GetEntity, reinterpret_cast<LPVOID*>(&Original_GetEntity)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetEntity", "RotMG Internal", MB_OK);
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

    //void* SocketManager_SendMessage = (void*)(g_pBaseAddress + OFFSET_SOCKET_SENDMESSAGE);
    //if (MH_CreateHook(SocketManager_SendMessage, Detour_SocketManager_SendMessage, reinterpret_cast<LPVOID*>(&Original_SocketManager_SendMessage)) != MH_OK)
    //{
    //    MessageBoxA(NULL, "Failed to Detour SocketManager_SendMessage", "RotMG Internal", MB_OK);
    //    return 1;
    //}

    void* GetPlayerList = (void*)(g_pBaseAddress + OFFSET_GET_PLAYER_LIST);
    if (MH_CreateHook(GetPlayerList, Detour_GetPlayerList, reinterpret_cast<LPVOID*>(&Original_GetPlayerList)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPlayerList", "RotMG Internal", MB_OK);
        return 1;
    }
    
    void* GetPet = (void*)(g_pBaseAddress + OFFSET_GET_PET);
    if (MH_CreateHook(GetPet, Detour_GetPet, reinterpret_cast<LPVOID*>(&Original_GetPet)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPet", "RotMG Internal", MB_OK);
        return 1;
    }

    void* IdleWatcher_Update = (void*)(g_pBaseAddress + OFFSET_IDLE_WATCHER_UPDATE);
    if (MH_CreateHook(IdleWatcher_Update, Detour_IdleWatcher_Update, reinterpret_cast<LPVOID*>(&Original_IdleWatcher_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour IdleWatcher_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    void* SocketManager_Connect = (void*)(g_pBaseAddress + OFFSET_SOCKET_CONNECT);
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
