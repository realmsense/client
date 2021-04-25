#include "pch.h"

#include "gui.h"
#include "hooks.h"
#include "module/module_list.h"
#include "module/module_manager.h"

#include <sstream>

DWORD WINAPI MainThread(HMODULE hModule)
{
    CreateConsole();
    InitPointers();
    InitHooks();
    LoadSettings();
    LoadModules();
    InitGui();

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

        if (g_pNBJLMDOACBC)
        {
            std::vector<Entity*> playerList = ReadUnityList<Entity*>(g_pNBJLMDOACBC->playerList);

            // added - local is not in global
            for (auto& player : playerList)
            {
                if (!player) continue;

                bool exists = std::find(g_aPlayerList.begin(), g_aPlayerList.end(), player) != g_aPlayerList.end();
                if (!exists)
                {
                    Vector3 newScale = { g_fPlayerSize, g_fPlayerSize, 1.0f };
                    uintptr_t contentTransform = (uintptr_t)player->viewHandler->contentTransform;
                    Transform_set_localScale(contentTransform, newScale);
                }
            }

            // removed - global is not in local
            //for (auto& player : g_aPlayerList)
            //{
            //    bool exists = std::find(playerList.begin(), playerList.end(), player) != playerList.end();
            //    if (!exists)
            //    {
            //        // can't update transform here
            //        // todo: we need to update our player's transform when we load into a new map
            //        std::cout << "Player was removed " << ReadUnityString(player->name) << std::endl;
            //    }
            //}

            g_aPlayerList = playerList;
        }

        // Ignore keybinds if window isn't focused
        if (!g_bWindowFocused)
        {
            continue;
        }

        static bool walk = false;
        static float oldSpeed;

        // LShift Pressed - turn on walk
        if (GetAsyncKeyState(VK_LSHIFT) < 0 && !walk)
        {
            std::cout << "Walk Enabled" << std::endl;
            walk = true;
            oldSpeed = g_pPlayer->speed;
            g_pPlayer->speed /= g_fWalkAmount;
        }

        // LShift Released - reset speed
        if (GetAsyncKeyState(VK_LSHIFT) == 0 && walk)
        {
            std::cout << "Walk Disabled" << std::endl;
            walk = false;
            g_pPlayer->speed = oldSpeed;
        }

        // ` - toggle menu
        if (GetAsyncKeyState(VK_OEM_3) & 1)
        {
            g_bMenuOpen = !g_bMenuOpen;
        }

        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {

        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            //std::cout << std::hex << g_pPlayer->viewHandler << std::endl;


            //std::cout << std::hex << gameObject << std::endl;

           // g_pPlayer->viewHandler->gameObject
        }

        // v key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            static Module* noclipModule = GetModule(ModuleList::NoclipModule);
            noclipModule->toggleModule();
        }

        CallEvent(ModuleEvent::MainLoop, nullptr);

        Sleep(5);
    }

    RemoveConsole();
    RemoveHooks();
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
