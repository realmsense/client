#pragma once

#include "../module.h"
#include "thirdparty/imgui/imgui.h"

class NameChangeModule : public Module {
public:
	NameChangeModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	void onMainLoop() override;
	void onMapChange() override;
	// TODO: onChatManager_addslot, replace sent chat messages

private:
	std::string custom_player_name;
	void changePlayerName(std::string name);
	void resetPlayerName();

	bool rainbow_name;
	void changeNameColor(app::Color color);

	std::string custom_guild_name;
	void changeGuildName(std::string name);
	void resetGuildName();

	app::CharacterInfo* GetCharacterInfo();
};

