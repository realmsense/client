#include "pch.h"

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern app::ApplicationManager* g_pApplicationManager;
extern app::GameController* g_pGameController;
extern app::ProCamera2D* g_pProCamera2D;
extern app::CameraManager* g_pCameraManager;
extern app::Camera* g_pMainCamera;

// Hack Settings
extern float g_fZoomAmount;
extern bool g_bDisableFog;
extern bool g_bDisablePerspectiveEditor;
extern bool g_bNoclip;

void InitPointers();
void LoadSettings();
