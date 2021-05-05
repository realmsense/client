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
    bool onMainLoop();
    bool onTMPSetText(CDataPack* dp);

    const char* customGuildName;
    std::string oldGuildName;
    void ChangeGuildName(const char* name);

    const char* customPlayerName;
    std::string oldPlayerName;
    void ChangePlayerName(const char* name);

    bool rainbowText;
    Color nameColor;
    void ChangeNameColor(Color color);

private:
    CharacterInfo_GUI* charInfoObj;
    bool GetCharInfoObject();
};
