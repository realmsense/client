#include "pch.h"

// Pointers (game objects)
uintptr_t g_pBaseAddress;

// Hack Settings

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
}

void LoadSettings()
{
    // TODO: load from save settings
}
