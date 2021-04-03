#include "pch.h"

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

    std::cout << "GameAssembly.dll " << g_pBaseAddress << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        g_pPlayer = *(Player**)FindDMAAddy(g_pBaseAddress + 0x3A41998, { 0x8, 0x160, 0x38 });

        // use arrow keys to increment noclip
        if (GetAsyncKeyState(VK_UP) & 1) {
            g_pPlayer->pos.y -= 1.0f;
        }
        if (GetAsyncKeyState(VK_DOWN) & 1) {
            g_pPlayer->pos.y += 1.0f;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 1) {
            g_pPlayer->pos.x += 1.0f;
        }
        if (GetAsyncKeyState(VK_LEFT) & 1) {
            g_pPlayer->pos.x -= 1.0f;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1) {
            std::cout << g_pPlayer->pos.x << std::endl;
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
