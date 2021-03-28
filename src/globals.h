#include "pch.h"

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern app::ApplicationManager* g_pApplicationManager;
extern app::ProCamera2D* g_pProCamera2D;
extern app::CameraManager* g_pCameraManager;
extern app::Camera* g_pMainCamera;

// Hack Settings
extern float zoomAmount;
extern bool disableFog;
extern bool disablePerspectiveEditor;

void InitPointers();
void LoadSettings();
