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
            static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
            ChatManager* chat_manager = game_controller->fields.chatManager;

            ChatSlot* chat_slot = ChatManager_GetChatMessage(chat_manager, nullptr);
            chat_slot->fields.formatted_message = (String*)il2cpp_string_new("<color=#FFFF00>Extacypls died at level 20, killed by Demon of the Abyss</color>");
            ChatManager_AddSlot(chat_manager, chat_slot, nullptr);
        }

        // V key - toggle noclip
        if (GetAsyncKeyState(0x56) & 1)
        {
            NoclipModule* noclip = ModuleManager::FindModule<NoclipModule>(ModuleList::Noclip);
            noclip->toggleModule();
        }

        static Player* old_player = nullptr;
        Player* player = GetPlayer();
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