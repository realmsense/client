#include "pch.h"

#include <windows.h>
#include <iostream>

#include <d3d11.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "globals.h"

using namespace app;

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present g_oPresent = nullptr;
HWND g_hWindow = nullptr;
WNDPROC oWndProc = nullptr;

ID3D11Device* pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall Detour_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static bool init = false;
    if (!init)
    {
        pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice);
        if (!pDevice)
        {
            return g_oPresent(pSwapChain, SyncInterval, Flags);
        }

        DXGI_SWAP_CHAIN_DESC desc;
        pSwapChain->GetDesc(&desc);
        g_hWindow = desc.OutputWindow;

        pDevice->GetImmediateContext(&g_pContext);

        // Render Target
        ID3D11Texture2D* pBackBuffer;
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
        pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
        pBackBuffer->Release();

        oWndProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

        // Init ImGgui
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        ImGui_ImplWin32_Init(g_hWindow);
        ImGui_ImplDX11_Init(pDevice, g_pContext);

        init = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("RotMG Internal");
    ImGui::Text("Hello World!");

    if (ImGui::SliderFloat("Zoom Amount", &zoomAmount, 0.0f, 20.0f))
    {
        std::cout << "Zoom Amount: " << zoomAmount << std::endl;
        Camera_set_orthographicSize(g_pMainCamera, zoomAmount, nullptr);
    }

    if (ImGui::Checkbox("Perspective Editor", &disablePerspectiveEditor))
    {
        if (!g_pCameraManager)
        {
            std::cout << "g_pCameraManager is nullptr" << std::endl;
        }
        else
        {
            CameraPerspectiveEditor* cameraPerspectiveEditor = g_pCameraManager->fields.OOJJDIANIBF;
            Behaviour_set_enabled(reinterpret_cast<Behaviour*>(cameraPerspectiveEditor), disablePerspectiveEditor, nullptr);
            std::cout << "CameraPerspectiveEditor: " << disablePerspectiveEditor << std::endl;
        }
    }

    ImGui::Checkbox("Disable Fog", &disableFog);

    static float hue = 1.0f;
    static float speed = 0.0035f;
    hue += speed;
    if (hue > 360.0f) hue = 1.0f;
    ImColor rainbow = ImColor::HSV(hue, 1.0f, 1.0f);

    RECT windowRect;
    if (GetClientRect(g_hWindow, &windowRect)) {
        Vector3 playerPos;
        playerPos.x = g_pProCamera2D->fields.BKGIPAJPNPF;
        playerPos.y = g_pProCamera2D->fields.EJEMLBMNAKC;
        playerPos.z = 0.0f;

        // Camera Offset (pressing x)
        Transform* transform = Component_1_get_transform(reinterpret_cast<Component_1*>(g_pMainCamera), nullptr);
        Vector3 localPlayerPos = Transform_get_localPosition(transform, nullptr);
        playerPos.y += localPlayerPos.y * 2;

        Vector3 playerScreenPos = Camera_WorldToScreenPoint_1(g_pMainCamera, playerPos, nullptr);

        ImVec2 origin;
        origin.x = playerScreenPos.x;
        origin.y = playerScreenPos.y;

        ImVec2 target = ImGui::GetMousePos();

        ImDrawList* draw = ImGui::GetBackgroundDrawList();
        draw->AddLine((origin), target, rainbow, 3.0f);
    }

    ImGui::End();
    ImGui::Render();

    g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return g_oPresent(pSwapChain, SyncInterval, Flags);
}

bool InitGui()
{
    if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
    {
        kiero::bind(8, (void**)& g_oPresent, Detour_Present);
        std::cout << "GUI Initialized" << std::endl;
        return true;
    } else {
        std::cout << "Failed to initialize GUI!" << std::endl;
        return false;
    }
}

void RemoveGui()
{
    kiero::shutdown();
    SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}
