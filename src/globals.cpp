#include "pch.h"
#include <unordered_set>

// Pointers (game objects)
uintptr_t g_pBaseAddress;
Entity* g_pPlayer;
NBJLMDOACBC* g_pNBJLMDOACBC; // TODO: think of a name for this
uintptr_t g_pMainCamera;
uintptr_t g_pCameraManager;
uintptr_t g_pIdleWatcher;

// Functions
_Camera_set_orthographicSize Camera_set_orthographicSize;
_Behaviour_get_enabled Behaviour_get_enabled;
_Behaviour_set_enabled Behaviour_set_enabled;
_Component_GetGameObject Component_GetGameObject;
_Object_GetName Object_GetName;
_GameObject_Find GameObject_Find;
_GameObject_GetTransform GameObject_GetTransform;
_GameObject_GetActive GameObject_GetActive;
_GameObject_SetActive GameObject_SetActive;
_Transform_Find Transform_Find;
_Transform_GetChild Transform_GetChild;
_Transform_get_childCount Transform_get_childCount;
_Transform_get_position Transform_get_position;
_Transform_set_position Transform_set_position;
_Transform_get_localScale Transform_get_localScale;
_Transform_set_localScale Transform_set_localScale;
_WorldToScreen WorldToScreen;
_ScreenToWorld ScreenToWorld;
_SetVsync SetVsync;
_SetFpsTarget SetFpsTarget;

// Variables / Settings
bool g_bWindowFocused;
bool g_bMenuOpen;
std::unordered_set<Entity*> g_aEnemyList;
std::vector<Entity*> g_aPlayerList;

/* autos */
bool g_bAutoAim;
AutoAimTarget g_AutoAimTarget;

/* movement */
float g_fNoclipChange;
float g_fWalkAmount;

/* meme */
bool g_bNiggaMode;

/* view */
bool g_bDisableFog;
float g_fZoomAmount;
bool g_bDisablePerspectiveEditor;
float g_fPlayerSize;
bool g_bHideTiles;
bool g_bHidePets;
bool g_bShowFps;

/* other */
bool g_bDisableAfkKicker;
int g_iReconDelay;

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
    Component_GetGameObject = (_Component_GetGameObject)(g_pBaseAddress + OFFSET_COMPONENT_GET_GAMEOBJECT);
    Object_GetName = (_Object_GetName)(g_pBaseAddress + OFFSET_OBJECT_GET_NAME);
    GameObject_Find = (_GameObject_Find)(g_pBaseAddress + OFFSET_GAMEOBJECT_FIND);
    GameObject_GetTransform = (_GameObject_GetTransform)(g_pBaseAddress + OFFSET_GAMEOBJECT_GET_TRANSFORM);
    GameObject_GetActive = (_GameObject_GetActive)(g_pBaseAddress + OFFSET_GAMEOBJECT_GET_ACTIVE);
    GameObject_SetActive = (_GameObject_SetActive)(g_pBaseAddress + OFFSET_GAMEOBJECT_SET_ACTIVE);
    Transform_Find = (_Transform_Find)(g_pBaseAddress + OFFSET_TRANSFORM_FIND);
    Transform_GetChild = (_Transform_GetChild)(g_pBaseAddress + OFFSET_TRANSFORM_GET_CHILD);
    Transform_get_childCount = (_Transform_get_childCount)(g_pBaseAddress + OFFSET_TRANSFORM_GET_CHILD_COUNT);
    Transform_get_position = (_Transform_get_position)(g_pBaseAddress + OFFSET_TRANSFORM_GET_POSITION);
    Transform_set_position = (_Transform_set_position)(g_pBaseAddress + OFFSET_TRANSFORM_SET_POSITION);
    Transform_get_localScale = (_Transform_get_localScale)(g_pBaseAddress + OFFSET_TRANSFORM_GET_LOCAL_SCALE);
    Transform_set_localScale = (_Transform_set_localScale)(g_pBaseAddress + OFFSET_TRANSFORM_SET_LOCAL_SCALE);
    WorldToScreen = (_WorldToScreen)(g_pBaseAddress + OFFSET_WORLD_TO_SCREEN);
    ScreenToWorld = (_ScreenToWorld)(g_pBaseAddress + OFFSET_SCREEN_TO_WORLD);
    SetVsync = (_SetVsync)(g_pBaseAddress + OFFSET_SET_VSYNC);
    SetFpsTarget = (_SetFpsTarget)(g_pBaseAddress + OFFSET_SET_FPS_TARGET);
}

void LoadSettings()
{

    // TODO: load from save settings

    g_bMenuOpen = true;

    /* autos */
    g_bAutoAim = false;
    g_AutoAimTarget = AutoAimTarget::ClosestPos;

    /* movement */
    g_fNoclipChange = 1.0f;
    g_fWalkAmount = 2.0f;

    /* meme */
    g_bNiggaMode = false;

    /* view */
    g_bDisableFog = true;
    g_fZoomAmount = 7.2f;
    g_bDisablePerspectiveEditor = true;
    g_fPlayerSize = 1.0f;
    g_bHideTiles = false;
    g_bHidePets = false;
    g_bShowFps = false;

    /* other */
    g_bDisableAfkKicker = true;
    g_iReconDelay = 0;

    /* debug */
    g_bEnemyTracers = false;
    g_bEnemyNames = false;
}
