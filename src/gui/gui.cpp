#include "pch.h"
#include "gui.h"
#include "module/module_manager.h"

#include "thirdparty/kiero/kiero.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_win32.h"
#include "thirdparty/imgui/imgui_impl_dx11.h"

#include <d3d11.h>

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present g_oPresent = nullptr;
WNDPROC g_oWndProc = nullptr;
HWND g_hWindow = nullptr;

ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

void GUI_WrapInLoop(int i, int length)
{
    ImGuiStyle& style = ImGui::GetStyle();
    float window_visible_x = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    float button_size_x = ImGui::GetItemRectSize().x;
    float pos_x = ImGui::GetItemRectMax().x;
    float next_x = pos_x + style.ItemSpacing.x + button_size_x;
    bool wrap_next = i + 1 < length && next_x < window_visible_x;
    if (wrap_next)
        ImGui::SameLine();
}

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

    //ImGui::ShowDemoWindow();

    if (g_bGuiOpen)
    {
        const char* category_names[] = {
            "View",         // ModuleCategory::VIEW
            "Movement",     // ModuleCategory::MOVEMENT
            "Auto",         // ModuleCategory::AUTO
            "Other"         // ModuleCategory::OTHER
        };

        for (int i = 0; i < (int)ModuleCategory::Count; i++)
        {
            ModuleCategory category = ModuleCategory(i);
            const char* category_name = category_names[i];

            ImGui::Begin(category_name);
            for (Module* module : ModuleManager::modules)
            {
                if (!module->initialized) continue;
                if (module->category != category) continue;

                const char* module_name = module->name.c_str();
                ImGui::PushID(module_name);

                if (ImGui::Checkbox("", &module->enabled))
                    module->setEnabled(module->enabled, true);

                const ImVec2 checkboxSize = ImGui::GetItemRectSize();
                ImGui::SameLine();
                if (!module->has_gui_elements)
                {
                    // Empty header
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