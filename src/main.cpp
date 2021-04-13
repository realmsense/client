#include "pch.h"

#include "globals.h"
#include "gui.h"
#include "hooks.h"

#include <sstream>

DWORD WINAPI MainThread(HMODULE hModule)
{
    CreateConsole();
    InitGui();
    InitPointers();
    InitHooks();
    LoadSettings();

    while (true)
    {
        // Remove enemies that no longer exist - https://stackoverflow.com/a/15662547
        for (auto it = g_aEnemyList.begin(); it != g_aEnemyList.end();)
        {
            Entity* enemy = *it;
            if (!enemy->alive)
                it = g_aEnemyList.erase(it);
            else
                it++;
        }

        // Ignore keybinds if window isn't focused
        if (!g_bWindowFocused)
        {
            continue;
        }

        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (g_bNoclip && g_pPlayer)
        {
            if (GetAsyncKeyState(0x57)) g_pPlayer->pos.y -= 0.01f * g_fNoclipChange; // w - up
            if (GetAsyncKeyState(0x41)) g_pPlayer->pos.x -= 0.01f * g_fNoclipChange; // a - left
            if (GetAsyncKeyState(0x53)) g_pPlayer->pos.y += 0.01f * g_fNoclipChange; // s - down
            if (GetAsyncKeyState(0x44)) g_pPlayer->pos.x += 0.01f * g_fNoclipChange; // d - right
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {

        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {

        }

        // v key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            g_bNoclip = !g_bNoclip;
        }

        Sleep(5);
    }

    RemoveConsole();
    RemoveHooks();
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
