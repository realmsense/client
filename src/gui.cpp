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
                    static AutoAimModule* autoAimModule = GetModule<AutoAimModule>(ModuleList::AutoAimModule);
                    if (ImGui::Checkbox("Auto Aim", &autoAimModule->enabled))
                        autoAimModule->setEnabled(autoAimModule->enabled, true);

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
                        autoAimModule->target = AutoAimTarget(selected_target);
                        std::cout << "Auto Aim Target set to: " << aim_targets[selected_target] << std::endl;
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Movement"))
                {
                    static NoclipModule* noclipModule = GetModule<NoclipModule>(ModuleList::NoclipModule);
                    if (ImGui::Checkbox("Noclip", &noclipModule->enabled))
                        noclipModule->setEnabled(noclipModule->enabled, true);

                    static WalkModule* walkModule = GetModule<WalkModule>(ModuleList::WalkModule);
                    ImGui::SliderFloat("Walk Modifier", &walkModule->walkModifier, 1.0f, 10.0f);

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("View"))
                {
                    static DisableFogModule* disableFogModule = GetModule<DisableFogModule>(ModuleList::DisableFogModule);
                    ImGui::Checkbox("Disable Fog", &disableFogModule->enabled);

                    static UnlimitedZoomModule* unlimitedZoomModule = GetModule<UnlimitedZoomModule>(ModuleList::UnlimitedZoom);
                    if (ImGui::SliderFloat("Zoom Amount", &unlimitedZoomModule->zoomAmount, 0.0f, 20.0f))
                        unlimitedZoomModule->Zoom(unlimitedZoomModule->zoomAmount);

                    if (ImGui::Checkbox("Perspective Editor", &unlimitedZoomModule->perspectiveEditorEnabled))
                        unlimitedZoomModule->TogglePerspectiveEditor(unlimitedZoomModule->perspectiveEditorEnabled);

                    static float playerSize = 1.0f;
                    ImGui::SliderFloat("My Player Size", &playerSize, 0.0f, 5.0f);
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        Vector3 newScale = { playerSize, playerSize, playerSize };
                        uintptr_t viewTransform = (uintptr_t)g_pPlayer->viewHandler->viewTransform;
                        ResizeCharacter(viewTransform, newScale);
                    }

                    static AntiLagModule* antiLagModule = GetModule<AntiLagModule>(ModuleList::AntiLag);

                    ImGui::SliderFloat("Player Size", &antiLagModule->playerSize, 0.0f, 1.0f);
                    if (ImGui::IsItemDeactivatedAfterEdit()) // Only update transforms after the slider is released, to prevent the game crashing from too many updates
                        antiLagModule->ResizePlayers(antiLagModule->playerSize);

                    if (ImGui::Checkbox("Hide Tiles", &antiLagModule->hideTiles))
                        antiLagModule->HideTiles(antiLagModule->hideTiles);

                    ImGui::Checkbox("Hide Pets", &antiLagModule->hidePets);

                    if (ImGui::Checkbox("Unlimited FPS", &antiLagModule->unlimitedFPS))
                        antiLagModule->ToggleUnlimitedFPS(antiLagModule->unlimitedFPS);

                    if (ImGui::Checkbox("Show FPS", &antiLagModule->showFPS))
                        antiLagModule->ShowFPS(antiLagModule->showFPS);


                    const char* fullscreen_modes[] =
                    {
                        "Exclusive Fullscreen",
                        "Fullscreen Windowed",
                        "Maximized Window",
                        "Windowed"
                    };
                    static int selected_target = 1;

                    ImGui::SetNextItemWidth(ImGui::GetTextLineHeightWithSpacing()* strlen(fullscreen_modes[0]) / 2); // set width to the widest string
                    if (ImGui::Combo("Fullscreen Mode", &selected_target, fullscreen_modes, IM_ARRAYSIZE(fullscreen_modes), IM_ARRAYSIZE(fullscreen_modes)))
                    {
                        antiLagModule->SetFullscreenMode(selected_target);
                        std::cout << "Auto Aim Target set to: " << fullscreen_modes[selected_target] << std::endl;
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Other"))
                {
                    if (ImGui::Checkbox("Disable AFK Kicker", &g_bDisableAfkKicker))
                    {
                        if (g_pIdleWatcher)
                            Behaviour_set_enabled(g_pIdleWatcher, !g_bDisableAfkKicker);
                    }

                    ImGui::SliderInt("Reconnect Delay", &g_iReconDelay, 0, 30, "%d sec");

                    static NameChangeModule* nameChangeModule = GetModule<NameChangeModule>(ModuleList::NameChange);

                    static char customPlayerName[128] = "";
                    if (ImGui::InputText("Custom Player Name", customPlayerName, IM_ARRAYSIZE(customPlayerName)))
                        nameChangeModule->ChangePlayerName(customPlayerName);

                    static char customGuildName[128] = "";
                    if (ImGui::InputText("Custom Guild Name", customGuildName, IM_ARRAYSIZE(customGuildName)))
                        nameChangeModule->ChangeGuildName(customGuildName);

                    if (ImGui::Checkbox("Rainbow Name", &nameChangeModule->rainbowText))
                    {
                        if (!nameChangeModule->rainbowText)
                        {
                            // Reset name back to white text
                            Color white{ 1.0f, 1.0f, 1.0f, 1.0f };
                            nameChangeModule->ChangeNameColor(white);
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
            static NoclipModule* noclipModule = GetModule< NoclipModule>(ModuleList::NoclipModule);
            if (ImGui::Checkbox("nigga mode", &niggmode))
            {
                if (niggmode)
                {
                    noclipModule->setEnabled(true, true);
                    noclipModule->noclipSpeed = 77.7f;
                    PlaySound(TEXT("C:\\Users\\Extacy\\Desktop\\picture_cut.wav"), NULL, SND_FILENAME | SND_ASYNC);
                }
                else
                {
                    noclipModule->setEnabled(false, true);
                    noclipModule->noclipSpeed = 1.0f;
                    PlaySound(NULL, NULL, SND_ASYNC);
                }
            }

            ImGui::SliderFloat("Noclip Amount", &noclipModule->noclipSpeed, 1.0, 100.0);

            const char* bruh[] = { "aaa", "aaa" };

            static bool ComboTile = true;
            static bool Character = true;
            static bool MapObject = true;
            static bool DrawOnGroundObject = true;
            static bool Table = true;
            static bool ParticleObject = true;
            static bool MapObjectGUI = true;
            static bool StaticSizeParticleObject = true;
            static bool BitmapParticleObject = true;
            static bool BardContainer = true;

            std::map<std::string, bool*> map;
            map.insert(std::pair<std::string, bool*>("ComboTile", &ComboTile));
            map.insert(std::pair<std::string, bool*>("Character", &Character));
            map.insert(std::pair<std::string, bool*>("MapObject", &MapObject));
            map.insert(std::pair<std::string, bool*>("DrawOnGroundObject", &DrawOnGroundObject));
            map.insert(std::pair<std::string, bool*>("Table", &Table));
            map.insert(std::pair<std::string, bool*>("ParticleObject", &ParticleObject));
            map.insert(std::pair<std::string, bool*>("MapObjectGUI", &MapObjectGUI));
            map.insert(std::pair<std::string, bool*>("StaticSizeParticleObject", &StaticSizeParticleObject));
            map.insert(std::pair<std::string, bool*>("BitmapParticleObject", &BitmapParticleObject));
            map.insert(std::pair<std::string, bool*>("BardContainer", &BardContainer));

            for (auto& item : map)
            {
                const char* name = item.first.c_str();
                bool* enabled = item.second;
                if (ImGui::Checkbox(item.first.c_str(), enabled))
                {
                    std::vector<uintptr_t> transfList = GetChildTransforms(FindGameObject(name));
                    for (int i = 0; i < transfList.size(); i++)
                    {
                        uintptr_t transform = transfList[i];

                        Vector3 newScale;

                        if (*enabled)
                            newScale = { 1.0f, 1.0f, 1.0f };
                        else
                            newScale = { 0.0f, 0.0f, 1.0f };

                        if (item.first == "Character")
                        {
                            std::vector<std::string> names{ "Content", "CharacterGUI", "Shadow" };
                            std::vector<uintptr_t> transformList = FindChildTransforms(transform, names);
                            for (int j = 0; j < transformList.size(); j++)
                                Transform_set_localScale(transformList[j], newScale);
                        }
                        else if (item.first == "MapObject")
                        {
                            std::vector<std::string> names{ "Content", "Shadow", "Loot Container" };
                            std::vector<uintptr_t> transformList = FindChildTransforms(transform, names);
                            for (int j = 0; j < transformList.size(); j++)
                                Transform_set_localScale(transformList[j], newScale);
                        }
                        else if (item.first == "Table")
                        {
                            std::vector<std::string> names{ "Mesh1_Model", "Shadow" };
                            std::vector<uintptr_t> transformList = FindChildTransforms(transform, names);
                            for (int j = 0; j < transformList.size(); j++)
                                Transform_set_localScale(transformList[j], newScale);
                        }
                        else
                        {
                            Transform_set_localScale(transform, newScale);
                        }
                    }

                    std::cout << name << " " << *enabled << std::endl;
                }
            }

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
