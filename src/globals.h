#include "pch.h"
#include <vector>

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Player* g_pPlayer;
extern uintptr_t g_pMainCamera;
extern uintptr_t g_pCameraManager;

// Functions
typedef void* (__cdecl* _Camera_set_orthographicSize)(uintptr_t UnityEngine_Camera, float amount);
extern _Camera_set_orthographicSize Camera_set_orthographicSize;

typedef void* (__cdecl* _Behaviour_set_enabled)(uintptr_t __this, bool value);
extern _Behaviour_set_enabled Behaviour_set_enabled;

typedef bool (__cdecl* _Behaviour_get_enabled)(uintptr_t __this);
extern _Behaviour_get_enabled Behaviour_get_enabled;


// Hack Settings

/* movement */
extern bool g_bNoclip;
extern float g_fNoclipChange;
extern bool g_bNiggaMode;

/* view */
extern bool g_bDisableFog;
extern float g_fZoomAmount;
extern bool g_bDisablePerspectiveEditor;

extern std::vector<uintptr_t> g_aEntityList;

void InitPointers();
void LoadSettings();
