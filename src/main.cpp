#include "pch.h"

#include "gui.h"
#include "hooks.h"
#include "module/module_list.h"
#include "module/module_manager.h"

#include <sstream>

void UpdatePointers()
{
    // static objects, (DontDestroyOnLoad)
    if (!g_pCameraManager)
        g_pCameraManager = (CameraManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.CameraManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");

    // dynamic objects
    if (g_pCameraManager)
    {
        g_pMainCamera = (uintptr_t)g_pCameraManager->main_camera;
        g_pPlayer = g_pCameraManager->N00000A56->player;
    }
}

DWORD WINAPI MainThread(const HMODULE hModule)
{
    CreateConsole();
    InitPointers();
    init_hooks();
    LoadSettings();
    LoadModules();
    InitGui();

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        // ` - toggle menu
        if (GetAsyncKeyState(VK_OEM_3) & 1)
        {
            g_bMenuOpen = !g_bMenuOpen;
        }

        // Remove enemies that no longer exist - https://stackoverflow.com/a/15662547
        for (auto it = g_aEnemyList.begin(); it != g_aEnemyList.end();)
        {
            Entity* enemy = *it;
            if (!enemy->alive)
                it = g_aEnemyList.erase(it);
            else
                // we are incrementing an incrementor while looping inside a loop here
                // if we postfix instead of prefix 
                ++it;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            uintptr_t obj = FindObjectByQualifiedName("CharacterGUIInfoSection, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            std::cout << std::hex << obj << std::endl;

            //String* player_QualifiedName = il2cpp_string_new("JFNHHLNJJKP, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            //uintptr_t player_Type = System_GetType(player_QualifiedName);
            //uintptr_t player_Obj = Object_FindObjectOfType(player_Type);
            //std::cout << std::hex << player_Obj << std::endl;
        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {

        }

        // v key - toggle noclip
        // TODO: replace with a key config and keycode enum
        if (GetAsyncKeyState(0x56) & 1)
        {
            static auto* noclip_module = GetModule<NoclipModule>(ModuleList::Noclip);
            noclip_module->toggleModule();
        }

        // keep all module main functions running by calling every 4ms (game tick speed)
        CallEvent(ModuleEvent::MainLoop, nullptr);
        UpdatePointers();
        Sleep(4);
    }

    RemoveConsole();
    remove_hooks();
    UnloadModules();
    RemoveGui();
    FreeLibraryAndExitThread(hModule, 0);
    return TRUE;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);

            HANDLE main_thread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
            if (main_thread) CloseHandle(main_thread);
        }
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        default:
            return FALSE;
    }
    return TRUE;
}
