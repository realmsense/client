#include "pch.h"
#include <unordered_set>

void InitPointers();
void LoadSettings();

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Entity* g_pPlayer;
extern NBJLMDOACBC* g_pNBJLMDOACBC;
extern uintptr_t g_pMainCamera;
extern uintptr_t g_pCameraManager;

// Functions
extern _Camera_set_orthographicSize Camera_set_orthographicSize;
extern _Behaviour_set_enabled Behaviour_set_enabled;
extern _Behaviour_get_enabled Behaviour_get_enabled;
extern _Transform_get_localScale Transform_get_localScale;
extern _Transform_set_localScale Transform_set_localScale;
extern _WorldToScreen WorldToScreen;
extern _ScreenToWorld ScreenToWorld;

// Variables / Settings
extern bool g_bWindowFocused;
extern bool g_bMenuOpen;
extern std::unordered_set<Entity*> g_aEnemyList;
extern std::vector<Entity*> g_aPlayerList;

/* autos */
extern bool g_bAutoAim;
extern AutoAimTarget g_AutoAimTarget;

/* movement */
extern bool g_bNoclip;
extern float g_fNoclipChange;

/* meme */
extern bool g_bNiggaMode;

/* view */
extern bool g_bDisableFog;
extern float g_fZoomAmount;
extern bool g_bDisablePerspectiveEditor;
extern float g_fPlayerSize;
extern bool g_bHidePets;

/* debug */
extern bool g_bEnemyTracers;
extern bool g_bEnemyNames;
