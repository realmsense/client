#include "pch.h"
#include "il2cpp-init.h"
#include "helpers.h"
#include "gui.h"

using namespace app;

DWORD WINAPI MainThread(const HMODULE hModule)
{
    il2cpp_thread_attach(il2cpp_domain_get());
    CreateConsole();
    InitGui();

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
    }

    RemoveGui();
    RemoveConsole();
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