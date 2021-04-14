#include "pch.h"
#include <unordered_set>

void InitPointers();
void LoadSettings();


// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Entity* g_pPlayer;
extern uintptr_t g_pMainCamera;
extern uintptr_t g_pCameraManager;

// Functions
extern _Camera_set_orthographicSize Camera_set_orthographicSize;
extern _Behaviour_set_enabled Behaviour_set_enabled;
extern _Behaviour_get_enabled Behaviour_get_enabled;
extern _WorldToScreen WorldToScreen;
extern _ScreenToWorld ScreenToWorld;

// Variables / Settings
extern bool g_bWindowFocused;
extern std::unordered_set<Entity*> g_aEnemyList;

/* autos */
extern bool g_bAutoAim;

/* movement */
extern bool g_bNoclip;
extern float g_fNoclipChange;
extern bool g_bNiggaMode;

/* view */
extern bool g_bDisableFog;
extern float g_fZoomAmount;
extern bool g_bDisablePerspectiveEditor;

/* debug */
extern bool g_bEnemyTracers;
extern bool g_bEnemyNames;
