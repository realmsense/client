#include "pch.h"

// Pointers (game objects)
uintptr_t g_pBaseAddress;
Player* g_pPlayer;

// Hack Settings
bool g_bNoclip;
bool g_bDisableFog;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
}

void LoadSettings()
{
    // TODO: load from save settings
    g_bNoclip = false;
    g_bDisableFog = true;
}
