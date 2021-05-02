#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include <chrono>
#include <thread>
#include <future>

#include "anti_lag.h"

void ResizeCharacter(uintptr_t characterTransform, Vector3 newScale)
{
    std::vector<std::string> names{ "Content", "CharacterGUI", "Shadow" };
    std::vector<uintptr_t> transformList = FindChildTransforms(characterTransform, names);
    for (int i = 0; i < transformList.size(); i++)
    {
        if (names[i] == "Shadow")
            Transform_set_localScale(transformList[i], { newScale.x / 1.5f, newScale.y / 3.0f, newScale.z }); // 0.6x 0.3y
        else
            Transform_set_localScale(transformList[i], newScale);
    }
}

AntiLagModule::AntiLagModule(std::string name, bool enabled, ModuleCategory category)
    : Module(name, enabled, category)
{
    this->playerSize = 1.0f;
    this->hideTiles = false;
    this->hidePets = false;
    this->showFPS = false;
    this->unlimitedFPS = false;
}

void AntiLagModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void AntiLagModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

bool AntiLagModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::MainLoop:
        return this->onMainLoop();
    case ModuleEvent::Pet_Update:
        return this->onPetUpdate(dp);
    default:
        return true;
    }
}

bool AntiLagModule::onMainLoop()
{
    this->fullscreenMode = Screen_GetFullscreenMode();
    return true;
}

bool AntiLagModule::onPetUpdate(CDataPack* dp)
{
    // TODO: we need a better method of hiding pets
    // we're also potentially hiding map objects, if they use the same transform as a previous hidden pet

    // the better option is to just disable the "MapObject" thing (from UnityExplorer)
    // and not change scale like we're currently doing
    // that way if we disable Hide Pets and load into a new map everything will be loaded correctly.
    // downside is that we cannot unhide pets easily (unless we load into a new map)
    // we could solve this by keeping a vector of disabled pets but that can become too difficult and potential memory issues (bad ptrs)

    if (!this->hidePets)
        return true;

    Vector3 newScale = { 0.0f, 0.0f, 0.0f, };
    dp->Reset();
    dp->PackFloat(newScale.x);
    dp->PackFloat(newScale.y);
    dp->PackFloat(newScale.z);
    return true;
}

void AntiLagModule::ResizePlayers(float scale)
{
    this->playerSize = scale;

    //auto future = std::async(std::launch::async, ResizePlayers, scale);

    std::vector<uintptr_t> characterList = GetChildTransforms(FindGameObject("Character"));
    for (int i = 0; i < characterList.size(); i++)
    {
        uintptr_t character = characterList[i];
        Vector3 newScale = { scale, scale, 1.0f };
        ResizeCharacter(character, newScale);

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Reset our player's size
    Vector3 newScale = { 1.0f, 1.0f, 1.0f };
    uintptr_t viewTransform = (uintptr_t)g_pPlayer->viewHandler->viewTransform;
    ResizeCharacter(viewTransform, newScale);
}

void AntiLagModule::HideTiles(bool hide)
{
    this->hideTiles = hide;

    //auto future = std::async(std::launch::async, _HideTiles, hide);

    std::vector<uintptr_t> tileList = GetChildTransforms(FindGameObject("ComboTile"));
    for (int i = 0; i < tileList.size(); i++)
    {
        uintptr_t tile = tileList[i];
        if (hide)
        {
            Vector3 newScale = { 0.0f, 0.0f, 1.0f };
            Transform_set_localScale(tile, newScale);
        }
        else
        {
            Vector3 newScale = { 1.0f, 1.0f, 1.0f };
            Transform_set_localScale(tile, newScale);
        }
    }

    if (this->hideTiles)
    {
        this->log.color = Color32_GREEN;
        this->log.floatingText = true;
        this->log << "Hide Tiles enabled" << std::endl;
    }
    else
    {
        this->log.color = Color32_RED;
        this->log.floatingText = true;
        this->log << "Hide Tiles disabled" << std::endl;
    }
}

void AntiLagModule::ShowFPS(bool show)
{
    this->showFPS = show;

    std::vector<uintptr_t> transfList = GetChildTransforms(FindGameObject("GameController"));
    for (int i = 0; i < transfList.size(); i++)
    {
        uintptr_t transform = transfList[i];
        std::string transformName = ReadUnityString(Object_GetName(transform));

        // We can't just do Transform.Find() because the forward slash in "Fps/Stats" is treated as a path name
        if (transformName != "Fps/Stats")
            continue;

        uintptr_t fpsStatsObj = Component_GetGameObject(transform);

        String* str = il2cpp_string_new("FPS ---------------------------");
        uintptr_t fpsTransf = Transform_Find(transform, str);
        uintptr_t fpsObj = Component_GetGameObject(fpsTransf);

        std::cout << std::hex << fpsStatsObj << std::endl;
        std::cout << std::hex << fpsObj << std::endl;
        std::cout << this->showFPS << std::endl;

        // weird bug, we get access violations probably because the GraphyManager object isn't initialized ??
        // try enabling in unity explorer, we get a bit of lag and prboably an error (if we're debugging) when we try to enalbe FPS/Stats
        // dunno how to fix

        GameObject_SetActive(fpsStatsObj, this->showFPS);
        GameObject_SetActive(fpsObj, this->showFPS);
        break;
    }

    if (this->showFPS)
    {
        this->log.color = Color32_GREEN;
        this->log.floatingText = true;
        this->log << "Show FPS enabled" << std::endl;
    }
    else
    {
        this->log.color = Color32_RED;
        this->log.floatingText = true;
        this->log << "Show FPS disabled" << std::endl;
    }
}


void AntiLagModule::ToggleUnlimitedFPS(bool on)
{
    this->unlimitedFPS = on;
    if (this->unlimitedFPS)
    {
        SetVsync(0);
        SetFpsTarget(999);
    }
    else
    {
        // fps target is irrelevant if vsync is on
        SetVsync(1);
    }

    if (this->unlimitedFPS)
    {
        this->log.color = Color32_GREEN;
        this->log.floatingText = true;
        this->log << "Unlimited FPS enabled" << std::endl;
    }
    else
    {
        this->log.color = Color32_RED;
        this->log.floatingText = true;
        this->log << "Unlimited FPS disabled" << std::endl;
    }
}

void AntiLagModule::SetFullscreenMode(int mode)
{
    this->fullscreenMode = mode;
    Screen_SetFullscreenMode(this->fullscreenMode);
}
