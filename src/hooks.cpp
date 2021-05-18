#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

#include "module/module_manager.h"

_UnityThread_Update Original_UnityThread_Update = nullptr;
void Detour_UnityThread_Update(uintptr_t __this)
{
    if (!CallEvent(ModuleEvent::UnityThread_Update, nullptr))
        return;

    return Original_UnityThread_Update(__this);
}

_EntityUpdate Original_Entity_Update = nullptr;
void Detour_Entity_Update(Entity entity)
{
    // TODO: probably a list of entities somewhere. maybe a static field

    // ignore if this is our player
    if (&entity == g_pPlayer)
    {
        return Detour_Entity_Update(entity);
    }

    // TODO: we should probably be using one std::map?
    // to store one large entity list but the enum EntityType

    // Weird naming by DECA, but "Character" is really an enemy
    if (entity.entity_type == EntityType::Character)
    {
        g_aEnemyList.insert(&entity);
    }

    return Original_Entity_Update(entity);
}

_Input_GetMousePos Original_Input_Get_Mouse_Pos = nullptr;
Vector3 Detour_Input_Get_Mouse_Pos(uintptr_t __this)
{
    Vector3 mouse_pos = Original_Input_Get_Mouse_Pos(__this);

    CDataPack dp;
    dp.PackFloat(mouse_pos.x);
    dp.PackFloat(mouse_pos.y);

    CallEvent(ModuleEvent::GetMousePos, &dp);

    dp.Reset();
    mouse_pos.x = dp.ReadFloat();
    mouse_pos.y = dp.ReadFloat();
    return mouse_pos;
}

_PetUpdate Original_Pet_Update = nullptr;
void Detour_Pet_Update(Entity pet, bool AMKOONDPFBD)
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

    // try to use auto if you're casting, line looks cleaner with no duplicates
    auto content_transform = (uintptr_t)pet.view_handler->content_transform;
    auto shadow_transform = (uintptr_t)pet.view_handler->shadow_transform;
    Transform_set_localScale(content_transform, scale);
    Transform_set_localScale(shadow_transform, scale);

    // TODO: Optimise this
    // we shouldn't be updating transforms every tick

    return Original_Pet_Update(pet, AMKOONDPFBD);
}

