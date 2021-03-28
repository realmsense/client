#include "pch.h"

// Pointers (game objects)
extern uintptr_t g_pBaseAddress;
extern app::ProCamera2D* g_pProCamera2D;
extern app::Camera* g_pMainCamera;

// Hack Settings
extern float zoomAmount;
extern bool disableFog;

void InitPointers();
void LoadSettings();
