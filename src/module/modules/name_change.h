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
	// Wait until the original name is set on mapchange, before setting a custom one.
	bool wait_for_playername = false;
	bool wait_for_guildname = false;

	std::string custom_player_name;
	void changePlayerName(std::string name);
	void resetPlayerName();

	bool rainbow_name;
	void changeNameColor(Color color);

	std::string custom_guild_name;
	void changeGuildName(std::string name);
	void resetGuildName();

	CharacterInfo* GetCharacterInfo();
};

