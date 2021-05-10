#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

#include "module/module_manager.h"

_UnityThread_Update original_unity_thread_update = nullptr;

auto detour_unity_thread_update(uintptr_t __this) -> void*
{
    if (!CallEvent(ModuleEvent::UnityThread_Update, nullptr))
        return nullptr;

    return original_unity_thread_update(__this);
}

_EntityUpdate original_entity_update = nullptr;
auto detour_entity_update(Entity entity) -> void*
{
    // ignore if this is our player
    if (&entity == g_pPlayer)
    {
        return detour_entity_update(entity);
    }

    // TODO: we should probably be using one std::map?
    // to store one large entity list but the enum EntityType

    // Weird naming by DECA, but "Character" is really an enemy
    if (entity.entity_type == EntityType::Character)
    {
        g_aEnemyList.insert(&entity);
    }

    return original_entity_update(entity);
}

_Input_GetMousePos original_input_get_mouse_pos = nullptr;
auto detour_input_get_mouse_pos(uintptr_t __this) -> Vector3
{
    auto mouse_pos = original_input_get_mouse_pos(__this);

    CDataPack dp;
    dp.PackFloat(mouse_pos.x);
    dp.PackFloat(mouse_pos.y);

    CallEvent(ModuleEvent::GetMousePos, &dp);

    dp.Reset();
    mouse_pos.x = dp.ReadFloat();
    mouse_pos.y = dp.ReadFloat();
    return mouse_pos;
}

_PetUpdate original_pet_update = nullptr;

auto detour_pet_update(Entity pet, bool AMKOONDPFBD) -> void*
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

    return original_pet_update(pet, AMKOONDPFBD);
}

_SocketManager_Connect original_socket_manager_connect = nullptr;

auto detour_socket_manager_connect(uintptr_t __this, String* address, int port,
                                    String* OUTGOING_KEY,
                                    String* INCOMING_KEY) -> void
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
    
    return original_socket_manager_connect(__this, address, port, OUTGOING_KEY, INCOMING_KEY);
}

_TMP_Text_SetText_Internal original_tmp_text_set_text_internal = nullptr;

auto detour_tmp_text_set_text_internal(uintptr_t __this, String* text, bool syncTextInputBox) -> void
{
    if (text == nullptr)
        return original_tmp_text_set_text_internal(__this, text, syncTextInputBox);

    const std::string txt = ReadUnityString(text);
    CDataPack dp;
    dp.PackCell(txt.length());
    dp.PackString(txt.c_str());

    CallEvent(ModuleEvent::TMP_SetText, &dp);

    dp.Reset();
    size_t txt_len = dp.ReadCell();
    const char* txt2 = dp.ReadString(&txt_len);
    text = il2cpp_string_new(txt2);

    return original_tmp_text_set_text_internal(__this, text, syncTextInputBox);
}

_Input_GetKey original_input_get_key = nullptr;

auto detour_input_get_key(void* keyCode) -> bool
{
    if (g_bGUIBlockInputs && g_bMenuOpen)
        return false;
    else
        return original_input_get_key(keyCode);
}

_Input_GetKey original_input_get_key_down = nullptr;

auto detour_input_get_key_down(void* keyCode) -> bool
{
    if (g_bGUIBlockInputs && g_bMenuOpen)
        return false;
    else
        return original_input_get_key_down(keyCode);
}

_Map_ViewHelper_Update Original_Map_ViewHelper_Update = nullptr;
void Detour_Map_ViewHelper_Update(uintptr_t __this, int gameOpenTimeMS)
{
    g_pMapViewHelper = __this;
    return Original_Map_ViewHelper_Update(__this, gameOpenTimeMS);
}

/**
 * @brief Try to implement all of the function hooks we need with minhook
 * @return : true if all hooks initialized, false if one of the hooks failed
 */
