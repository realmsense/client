#include "pch.h"

#include "gui.h"
#include "hooks.h"
#include "module/module_list.h"
#include "module/module_manager.h"

void UpdatePointers()
{
    // static objects, only set once (DontDestroyOnLoad)
    if (!g_pCameraManager)
        g_pCameraManager = (CameraManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.CameraManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");

    // dynamic objects
    if (g_pCameraManager)
    {
        g_pMainCamera = (uintptr_t)g_pCameraManager->main_camera;
        g_pPlayer = g_pCameraManager->N00000A56->player;
    }

    static Entity* old_player = g_pPlayer;
    if (g_pPlayer != old_player && g_pPlayer != nullptr)
    {
        CallEvent(ModuleEvent::MapChange, NULL);
        old_player = g_pPlayer;
    }
}

void MainThread(HMODULE hModule)
{
    CreateConsole();
    InitPointers();
    InitHooks();
    LoadSettings();
    LoadModules();
    InitGui();

    // TODO: Exit if hooks are not succesfully initialized

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

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            CameraManager* cameraManager = (CameraManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.CameraManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            Entity* player = cameraManager->N00000A56->player;
            std::string player_name = ReadUnityString(player->name);
            std::cout << player_name << std::endl;
        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            //
        }

        // v key - toggle noclip
        // TODO: replace with a key config and keycode enum
        if (GetAsyncKeyState(0x56) & 1)
        {
            static auto* noclip_module = GetModule<NoclipModule>(ModuleList::Noclip);
            noclip_module->toggleModule();
        }

        CallEvent(ModuleEvent::MainLoop, nullptr);
        Sleep(5);
    }

    RemoveConsole();
    RemoveHooks();
    UnloadModules();
    RemoveGui();
    FreeLibraryAndExitThread(hModule, 0);
    return;
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
