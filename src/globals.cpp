#include "pch.h"
#include "il2cpp-helpers.h"

// Pointers (game objects)
uintptr_t g_pBaseAddress;
app::ProCamera2D* g_pProCamera2D;
app::Camera* g_pMainCamera;

// Hack Settings
float zoomAmount;
bool disableFog;

void InitPointers()
{
    // Load pointers we can get easily from functions
    // The remaining pointers will be set from detoured functions
    g_pBaseAddress = il2cppi_get_base_address();
    g_pProCamera2D = app::ProCamera2D_get_Instance(nullptr);
    g_pMainCamera = g_pProCamera2D->fields.GameCamera;
}

void LoadSettings()
{
    // TODO: load from save settings
    zoomAmount = 7.2f;
    disableFog = true;
}