auto init_hooks() -> bool
{
    MH_Initialize();

    // TODO: reverse all the MH_CreateHook checks and this will look 10x cleaner and more readable  // NOLINT
    // TODO: also, we probably shouldn't return FALSE if just one hook fails, either add fallbacks or disable the related module

    // TODO: Use sig scan here
    const auto UnityThread_Update = (void*)(g_pBaseAddress + OFFSET_UNITYTHREAD_UPDATE);
    if (MH_CreateHook(UnityThread_Update, detour_unity_thread_update, reinterpret_cast<LPVOID*>(&original_unity_thread_update)) != MH_OK)
    {
        // TODO: remove all of these message boxes in production and log them in debug mode

        MessageBoxA(nullptr, "Failed to Detour UnityThread_Update", "RotMGInternal", MB_OK);
        return false;
    }

    const auto EntityUpdate = (void*)(g_pBaseAddress + OFFSET_ENTITY_UPDATE);
    if (MH_CreateHook(EntityUpdate, detour_entity_update, reinterpret_cast<LPVOID*>(&original_entity_update)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour EntityUpdate", "RotMG Internal", MB_OK);
        return 1;
    }

    const auto Input_GetMousePos = (void*)(g_pBaseAddress + OFFSET_GET_MOUSEPOS);
    if (MH_CreateHook(Input_GetMousePos, detour_input_get_mouse_pos, reinterpret_cast<LPVOID*>(&original_input_get_mouse_pos)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour Input_GetMousePos", "RotMG Internal", MB_OK);
    }
    
    //void* PetUpdate = (void*)(g_pBaseAddress + OFFSET_PET_UPDATE);
    //if (MH_CreateHook(PetUpdate, Detour_PetUpdate, reinterpret_cast<LPVOID*>(&Original_PetUpdate)) != MH_OK)
    //{
    //    MessageBoxA(nullptr, "Failed to Detour PetUpdate", "RotMG Internal", MB_OK);
    //}

    const auto SocketManager_Connect = (void*)(g_pBaseAddress + OFFSET_SOCKET_MANAGER_CONNECT);
    if (MH_CreateHook(SocketManager_Connect, detour_socket_manager_connect, reinterpret_cast<LPVOID*>(&original_socket_manager_connect)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour SocketManager_Connect", "RotMG Internal", MB_OK);
        return 1;
    }

    const auto TMP_Text_SetText_Internal = (void*)(g_pBaseAddress + OFFSET_TMP_TEXT_SET_TEXT_INTERNAL);
    if (MH_CreateHook(TMP_Text_SetText_Internal, detour_tmp_text_set_text_internal, reinterpret_cast<LPVOID*>(&original_tmp_text_set_text_internal)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour TMP_Text_SetText_Internal", "RotMG Internal", MB_OK);
        return 1;
    }

    const auto Input_GetKeyDown = (void*)(g_pBaseAddress + OFFSET_GET_KEY_DOWN);
    if (MH_CreateHook(Input_GetKeyDown, detour_input_get_key_down, reinterpret_cast<LPVOID*>(&original_input_get_key_down)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour Input_GetKeyDown", "RotMG Internal", MB_OK);
        return 1;
    }

    const auto Input_GetKey = (void*)(g_pBaseAddress + OFFSET_GET_KEY);
    if (MH_CreateHook(Input_GetKey, detour_input_get_key, reinterpret_cast<LPVOID*>(&original_input_get_key)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour Input_GetKey", "RotMG Internal", MB_OK);
        return 1;
    }

    const auto Map_ViewHelper_Update = (void*)(g_pBaseAddress + OFFSET_MAP_VIEWHELPER_UPDATE);
    if (MH_CreateHook(Map_ViewHelper_Update, Detour_Map_ViewHelper_Update, reinterpret_cast<LPVOID*>(&Original_Map_ViewHelper_Update)) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed to Detour Map_ViewHelper_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(nullptr, "Failed To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }
    
    return true;
}

auto remove_hooks() -> void
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
