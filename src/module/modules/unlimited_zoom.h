#pragma once

#include "structs.h"
#include "../module.h"

class UnlimitedZoomModule : public Module {
public:
    UnlimitedZoomModule();

    float zoomAmount;
    bool perspectiveEditorEnabled;

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);

    void Zoom(float amount);
    void TogglePerspectiveEditor(bool enabled);

private:
    //
};
