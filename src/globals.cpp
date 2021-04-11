#include "pch.h"
#include <vector>

// Pointers (game objects)
uintptr_t g_pBaseAddress;
Player* g_pPlayer;
uintptr_t g_pMainCamera;
uintptr_t g_pCameraManager;

// Functions
_Camera_set_orthographicSize Camera_set_orthographicSize;
_Behaviour_get_enabled Behaviour_get_enabled;
_Behaviour_set_enabled Behaviour_set_enabled;

// Hack Settings

/* movement */
bool g_bNoclip;
float g_fNoclipChange;
bool g_bNiggaMode;

/* view */
bool g_bDisableFog;
float g_fZoomAmount;
bool g_bDisablePerspectiveEditor;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");

    GetMainCamera getMainCamera = (GetMainCamera)(g_pBaseAddress + OFFSET_GET_MAINCAMERA);
    g_pMainCamera = getMainCamera();

    Camera_set_orthographicSize = (_Camera_set_orthographicSize)(g_pBaseAddress + OFFSET_SET_ORTHOGRAPHICSIZE);
    Behaviour_get_enabled = (_Behaviour_get_enabled)(g_pBaseAddress + OFFSET_BEHAVIOUR_GET_ENABLED);
    Behaviour_set_enabled = (_Behaviour_set_enabled)(g_pBaseAddress + OFFSET_BEHAVIOUR_SET_ENABLED);
}

void LoadSettings()
{
    // TODO: load from save settings

    /* movement */
    g_bNoclip = false;
    g_fNoclipChange = 1.0f;
    g_bNiggaMode = false;

    /* view */
    g_bDisableFog = true;
    g_fZoomAmount = 7.2f;
    g_bDisablePerspectiveEditor = true;
}
