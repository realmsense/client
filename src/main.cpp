#include "pch.h"
#include "il2cpp-init.h"
#include "helpers.h"
#include "gui.h"

#include "module/module_list.h"
#include "module/module_manager.h"

using namespace app;

void MainThread(HMODULE hModule)
{
    il2cpp_thread_attach(il2cpp_domain_get());
    CreateConsole();
    InitGui();
    ModuleManager::LoadModules();

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            String* qualifiedName = reinterpret_cast<String*>(il2cpp_string_new("DecaGames.RotMG.Extensions.UnityThread, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null"));
            Type* unityThreadType = Type_GetType_2(qualifiedName, nullptr);

            std::cout << "Hello, World!" << std::endl;
        }

        // V key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            NoclipModule* noclip = ModuleManager::FindModule<NoclipModule>(ModuleList::Noclip);
            noclip->toggleModule();
        }
    }

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