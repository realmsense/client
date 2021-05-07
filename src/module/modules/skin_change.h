#pragma once

#include "structs.h"
#include "../module.h"
#include "gui.h"

class SkinChangeModule : public Module {
public:
    SkinChangeModule();

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);

private:
    bool onMainLoop();
};

struct Skin : Image
{
    Skin(std::string name, std::string file_name, int skin_id);

    std::string name;
    int skin_id;
};
