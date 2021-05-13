// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "il2cpp-appdata.h"
#include "il2cpp-init.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "helpers.h"

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

// Custom injected code entry point

DWORD WINAPI MainThread(const HMODULE hModule)
{
    // Initialize thread data - DO NOT REMOVE
    il2cpp_thread_attach(il2cpp_domain_get());

    // If you would like to write to a log file, specify the name above and use il2cppi_log_write()
    // il2cppi_log_write("Startup");

    // If you would like to output to a new console window, use il2cppi_new_console() to open one and redirect stdout
    // il2cppi_new_console();

    // Place your custom code here

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