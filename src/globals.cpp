#include "pch.h"
#include <unordered_set>

// Pointers (game objects)
uintptr_t g_pBaseAddress;
Entity* g_pPlayer;
NBJLMDOACBC* g_pNBJLMDOACBC; // TODO: think of a name for this
uintptr_t g_pMainCamera;
uintptr_t g_pCameraManager;

// Functions
_Camera_set_orthographicSize Camera_set_orthographicSize;
_Behaviour_get_enabled Behaviour_get_enabled;
_Behaviour_set_enabled Behaviour_set_enabled;
_Transform_get_localScale Transform_get_localScale;
_Transform_set_localScale Transform_set_localScale;
_WorldToScreen WorldToScreen;
_ScreenToWorld ScreenToWorld;

// Variables / Settings
bool g_bWindowFocused;
bool g_bMenuOpen;
std::unordered_set<Entity*> g_aEnemyList;
std::vector<Entity*> g_aPlayerList;

/* autos */
bool g_bAutoAim;
AutoAimTarget g_AutoAimTarget;

/* movement */
bool g_bNoclip;
float g_fNoclipChange;

/* meme */
bool g_bNiggaMode;

/* view */
bool g_bDisableFog;
float g_fZoomAmount;
bool g_bDisablePerspectiveEditor;
float g_fPlayerSize;

/* debug */
bool g_bEnemyTracers;
bool g_bEnemyNames;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = (uintptr_t)GetModuleHandle(L"GameAssembly.dll");

    _GetMainCamera getMainCamera = (_GetMainCamera)(g_pBaseAddress + OFFSET_GET_MAINCAMERA);
    g_pMainCamera = getMainCamera();

    Camera_set_orthographicSize = (_Camera_set_orthographicSize)(g_pBaseAddress + OFFSET_SET_ORTHOGRAPHICSIZE);
    Behaviour_get_enabled = (_Behaviour_get_enabled)(g_pBaseAddress + OFFSET_BEHAVIOUR_GET_ENABLED);
    Behaviour_set_enabled = (_Behaviour_set_enabled)(g_pBaseAddress + OFFSET_BEHAVIOUR_SET_ENABLED);
    Transform_get_localScale = (_Transform_get_localScale)(g_pBaseAddress + OFFSET_TRANSFORM_GET_LOCAL_SCALE);
    Transform_set_localScale = (_Transform_set_localScale)(g_pBaseAddress + OFFSET_TRANSFORM_SET_LOCAL_SCALE);
    WorldToScreen = (_WorldToScreen)(g_pBaseAddress + OFFSET_WORLD_TO_SCREEN);
    ScreenToWorld = (_ScreenToWorld)(g_pBaseAddress + OFFSET_SCREEN_TO_WORLD);
}

void LoadSettings()
{

    // TODO: load from save settings

    g_bMenuOpen = true;

    /* autos */
    g_bAutoAim = true;
    g_AutoAimTarget = AutoAimTarget::ClosestPos;

    /* movement */
    g_bNoclip = false;
    g_fNoclipChange = 1.0f;

    /* meme */
    g_bNiggaMode = false;

    /* view */
    g_bDisableFog = true;
    g_fZoomAmount = 7.2f;
    g_bDisablePerspectiveEditor = true;
    g_fPlayerSize = 1.0f;

    /* debug */
    g_bEnemyTracers = false;
    g_bEnemyNames = false;
}
