#include "pch.h"

#include "globals.h"
#include "gui.h"
#include "hooks.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

DWORD WINAPI MainThread(HMODULE hModule)
{
    CreateConsole();
    InitGui();
    InitPointers();
    InitHooks();
    LoadSettings();

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        if (g_bNoclip && g_pPlayer)
        {
            if (GetAsyncKeyState(0x57)) g_pPlayer->pos.y -= 0.01 * g_fNoclipChange; // w - up
            if (GetAsyncKeyState(0x41)) g_pPlayer->pos.x -= 0.01 * g_fNoclipChange; // a - left
            if (GetAsyncKeyState(0x53)) g_pPlayer->pos.y += 0.01 * g_fNoclipChange; // s - down
            if (GetAsyncKeyState(0x44)) g_pPlayer->pos.x += 0.01 * g_fNoclipChange; // d - right
        }

        static bool niggmode = false;
        if (GetAsyncKeyState(VK_INSERT) & 1) {
        
            niggmode = !niggmode;
            if (niggmode)
            {
                g_bNoclip = true;
                //g_fNoclipChange = 50.0f;
                PlaySound(TEXT("C:\\Users\\Extacy\\source\\repos\\RotMG-Internal\\x64\\Debug\\picture_cut.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            else
            {
                g_bNoclip = false;
                //g_fNoclipChange = 1.0f;
                PlaySound(NULL, NULL, SND_ASYNC);
            }
        }

        if (GetAsyncKeyState(VK_DELETE) & 1) {
            //String* string;
            //string->length = 1;
            //string->value[0] = L'\x48';
            //
            //Notification_MACCMNMIHPN notification;
            //notification.Message_HMDIOGPMABE = string;
            //notification.ObjectID_LADFHJEFKEC
        
            //notification.Mess;age_HMDIOGPMABE = "";
        }

        if (GetAsyncKeyState(VK_SPACE) & 1) {
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
