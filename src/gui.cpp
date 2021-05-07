#include "pch.h"
#include "globals.h"

#include "module/module_manager.h"

#include <d3d11.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <map>
#include <sstream>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
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

    g_bWindowFocused = GetForegroundWindow() == g_hWindow;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    const char* category_names[] = {
        "View",         // ModuleCategory::VIEW
        "Movement",     // ModuleCategory::MOVEMENT
        "Auto",         // ModuleCategory::AUTO
        "Other"         // ModuleCategory::OTHER
    };

    for (int i = 0; i < (int)ModuleCategory::Count; i++)
    {
        const char* category_name = category_names[i];
        ImGui::Begin(category_name);

        ModuleCategory module_category = ModuleCategory(i);
        std::vector<Module*> modules = GetModules(module_category);

        for (auto module : modules)
        {
            if (!module->intialized) continue;

            const char* module_name = module->name.c_str();
            ImGui::PushID(module_name);

            if (ImGui::Checkbox("", &module->enabled))
                module->toggleModule(module->enabled);

            const ImVec2 checkboxSize = ImGui::GetItemRectSize();

            ImGui::SameLine();

            if (!module->hasGuiElements)
            {
                ImGui::CollapsingHeader(module_name, ImGuiTreeNodeFlags_Leaf);
            }
            else
            {
                if (ImGui::CollapsingHeader(module_name))
                {
                    ImGui::Indent(checkboxSize.x + 5.0f);
                    module->renderGUI();
                    ImGui::Unindent(checkboxSize.x + 5.0f);
                }
            }

            ImGui::PopID();
        }

        ImGui::End();
    }

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