_SocketManager_Connect Original_SocketManager_Connect = nullptr;
void Detour_SocketManager_Connect(uintptr_t __this, String* address, int port, String* OUTGOING_KEY, String* INCOMING_KEY)
{
    const std::string addr = ReadUnityString(address);
    CDataPack dp;
    dp.PackCell(addr.length());
    dp.PackString(addr.c_str());

    if (!CallEvent(ModuleEvent::SocketManager_Connect, &dp))
        return;

    dp.Reset();
    size_t addr_len = dp.ReadCell();
    const char* addr2 = dp.ReadString(&addr_len);
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

_TMP_Text_SetText_Internal Original_TMP_Text_Set_Text_Internal = nullptr;
auto Detour_TMP_Text_Set_Text_Internal(uintptr_t __this, String* text, bool syncTextInputBox) -> void
{
    if (text == nullptr)
        return Original_TMP_Text_Set_Text_Internal(__this, text, syncTextInputBox);

    const std::string txt = ReadUnityString(text);
    CDataPack dp;
    dp.PackCell(txt.length());
    dp.PackString(txt.c_str());

    CallEvent(ModuleEvent::TMP_SetText, &dp);

    dp.Reset();
    size_t txt_len = dp.ReadCell();
    const char* txt2 = dp.ReadString(&txt_len);
    text = il2cpp_string_new(txt2);

    return Original_TMP_Text_Set_Text_Internal(__this, text, syncTextInputBox);
}

_Input_GetKey Original_Input_GetKey = nullptr;
bool Detour_Input_GetKey(int keyCode)
{
    CDataPack dp;
    dp.PackCell(keyCode);

    if (!CallEvent(ModuleEvent::GetKeyDown, &dp))
        return false;

    dp.Reset();
    keyCode = dp.ReadCell();
    return Original_Input_GetKey(keyCode);
}

_Input_GetKey Original_Input_Get_Key_Down = nullptr;
bool Detour_Input_Get_Key_Down(int keyCode)
{
    CDataPack dp;
    dp.PackCell(keyCode);

    if (!CallEvent(ModuleEvent::GetKeyDown, &dp))
        return false;

    dp.Reset();
    keyCode = dp.ReadCell();
    return Original_Input_Get_Key_Down(keyCode);
}

_Map_ViewHelper_Update Original_Map_ViewHelper_Update = nullptr;
void Detour_Map_ViewHelper_Update(uintptr_t __this, int gameOpenTimeMS)
{
    g_pMapViewHelper = __this;
    return Original_Map_ViewHelper_Update(__this, gameOpenTimeMS);
}

bool InitHooks()
{
    MH_Initialize();

    bool ret = true;

    void* UnityThread_Update = (void*)(g_pBaseAddress + OFFSET_UNITYTHREAD_UPDATE);
    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        std::cout << "Failed to Detour UnityThread_Update" << std::endl;
        ret = false;
    }

    void* EntityUpdate = (void*)(g_pBaseAddress + OFFSET_ENTITY_UPDATE);
    if (MH_CreateHook(EntityUpdate, Detour_Entity_Update, reinterpret_cast<LPVOID*>(&Original_Entity_Update)) != MH_OK)
    {
        std::cout << "Failed to Detour EntityUpdate" << std::endl;
        ret = false;
    }

    void* Input_GetMousePos = (void*)(g_pBaseAddress + OFFSET_GET_MOUSEPOS);
    if (MH_CreateHook(Input_GetMousePos, Detour_Input_Get_Mouse_Pos, reinterpret_cast<LPVOID*>(&Original_Input_Get_Mouse_Pos)) != MH_OK)
    {
        std::cout << "Failed to Detour Input_GetMousePos" << std::endl;
        ret = false;
    }
    
    void* SocketManager_Connect = (void*)(g_pBaseAddress + OFFSET_SOCKET_MANAGER_CONNECT);
    if (MH_CreateHook(SocketManager_Connect, Detour_SocketManager_Connect, reinterpret_cast<LPVOID*>(&Original_SocketManager_Connect)) != MH_OK)
    {
        std::cout << "Failed to Detour SocketManager_Connect" << std::endl;
        ret = false;
    }

    void* TMP_Text_SetText_Internal = (void*)(g_pBaseAddress + OFFSET_TMP_TEXT_SET_TEXT_INTERNAL);
    if (MH_CreateHook(TMP_Text_SetText_Internal, Detour_TMP_Text_Set_Text_Internal, reinterpret_cast<LPVOID*>(&Original_TMP_Text_Set_Text_Internal)) != MH_OK)
    {
        std::cout << "Failed to Detour TMP_Text_SetText_Internal" << std::endl;
        ret = false;
    }

    void* Input_GetKey = (void*)(g_pBaseAddress + OFFSET_GET_KEY);
    if (MH_CreateHook(Input_GetKey, Detour_Input_GetKey, reinterpret_cast<LPVOID*>(&Original_Input_GetKey)) != MH_OK)
    {
        std::cout << "Failed to Detour Input_GetKey" << std::endl;
        ret = false;
    }

    void* Input_GetKeyDown = (void*)(g_pBaseAddress + OFFSET_GET_KEY_DOWN);
    if (MH_CreateHook(Input_GetKeyDown, Detour_Input_Get_Key_Down, reinterpret_cast<LPVOID*>(&Original_Input_Get_Key_Down)) != MH_OK)
    {
        std::cout << "Failed to Detour Input_GetKeyDown" << std::endl;
        ret = false;
    }

    void* Map_ViewHelper_Update = (void*)(g_pBaseAddress + OFFSET_MAP_VIEWHELPER_UPDATE);
    if (MH_CreateHook(Map_ViewHelper_Update, Detour_Map_ViewHelper_Update, reinterpret_cast<LPVOID*>(&Original_Map_ViewHelper_Update)) != MH_OK)
    {
        std::cout << "Failed to Detour Map_ViewHelper_Update" << std::endl;
        ret = false;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        std::cout << "Failed to activate hooks" << std::endl;
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
