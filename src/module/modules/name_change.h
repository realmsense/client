#pragma once

#include "../module.h"
#include "thirdparty/imgui/imgui.h"

static const char* guild_ranks[] = { "Founder", "Leader", "Officer", "Member", "Initiate" };

class NameChangeModule : public Module {
public:
	NameChangeModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	bool hook_GameController_FixedUpdate(GameController* __this, MethodInfo*& method, bool& NOP) override;
	bool hook_TMP_Text_set_text_internal(TMP_Text*& __this, String*& value, MethodInfo*& method, bool& NOP) override;
	bool hook_GameObject_SetActive(GameObject*& __this, bool& value, MethodInfo*& method, bool& NOP) override;

	// TODO: onChatManager_addslot, replace sent chat messages

private:

	std::string custom_player_name;
	void changePlayerName(std::string name);
	void resetPlayerName();

	bool hide_guild;
	std::string custom_guild_name;
	int custom_guild_rank = 40; // default leader
	bool change_guild; // TODO: need to sync renderGUI with Unity Update method
	void changeGuild(std::string name, int rank);
	void resetGuild();
	void setGuildVisibility(bool shown);

	GuiManager* GetGuiManager();
};

