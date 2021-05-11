#pragma once

#include "structs.h"
#include "../module.h"

class NameChangeModule : public Module {
public:
    NameChangeModule();

    void onEnable();
    void onDisable();
    void renderGUI();
    bool onEvent(ModuleEvent event, CDataPack* dp);


    bool input_focused;

    const char* customGuildName;
    std::string originalGuildName;
    void ChangeGuildName(const char* name);

    const char* customPlayerName;
    std::string originalPlayerName;
    void ChangePlayerName(const char* name);

    bool rainbowName;
    Color customNameColor;
    void ToggleRainbowName(bool enabled);
    void ChangeNameColor(Color color);

private:
    CharacterInfo_GUI* charInfoObj;
    bool GetCharInfoObject();

    bool onMainLoop();
    bool onGetKeyDown();
    bool onTMPSetText(CDataPack* dp);
    bool onMapChange();
};
