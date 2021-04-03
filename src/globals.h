#include "pch.h"

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Player* g_pPlayer;

// Hack Settings
extern bool g_bNoclip;
extern bool g_bDisableFog;

void InitPointers();
void LoadSettings();
