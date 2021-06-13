#include "pch.h"
#include "helpers.h"
#include "autonexus.h"

#include "thirdparty/imgui/imgui.h"

AutoNexusModule::AutoNexusModule()
	: Module()
{
	this->name = "Auto Nexus";
	this->enabled = false;
	this->category = ModuleCategory::AUTO;
	this->type = ModuleList::AutoNexus;
	this->has_gui_elements = true;

	this->nexus_percent = 15;
	this->nexused = false;

	this->ready();
}

void AutoNexusModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void AutoNexusModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void AutoNexusModule::renderGUI()
{
	ImGui::SliderInt("Percentage", &this->nexus_percent, 1, 99, "%d%% HP");
	if (ImGui::IsItemDeactivatedAfterEdit())
	{
		this->log << "Percentage set to " << this->nexus_percent << "%" << std::endl;

		//int hp_percent, nexus_hp;
		//this->calculateHPValues(GetPlayer(), hp_percent, nexus_hp);
		//
		//this->log.floatingText(Color32_BLUE);
		//this->log << "AutoNexus set to " << nexus_hp << " HP" << std::endl;
		//
		//this->enabled = true;
		this->setEnabled(true);
	}
}

void AutoNexusModule::onMainLoop()
{
	if (!this->enabled) return;

	Player* player = GetPlayer();
	if (player)
	{
		this->checkHP();
	}
}

void AutoNexusModule::onMapChange()
{
	this->nexused = false;
}

void AutoNexusModule::calculateHPValues(Player* player, int& hp_percent, int& nexus_hp)
{
	if (!player)
	{
		hp_percent = -1;
		nexus_hp = -1;
		return;
	}

	int current_hp = player->fields._._.hp;
	int max_hp = player->fields._._.max_hp;

	float percent_decimal = (float)this->nexus_percent / 100;

	hp_percent = (int)(((float)current_hp / (float)max_hp) * 100);
	nexus_hp = (int)(max_hp * percent_decimal);
}

void AutoNexusModule::checkHP()
{
	Player* player = GetPlayer();
	if (!player) return;

	int hp_percent, nexus_hp;
	this->calculateHPValues(player, hp_percent, nexus_hp);

	int current_hp = player->fields._._.hp;
	if (current_hp < nexus_hp)
		this->nexus();

}

void AutoNexusModule::nexus()
{
	if (this->nexused) return;

	static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	static MapViewService* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);
	MapViewService_Nexus(map_view_service, nullptr);

	Player* player = GetPlayer();
	if (!player) return;

	int max_hp = player->fields._._.max_hp;
	int current_hp = player->fields._._.hp;
	int hp_percent, nexus_hp;
	this->calculateHPValues(player, hp_percent, nexus_hp);

	std::cout << "Nexused at " << hp_percent << "% HP. Nexus Percentage: " << this->nexus_percent << "% Nexus HP: " << nexus_hp << std::endl;
	this->nexused = true;
}