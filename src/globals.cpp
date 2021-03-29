#include "pch.h"
#include "il2cpp-helpers.h"
#include <iostream>

using namespace app;

// Pointers (game objects)
uintptr_t g_pBaseAddress;
ApplicationManager* g_pApplicationManager;
GameController* g_pGameController;
CameraManager* g_pCameraManager;
ProCamera2D* g_pProCamera2D;
Camera* g_pMainCamera;

// Hack Settings
float g_fZoomAmount;
bool g_bDisableFog;
bool g_bDisablePerspectiveEditor;
bool g_bNoclip;
int g_iNoclipInterval;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = il2cppi_get_base_address();

    g_pApplicationManager = MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager__get_instance(*MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager__get_instance__MethodInfo);
    g_pGameController = ApplicationManager_get_GameController(g_pApplicationManager, nullptr);

    g_pProCamera2D = ProCamera2D_get_Instance(nullptr);
    g_pMainCamera = g_pProCamera2D->fields.GameCamera;
}

void LoadSettings()
{
    // TODO: load from save settings
    g_fZoomAmount = 7.2f;
    g_bDisableFog = false;
    g_bDisablePerspectiveEditor = false;
    g_bNoclip = false;
    g_iNoclipInterval = 100;
}
