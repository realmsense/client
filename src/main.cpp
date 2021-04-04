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
    LoadSettings();

    std::cout << "GameAssembly.dll " << g_pBaseAddress << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        g_pPlayer = *(Player**)FindDMAAddy(g_pBaseAddress + 0x3A41998, { 0x8, 0x160, 0x38 });

        if (g_bNoclip && g_pPlayer)
        {
            float change = 0.01f;
            if (GetAsyncKeyState(0x57)) g_pPlayer->pos.y -= change; // w - up
            if (GetAsyncKeyState(0x41)) g_pPlayer->pos.x -= change; // a - left
            if (GetAsyncKeyState(0x53)) g_pPlayer->pos.y += change; // s - down
            if (GetAsyncKeyState(0x44)) g_pPlayer->pos.x += change; // d - right
        }

        if (GetAsyncKeyState(VK_SPACE) & 1) {
            g_bNoclip = !g_bNoclip;
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
