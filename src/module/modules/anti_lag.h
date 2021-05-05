#pragma once

#include "structs.h"
#include "../module.h"

class AntiLagModule : public Module {
public:
    AntiLagModule();

    float playerSize;
    bool hideTiles;
    bool hidePets;
    bool showFPS;
    bool unlimitedFPS;
    int fullscreenMode;

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);
    bool onMainLoop();
    bool onPetUpdate(CDataPack* dp);

    void ResizePlayers(float scale);
    void HideTiles(bool hide);
    void ShowFPS(bool show);
    void ToggleUnlimitedFPS(bool on);
    void SetFullscreenMode(int mode);

private:

};

void ResizeCharacter(uintptr_t characterTransform, Vector3 newScale);
