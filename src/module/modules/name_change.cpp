#include "pch.h"
#include "helpers.h"
#include "name_change.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

NameChangeModule::NameChangeModule()
	: Module()
{
	this->name = "Name Change";
	this->enabled = false;
	this->category = ModuleCategory::OTHER;
	this->type = ModuleList::NameChange;
	this->has_gui_elements = true;

	this->custom_player_name = "";
	this->rainbow_name = false;
	this->custom_guild_name = "";

	this->ready();
}

void NameChangeModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;

	if (this->custom_player_name != "")
		this->changePlayerName(this->custom_player_name);

	if (this->custom_guild_name != "")
		this->changeGuildName(this->custom_guild_name);
}

void NameChangeModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;

	this->resetPlayerName();
	this->resetGuildName();

	this->changeNameColor({ 255.0f, 255.0f, 255.0f, 255.0f }); // white
}

void NameChangeModule::onMainLoop()
{
	if (!this->enabled) return;
	if (this->rainbow_name)
	{
		static float hue = 1.0f;
		static float speed = 0.0035f;
		hue += speed;
		if (hue > 360.0f) hue = 1.0f;
		ImVec4 rainbow = (ImVec4)(ImColor)ImColor::HSV(hue, 1.0f, 1.0f);

		Color color = { rainbow.x, rainbow.y, rainbow.z, rainbow.w};
		this->changeNameColor(color);
	}
}

void NameChangeModule::onMapChange()
{
	if (!this->enabled) return;

	if (this->custom_player_name != "")
		this->changePlayerName(this->custom_player_name);

	if (this->custom_guild_name != "")
		this->changeGuildName(this->custom_guild_name);

	std::cout << this->custom_player_name << std::endl;
}

void NameChangeModule::renderGUI()
{
	if (ImGui::InputText("Custom Player Name", &this->custom_player_name))
	{
		this->changePlayerName(this->custom_player_name);
		this->setEnabled(true);
	}

	if (ImGui::Checkbox("Rainbow Name", &this->rainbow_name))
	{
		if (this->rainbow_name)
			this->setEnabled(true);
		else
			this->changeNameColor({ 255.0f, 255.0f, 255.0f, 255.0f }); // white
	}

	if (ImGui::InputText("Custom Guild Name", &this->custom_guild_name))
	{
		this->changeGuildName(this->custom_guild_name);
		this->setEnabled(true);
	}
}

void NameChangeModule::changePlayerName(std::string name)
{
	CharacterInfo* character_info = this->GetCharacterInfo();
	TMP_Text* account_name = (TMP_Text*)character_info->fields.accountName;

	String* new_name = (String*)il2cpp_string_new(name.c_str());
	TMP_Text_SetText(account_name, new_name, true, nullptr);
}

void NameChangeModule::resetPlayerName()
{
	static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	Settings* settings = game_controller->fields.settings;
	this->changePlayerName(il2cppi_to_string(settings->fields.account_name));
}

void NameChangeModule::changeNameColor(Color color)
{
	CharacterInfo* character_info = this->GetCharacterInfo();
	TMP_Text* account_name = (TMP_Text*)character_info->fields.accountName;

	//Color new_color = { color[0], color[1], color[2], color[3]};
	TMP_Text_set_color(account_name, color, nullptr);
}

void NameChangeModule::changeGuildName(std::string name)
{
	// set gameobject enabled here
	// unless if name == "" then we can disable.

	CharacterInfo* character_info = this->GetCharacterInfo();
	GameObject* guild_object = character_info->fields.guildInfo;

	if (name == "")
	{
		GameObject_SetActive(guild_object, false, nullptr);
	}
	else
	{
		TMP_Text* guild_name = (TMP_Text*)character_info->fields.guildNameLabel;
		GameObject* name_object = Component_get_gameObject((Component*)guild_name, nullptr);

		GameObject_SetActive(guild_object, true, nullptr);
		GameObject_SetActive(name_object, true, nullptr);

		String* new_name = (String*)il2cpp_string_new(name.c_str());
		TMP_Text_SetText(guild_name, new_name, true, nullptr);
	}
}

void NameChangeModule::resetGuildName()
{
	static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	static GuildInfo* guild_info = application_manager->fields.guild_info;
	static Guild* guild = guild_info->fields.guild;

	if (!guild)
		this->changeGuildName(""); // hide
	else
		this->changeGuildName(il2cppi_to_string(guild->fields.name));
}

CharacterInfo* NameChangeModule::GetCharacterInfo()
{
	static CharacterInfo* character_info = (CharacterInfo*)FindObjectByQualifiedName("DecaGames.RotMG.UI.GUI.CharacterInfo, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	return character_info;
}