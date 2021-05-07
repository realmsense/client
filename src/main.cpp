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
        if (GetAsyncKeyState(VK_END) & 1)
        {
            break;
        }

        // ` - toggle menu
        if (GetAsyncKeyState(VK_OEM_3) & 1)
        {
            g_bMenuOpen = !g_bMenuOpen;
        }

        // Remove enemies that no longer exist - https://stackoverflow.com/a/15662547
        for (auto it = g_aEnemyList.begin(); it != g_aEnemyList.end();)
        {
            Entity* enemy = *it;
            if (!enemy->alive)
                it = g_aEnemyList.erase(it);
            else
                it++;
        }

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            uintptr_t obj = FindObjectByQualifiedName("CharacterGUIInfoSection, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            std::cout << std::hex << obj << std::endl;

            //String* player_QualifiedName = il2cpp_string_new("JFNHHLNJJKP, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            //uintptr_t player_Type = System_GetType(player_QualifiedName);
            //uintptr_t player_Obj = Object_FindObjectOfType(player_Type);
            //std::cout << std::hex << player_Obj << std::endl;
        }

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {

        }

        // v key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            static NoclipModule* noclipModule = GetModule<NoclipModule>(ModuleList::Noclip);
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
