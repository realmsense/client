#include "pch.h"
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <d3d11.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present g_oPresent = nullptr;
WNDPROC g_oWndProc = nullptr;
HWND g_hWindow = nullptr;

ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(g_oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall Detour_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static bool init = false;
    if (!init)
    {
        pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pDevice);
        if (!g_pDevice)
        {
            return g_oPresent(pSwapChain, SyncInterval, Flags);
        }

        DXGI_SWAP_CHAIN_DESC desc;
        pSwapChain->GetDesc(&desc);
        g_hWindow = desc.OutputWindow;

        g_pDevice->GetImmediateContext(&g_pContext);

        // Render Target
        ID3D11Texture2D* pBackBuffer;
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
        pBackBuffer->Release();

        g_oWndProc = (WNDPROC)SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

        // Init ImGgui
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        ImGui_ImplWin32_Init(g_hWindow);
        ImGui_ImplDX11_Init(g_pDevice, g_pContext);

        init = true;
    }
		
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return g_oPresent(pSwapChain, SyncInterval, Flags);
}

bool InitGui()
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&g_oPresent, Detour_Present);
		std::cout << "GUI Initialized" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed to initialize GUI!" << std::endl;
		return false;
	}
}

void RemoveGui()
{
    kiero::shutdown();
    SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, (LONG_PTR)g_oWndProc);
}