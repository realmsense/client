#include "pch.h"
#include <vector>

// Pointers (game objects)
uintptr_t g_pBaseAddress;
Player2* g_pPlayer;
uintptr_t* g_pMainCamera;
uintptr_t* g_pCameraManager;

// Functions
//Camera_set_orthographicSize camera_set_orthographicSize;

// Hack Settings
bool g_bNoclip;
bool g_bDisableFog;
bool g_bNiggaMode;
float g_fZoomAmount;
float g_fNoclipChange;
int g_iAutoNexusPercent;

std::vector<uintptr_t> g_aEntityList;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");

    GetMainCamera getMainCamera = (GetMainCamera)(g_pBaseAddress + OFFSET_GET_MAINCAMERA);
    g_pMainCamera = getMainCamera();
}

void LoadSettings()
{
    // TODO: load from save settings
    g_bNoclip = false;
    g_bDisableFog = true;
    g_fZoomAmount = 7.2f;
    g_fNoclipChange = 1.0f;
    g_iAutoNexusPercent = 10;
}
