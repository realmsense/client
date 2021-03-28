#include "pch.h"
#include "il2cpp-helpers.h"
#include <iostream>

using namespace app;

// Pointers (game objects)
uintptr_t g_pBaseAddress;
ApplicationManager* g_pApplicationManager;
CameraManager* g_pCameraManager;
ProCamera2D* g_pProCamera2D;
Camera* g_pMainCamera;

// Hack Settings
float zoomAmount;
bool disableFog;
bool disablePerspectiveEditor;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = il2cppi_get_base_address();

    g_pProCamera2D = ProCamera2D_get_Instance(nullptr);
    g_pMainCamera = g_pProCamera2D->fields.GameCamera;
}

void LoadSettings()
{
    // TODO: load from save settings
    zoomAmount = 7.2f;
    disableFog = false;
    disablePerspectiveEditor = false;
}
