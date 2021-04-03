#include <windows.h>
#include <iostream>

#include "globals.h"
#include "helpers.h"
#include "gui.h"
#include "hooks.h"

// Custom injected code entry point
DWORD WINAPI MainThread(HMODULE hModule)
{
    CreateConsole();
    InitGui();
    InitPointers();
    InitHooks();

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            std::cout << "yuh" << std::endl;
        }

        Sleep(5);
    }
    
    RemoveConsole();
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
            HANDLE mainThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
            if (mainThread) CloseHandle(mainThread);
        }
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
