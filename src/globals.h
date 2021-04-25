#pragma once

#include "pch.h"

void InitPointers();
void LoadSettings();

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Entity* g_pPlayer;
extern NBJLMDOACBC* g_pNBJLMDOACBC;
extern uintptr_t g_pMainCamera;
extern uintptr_t g_pCameraManager;
extern uintptr_t g_pIdleWatcher;

// Functions
extern _Camera_set_orthographicSize Camera_set_orthographicSize;
extern _Behaviour_set_enabled Behaviour_set_enabled;
extern _Behaviour_get_enabled Behaviour_get_enabled;
extern _Component_GetGameObject Component_GetGameObject;
extern _Object_GetName Object_GetName;
extern _GameObject_Find GameObject_Find;
extern _GameObject_GetTransform GameObject_GetTransform;
extern _GameObject_GetActive GameObject_GetActive;
extern _GameObject_SetActive GameObject_SetActive;
extern _Transform_Find Transform_Find;
extern _Transform_GetChild Transform_GetChild;
extern _Transform_get_childCount Transform_get_childCount;
extern _Transform_get_position Transform_get_position;
extern _Transform_set_position Transform_set_position;
extern _Transform_get_localScale Transform_get_localScale;
extern _Transform_set_localScale Transform_set_localScale;
extern _WorldToScreen WorldToScreen;
extern _ScreenToWorld ScreenToWorld;
extern _SetVsync SetVsync;
extern _SetFpsTarget SetFpsTarget;

// Variables / Settings
extern bool g_bWindowFocused;
extern bool g_bMenuOpen;
extern std::unordered_set<Entity*> g_aEnemyList;
extern std::vector<Entity*> g_aPlayerList;

/* movement */
extern float g_fWalkAmount;

/* view */
extern bool g_bDisableFog;
extern float g_fZoomAmount;
extern bool g_bDisablePerspectiveEditor;
extern float g_fPlayerSize;
extern bool g_bHideTiles;
extern bool g_bHidePets;
extern bool g_bShowFps;

/* other */
extern bool g_bDisableAfkKicker;
extern int g_iReconDelay;

/* debug */
extern bool g_bEnemyTracers;
extern bool g_bEnemyNames;
