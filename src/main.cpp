#include "pch.h"
#include "il2cpp-init.h"
#include "helpers.h"
#include "gui.h"
#include "hooks.h"

#include "module/module_list.h"
#include "module/module_manager.h"

using namespace app;

void MainThread(HMODULE hModule)
{
    il2cpp_thread_attach(il2cpp_domain_get());
    CreateConsole();
    InitGui();
    ModuleManager::LoadModules();
    InitHooks();

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            std::cout << "Hello, World!" << std::endl;
        }

        // V key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            NoclipModule* noclip = ModuleManager::FindModule<NoclipModule>(ModuleList::Noclip);
            noclip->toggleModule();
        }

        static JFNHHLNJJKP* old_player = nullptr;
        JFNHHLNJJKP* player = GetPlayer();
        bool map_change = player != old_player && player != nullptr;
        for (Module* module : ModuleManager::modules)
        {
            module->onMainLoop();
            
            if (map_change)
                module->onMapChange();
        }
        old_player = player;

        CleanEnemyList();
        Sleep(5);
    }

    RemoveHooks();
    ModuleManager::UnloadModules();
    RemoveGui();
    RemoveConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);
            init_il2cpp();
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