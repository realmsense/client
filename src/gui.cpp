#include "pch.h"
#include "globals.h"

#include <d3d11.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include <map>
#include <sstream>

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

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("RotMG Internal");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        // Hacks
        if (ImGui::BeginTabItem("Hacks"))
        {
            ImGui::Checkbox("Noclip", &g_bNoclip);
            ImGui::SliderFloat("Noclip Amount", &g_fNoclipChange, 1.0, 100.0);

            ImGui::EndTabItem();
        }

        // Debug
        if (ImGui::BeginTabItem("Debug"))
        {
            if (ImGui::TreeNode("Pointers"))
            {
                std::map<std::string, uintptr_t> map;
                map.insert(std::pair<std::string, uintptr_t>("g_pBaseAddress", g_pBaseAddress));
                map.insert(std::pair<std::string, uintptr_t>("g_pPlayer", *(uintptr_t*)g_pPlayer));
                for (auto const& x : map)
                {
                    std::string str1 = ptrToHex(x.second);
                    const char* str = str1.c_str();
                    ImGui::PushID(str);
                    ImGui::Text(x.first.c_str());
                    ImGui::SameLine(140);
                    ImGui::Text(str);
                    ImGui::SameLine(240);
                    if (ImGui::Button("Copy")) ImGui::SetClipboardText(str);
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    //ImGui::Checkbox("Disable Fog", &g_bDisableFog);
    //if (ImGui::SliderFloat("Zoom Amount", &g_fZoomAmount, 0.0f, 20.0f))
    //{
    //    std::cout << "Zoom Amount: " << g_fZoomAmount << std::endl;
    //
    //    if (!g_pCameraManager)
    //    {
    //        std::cout << "g_pCameraManager is nullptr!" << std::endl;
    //    }
    //    else
    //    {
    //        void* CameraManager_ZoomIn = (void*)(g_pBaseAddress + 0x15a3120);
    //    }
    //
    //    //Camera_set_orthographicSize(g_pMainCamera, g_fZoomAmount, nullptr);
    //}
    //
    //ImGui::SliderInt("AutoNexus", &g_iAutoNexusPercent, 0, 100, "%d%%");
    //
    //if (ImGui::Button("Nexus")) {
    //    INPUT inputs[2];
    //    ZeroMemory(inputs, sizeof(inputs));
    //
    //    inputs[0].type = INPUT_KEYBOARD;
    //    inputs[0].ki.wVk = 0x52;
    //
    //    inputs[1].type = INPUT_KEYBOARD;
    //    inputs[1].ki.wVk = 0x52;
    //    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    //
    //    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    //}


    //if (g_pPlayer)
    //{
    //    if (ImGui::CollapsingHeader("Player Info"))
    //    {
    //        ImGui::Text("X: %.2f", g_pPlayer->pos.x);
    //        ImGui::SameLine();
    //        ImGui::Text("Y: %.2f", g_pPlayer->pos.x);
    //
    //        ImGui::Text("HP: %i / %i", g_pPlayer->hp, g_pPlayer->maxHP);
    //        ImGui::Text("MP: %.0f / %i", g_pPlayer->mp, g_pPlayer->maxMP);
    //    }
    //}

    //RECT windowRect;
    //if (GetClientRect(g_hWindow, &windowRect) && g_pPlayer)
    //{
    //    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    //
    //    WorldToScreenPoint worldToScreenPoint = (WorldToScreenPoint)(g_pBaseAddress + 0xD6E820);
    //    Vector3 playerScreenPoint = worldToScreenPoint(g_pMainCamera, g_pPlayer->pos2);
    //
    //    for (int i = 0; i < g_aEntityList.size(); i++) {
    //        uintptr_t entity = g_aEntityList[i];
    //        float x = *(float*)(entity + 0x3C);
    //        float y = *(float*)(entity + 0x40);
    //        std::cout << x << "," << y << std::endl;
    //
    //        //Vector3 vecScreenPoint = worldToScreenPoint(g_pMainCamera, { x, y, 0.0f });
    //        //ImVec2 origin = ImVec2(playerScreenPoint.x, playerScreenPoint.y);
    //        //ImVec2 target = ImVec2(vecScreenPoint.x, vecScreenPoint.y);
    //        //draw->AddLine(origin, target, IM_COL32_BLACK, 3.0f);
    //    
    //        //float x = *(float*)(entity + 0x30);
    //        //std::cout << x << ",";
    //    }
    //
    //    //ImVec2 mousePos = ImGui::GetMousePos();
    //    //
    //    //ImVec2 origin = ImVec2(playerScreenPoint.x, playerScreenPoint.y);
    //    //ImVec2 target = mousePos;
    //    //
    //    //draw->AddLine(origin, target, IM_COL32_BLACK, 3.0f);
    //
    //    //WorldToScreenPoint screenToWorldPoint = (WorldToScreenPoint)(g_pBaseAddress + 0xd6e410);
    //    //Vector3 mouseWorldPoint = screenToWorldPoint(g_pMainCamera, { mousePos.x, mousePos.y, 0.0f });
    //}

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
