#include "pch.h"
#include "globals.h"

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

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowCollapsed(!g_bMenuOpen);
    g_bMenuOpen = ImGui::Begin("RotMG Internal");

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MainTabBar", tab_bar_flags))
    {
        // Hacks
        if (ImGui::BeginTabItem("Hacks"))
        {
            if (ImGui::BeginTabBar("HacksTabBar", tab_bar_flags))
            {
                if (ImGui::BeginTabItem("Autos"))
                {
                    ImGui::Checkbox("Auto Aim", &g_bAutoAim);

                    const char* aim_targets[] =
                    {
                        "Closest to Mouse",     // AutoAimTarget::ClosestMouse
                        "Closest to Player",    // AutoAimTarget::ClosestPos
                        "Highest Defense",      // AutoAimTarget::HighestDef
                        "Highest Max HP (Boss)" // AutoAimTarget::HighestMaxHP
                    };
                    static int selected_target = 1;

                    ImGui::SetNextItemWidth(ImGui::GetTextLineHeightWithSpacing() * strlen(aim_targets[3]) / 2); // set width to the widest string

                    if (ImGui::Combo("Auto Aim Target", &selected_target, aim_targets, IM_ARRAYSIZE(aim_targets), IM_ARRAYSIZE(aim_targets)))
                    {
                        g_AutoAimTarget = AutoAimTarget(selected_target);
                        std::cout << g_AutoAimTarget << " " << aim_targets[selected_target] << std::endl;
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Movement"))
                {
                    ImGui::Checkbox("Noclip", &g_bNoclip);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("View"))
                {
                    ImGui::Checkbox("Disable Fog", &g_bDisableFog);

                    if (ImGui::SliderFloat("Zoom Amount", &g_fZoomAmount, 0.0f, 20.0f))
                    {
                        if (g_pMainCamera)
                            Camera_set_orthographicSize(g_pMainCamera, g_fZoomAmount);
                    }

                    if (ImGui::Checkbox("Perspective Editor", &g_bDisablePerspectiveEditor))
                    {
                        if (g_pCameraManager)
                        {
                            uintptr_t cameraPerspectiveEditor = *(uintptr_t*)(g_pCameraManager + 0x48); // OOJJDIANIBF
                            Behaviour_set_enabled(cameraPerspectiveEditor, g_bDisablePerspectiveEditor);
                            std::cout << "CameraPerspectiveEditor: " << g_bDisablePerspectiveEditor << std::endl;
                        }
                    }

                    ImGui::SliderFloat("Player Size", &g_fPlayerSize, 0.0f, 1.0f);
                    // Only update transforms after the slider is released, to prevent the game crashing from too many updates
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        for (auto& player : g_aPlayerList)
                        {
                            Vector3 newScale = { g_fPlayerSize, g_fPlayerSize, 1.0f };
                            uintptr_t contentTransform = (uintptr_t)player->viewHandler->contentTransform;
                            Transform_set_localScale(contentTransform, newScale);
                        }
                    }

                    ImGui::Checkbox("Hide pets", &g_bHidePets);

                    static bool unlimitedFPS = false;
                    if (ImGui::Checkbox("Unlimited FPS", &unlimitedFPS))
                    {
                        if (unlimitedFPS)
                        {
                            SetVsync(0);
                            SetFpsTarget(999);
                        }
                        else
                        {
                            SetVsync(1);
                        }
                    }

                    ImGui::EndTabItem();
                }
                
                ImGui::EndTabBar();
            }

            ImGui::EndTabItem();
        }

        // Meme
        if (ImGui::BeginTabItem(":realtrollblack:"))
        {
            static bool niggmode = false;
            if (ImGui::Checkbox("nigga mode", &niggmode))
            {
                if (niggmode)
                {
                    g_bNoclip = true;
                    g_fNoclipChange = 77.7f;
                    PlaySound(TEXT("C:\\Users\\Extacy\\Desktop\\picture_cut.wav"), NULL, SND_FILENAME | SND_ASYNC);
                }
                else
                {
                    g_bNoclip = false;
                    g_fNoclipChange = 1.0f;
                    PlaySound(NULL, NULL, SND_ASYNC);
                }
            }

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
                map.insert(std::pair<std::string, uintptr_t>("g_pCameraManager", g_pCameraManager));
                map.insert(std::pair<std::string, uintptr_t>("g_pMainCamera", g_pMainCamera));
                map.insert(std::pair<std::string, uintptr_t>("g_pPlayer", reinterpret_cast<uintptr_t>(g_pPlayer)));
                for (auto &ptr : map)
                {
                    std::string ptrHex = PtrToHex(ptr.second);
                    ImGui::PushID(ptrHex.c_str());
                    ImGui::Text(ptr.first.c_str());
                    ImGui::SameLine(160);
                    ImGui::Text(ptrHex.c_str());
                    ImGui::SameLine(240);
                    if (ImGui::Button("Copy")) ImGui::SetClipboardText(ptrHex.c_str());
                    ImGui::PopID();
                }

                if (ImGui::TreeNode("Enemy List"))
                {
                    ImGui::Checkbox("Enemy Tracers", &g_bEnemyTracers);
                    ImGui::Checkbox("Enemy Names", &g_bEnemyNames);

                    for (auto& enemy : g_aEnemyList)
                    {
                        std::string enemyName = ReadUnityString(enemy->objectProps->name);
                        std::string enemyPtrHex = PtrToHex((uintptr_t)enemy).c_str();

                        ImGui::PushID(enemyName.c_str());
                        ImGui::Text(enemyName.c_str());
                        ImGui::SameLine(140);
                        ImGui::Text(enemyPtrHex.c_str());
                        ImGui::SameLine(240);
                        if (ImGui::Button("Copy")) ImGui::SetClipboardText(enemyPtrHex.c_str());
                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }

                //if (ImGui::TreeNode("Player List"))
                //{
                //    ImGui::Text("Length: %i", g_pNBJLMDOACBC->playerList->size);
                //    std::vector<Entity*> playerList = ReadUnityList<Entity*>(g_pNBJLMDOACBC->playerList);
                //    for (int i = 0; i < playerList.size(); i++)
                //    {
                //        Entity* player = playerList[i];
                //        std::string playerName = ReadUnityString(player->name);
                //        std::string playerPtrHex = PtrToHex((uintptr_t)player).c_str();
                //
                //        ImGui::PushID(playerName.c_str());
                //        ImGui::Text(playerName.c_str());
                //        ImGui::SameLine(140);
                //        ImGui::Text(playerPtrHex.c_str());
                //        ImGui::SameLine(240);
                //        if (ImGui::Button("Copy")) ImGui::SetClipboardText(playerPtrHex.c_str());
                //        ImGui::PopID();
                //    }
                //
                //    ImGui::TreePop();
                //}

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Player Info"))
            {
                float columnWidth = 130.0f;
                ImGui::Text("Name");
                ImGui::SameLine(columnWidth);
                std::string playerName = ReadUnityString(g_pPlayer->name);
                ImGui::Text(playerName.c_str());

                ImGui::Text("Object Name");
                ImGui::SameLine(columnWidth);
                std::string objectName = ReadUnityString(g_pPlayer->objectProps->name);
                ImGui::Text(objectName.c_str());

                ImGui::Text("HP");
                ImGui::SameLine(columnWidth);
                ImGui::Text("%i / %i", g_pPlayer->hp, g_pPlayer->maxHP);

                ImGui::Text("MP");
                ImGui::SameLine(columnWidth);
                ImGui::Text("%.0f / %i", g_pPlayer->mp, g_pPlayer->maxMP);

                ImGui::Text("Pos");
                ImGui::SameLine(columnWidth);
                ImGui::Text("X: %.2f Y: %.2f", g_pPlayer->pos.x, g_pPlayer->pos.y);

                ImGui::Text("Tile");

                if (g_pPlayer->standingTile)
                {
                    std::string tileName = ReadUnityString(g_pPlayer->standingTile->OBGKICHNIDN->name);
                    ImGui::SameLine(columnWidth);
                    ImGui::Text(tileName.c_str());
                }

                //stats
                ImGui::Text("Attack");
                ImGui::SameLine(columnWidth);
                ImGui::Text("%i", g_pPlayer->attack);

                ImGui::SameLine(columnWidth * 1.5f);
                ImGui::Text("Defense");
                ImGui::SameLine(columnWidth * 2.5f);
                ImGui::Text("%i", g_pPlayer->defense);

                ImGui::Text("Speed");
                ImGui::SameLine(columnWidth);
                ImGui::Text("%.0f", g_pPlayer->speed);

                ImGui::SameLine(columnWidth * 1.5f);
                ImGui::Text("Dexterity");
                ImGui::SameLine(columnWidth * 2.5f);
                ImGui::Text("%.0f", g_pPlayer->dexterity);

                ImGui::Text("Vitality");
                ImGui::SameLine(columnWidth);
                ImGui::Text("%i", g_pPlayer->vitality);

                ImGui::SameLine(columnWidth * 1.5f);
                ImGui::Text("Wisdom");
                ImGui::SameLine(columnWidth * 2.5f);
                ImGui::Text("%i", g_pPlayer->wisdom);

                ImGui::TreePop();
            }

            if (ImGui::Button("Clear Enemy List"))
            {
                g_aEnemyList.clear();
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    RECT windowRect;
    g_bWindowFocused = GetClientRect(g_hWindow, &windowRect);

    if (g_bWindowFocused && g_pPlayer)
    {
        /*
        * For some reason unity flips the Y coordinate when using WorldToSreen/ScreenToWorld
        * So we have to flip the value every time it's passed/returned.
        */

        static float hue = 1.0f;
        static float speed = 0.0035f;
        hue += speed;
        if (hue > 360.0f) hue = 1.0f;
        ImColor rainbow = ImColor::HSV(hue, 1.0f, 1.0f);

        ImDrawList* draw = ImGui::GetBackgroundDrawList();

        Vector3 playerPos = { g_pPlayer->pos.x, (g_pPlayer->pos.y) * -1, 0.0f };
        Vector3 playerScreenPoint = WorldToScreen(g_pMainCamera, playerPos);

        ImVec2 mousePos = ImGui::GetMousePos();

        ImVec2 origin = { playerScreenPoint.x, playerScreenPoint.y };
        ImVec2 target = mousePos;

        //ImGui::SetWindowFontScale(1.2f);
        for (auto &x : g_aEnemyList)
        {
            Entity* enemy = x;
            Vector3 enemyPos = { enemy->pos.x, (enemy->pos.y) * -1, 0.0f };
            Vector3 enemyScreenPos = WorldToScreen(g_pMainCamera, enemyPos);

            // Flip y coordinate, unity is weird
            float windowHeight = (float)(windowRect.bottom - windowRect.top);
            enemyScreenPos.y = windowHeight - enemyScreenPos.y;

            ImVec2 target = ImVec2(enemyScreenPos.x, enemyScreenPos.y);
            if (g_bEnemyTracers)
                draw->AddLine(origin, target, rainbow, 3.0f);

            if (g_bEnemyNames)
            {
                std::string enemyName = ReadUnityString(enemy->objectProps->name);
                draw->AddText(ImGui::GetFont(), ImGui::GetFontSize() * 1.5f, target, IM_COL32_BLACK, enemyName.c_str());
                //draw->AddText(target, IM_COL32_BLACK, enemyName.c_str());
            }
        }
        //ImGui::SetWindowFontScale(1.0);
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
