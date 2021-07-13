#include "pch.h"
#include "helpers.h"
#include "name_change.h"

#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/misc/cpp/imgui_stdlib.h"

NameChangeModule::NameChangeModule()
	: Module()
{
	this->name = "Name Change";
	this->enabled = false;
	this->category = ModuleCategory::OTHER;
	this->type = ModuleList::NameChange;
	this->has_gui_elements = true;

	this->ready();
}

void NameChangeModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;

	if (this->custom_player_name != "")
		this->changePlayerName(this->custom_player_name);

	if (this->custom_guild_name != "")
		this->change_guild = true;
}

void NameChangeModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
	
	this->resetPlayerName();
	this->resetGuild();
}

bool NameChangeModule::hook_GameController_FixedUpdate(GameController* __this, MethodInfo*& method, bool& NOP)
{
	if (this->change_guild)
	{
		this->changeGuild(this->custom_guild_name, this->custom_guild_rank);
		this->change_guild = false;
	}
	return false;
}

bool NameChangeModule::hook_TMP_Text_set_text_internal(TMP_Text*& __this, String*& value, MethodInfo*& method, bool& NOP)
{
	if (!this->enabled) return false;

	auto account_name = this->GetGuiManager()->fields.characterInfo->fields.accountName;
	if (__this == (TMP_Text*)account_name)
	{
		if (this->custom_player_name != "")
		{
			// prevent infinite-loop, when we set our custom name in this->changePlayerName
			if (il2cppi_to_string(value) == this->custom_player_name)
				return false;

			this->changePlayerName(this->custom_player_name);
			NOP = true;
			return true;
		}
	}

	auto guild_name = this->GetGuiManager()->fields.characterInfo->fields.guildNameLabel;
	if (__this == (TMP_Text*)guild_name)
	{
		if (this->custom_guild_name != "")
		{
			// prevent infinite-loop, when we set our custom name in this->changePlayerName
			if (il2cppi_to_string(value) == this->custom_guild_name)
				return false;

			this->changeGuild(this->custom_guild_name, this->custom_guild_rank);
			NOP = true;
			return true;
		}
	}

	return false;
}

bool NameChangeModule::hook_GameObject_SetActive(GameObject*& __this, bool& value, MethodInfo*& method, bool& NOP)
{
	if (!this->enabled) return false;

	bool show_guild = this->hide_guild ? false : this->custom_guild_name != "";
	if (value == show_guild) return false;

	GuiManager* gui_manager = this->GetGuiManager();
	GameObject* guild_info = gui_manager->fields.characterInfo->fields.guildInfo;
	
	Transform* guild_info_transf = GameObject_get_transform(guild_info, nullptr);
	int child_count = Transform_get_childCount(guild_info_transf, nullptr);
	for (int i = 0; i < child_count; i++)
	{
		Transform* child_transf = Transform_GetChild(guild_info_transf, i, nullptr);
		GameObject* child_obj = Component_get_gameObject((Component*)child_transf, nullptr);
		if (__this != child_obj) continue;

		this->setGuildVisibility(show_guild);
		NOP = true;
		return true;
	}

	return false;
}

void NameChangeModule::renderGUI()
{
	// TODO: block unity inputs

	if (ImGui::InputText("Custom Player Name", &this->custom_player_name))
	{
		this->changePlayerName(this->custom_player_name);
		this->setEnabled(true);
	}

	static int selected_guildrank = 0;
	if (ImGui::Combo("Custom Guild Rank", &selected_guildrank, guild_ranks, IM_ARRAYSIZE(guild_ranks), IM_ARRAYSIZE(guild_ranks)))
	{
		// rotmg devs forgot what an enum is, and have hard coded values for guild ranks (See ALGAPFJEAOI const ints: 0, 10, 20, 30, 40)
		// maybe a coincidence, but multiplying the index by 10 gives us the value used
		// we subtract rank_length because guild_ranks is in descending order
		int rank_length = IM_ARRAYSIZE(guild_ranks) - 1; // 4
		this->custom_guild_rank = (rank_length - selected_guildrank) * 10;

		this->change_guild = true;
		// this->changeGuild(this->custom_guild_name, this->custom_guild_rank);
		this->setEnabled(true);
	}

	if (ImGui::InputText("Custom Guild Name", &this->custom_guild_name))
	{
		this->change_guild = true;
		//this->changeGuild(this->custom_guild_name, this->custom_guild_rank);
		this->setEnabled(true);
	}

	if (ImGui::Checkbox("Hide Guild", &this->hide_guild))
	{
		this->setGuildVisibility(!this->hide_guild);
		this->setEnabled(true);
	}
}

void NameChangeModule::changePlayerName(std::string name)
{
	GuiManager* gui_manager = this->GetGuiManager();
	TextMeshProUGUI* account_name = gui_manager->fields.characterInfo->fields.accountName;

	TMP_Text_SetText(
		(TMP_Text*)account_name,
		(String*)il2cpp_string_new(name.c_str()),
		true,
		nullptr
	);
}

void NameChangeModule::resetPlayerName()
{
	static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	Settings* settings = game_controller->fields.settings;
	std::string original_name = il2cppi_to_string(settings->fields.account_name);
	this->changePlayerName(original_name);
}

void NameChangeModule::changeGuild(std::string name, int rank)
{
	GuiManager* gui_manager = this->GetGuiManager();

	if (name != "")
	{
		TextMeshProUGUI* guild_name = gui_manager->fields.characterInfo->fields.guildNameLabel;
		TMP_Text_SetText(
			(TMP_Text*)guild_name,
			(String*)il2cpp_string_new(name.c_str()),
			true,
			nullptr
		);
	}

	Image* guild_icon = gui_manager->fields.characterInfo->fields.guildIcon;
	GuildIcon_SetIcon(guild_icon, (int)rank, nullptr);

	this->setGuildVisibility(true);
}

void NameChangeModule::resetGuild()
{
	Player* player = GetPlayer();
	if (!player) return;

	std::string original_guildname = il2cppi_to_string(player->fields.guild_name);
	if (original_guildname == "")
	{
		this->setGuildVisibility(false);
		return;
	}

	this->changeGuild(original_guildname, player->fields.guild_rank);
}

void NameChangeModule::setGuildVisibility(bool shown)
{
	GuiManager* gui_manager = this->GetGuiManager();
	GameObject* guild_info = gui_manager->fields.characterInfo->fields.guildInfo;
	GameObject_SetActive(guild_info, shown, nullptr);

	Transform* guild_info_transf = GameObject_get_transform(guild_info, nullptr);
	int child_count = Transform_get_childCount(guild_info_transf, nullptr);
	for (int i = 0; i < child_count; i++)
	{
		Transform* child_transf = Transform_GetChild(guild_info_transf, i, nullptr);
		GameObject* child_obj = Component_get_gameObject((Component*)child_transf, nullptr);
		GameObject_SetActive(child_obj, shown, nullptr);
	}
}

GuiManager* NameChangeModule::GetGuiManager()
{
	static GuiManager* gui_manager = (GuiManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.GUI.GuiManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	return gui_manager;
}
