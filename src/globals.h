#include "pch.h"
#include <vector>

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern Player2* g_pPlayer;
extern uintptr_t* g_pMainCamera;
extern uintptr_t* g_pCameraManager;

// Functions
extern Camera_set_orthographicSize camera_set_orthographicSize;

// Hack Settings
extern bool g_bNoclip;
extern bool g_bNiggaMode;
extern float g_fNoclipChange;
extern bool g_bDisableFog;
extern float g_fZoomAmount;
extern int g_iAutoNexusPercent;

extern std::vector<uintptr_t> g_aEntityList;

void InitPointers();
void LoadSettings();
