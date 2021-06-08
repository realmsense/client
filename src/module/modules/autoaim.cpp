#include "pch.h"
#include "helpers.h"
#include "autoaim.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "thirdparty/imgui/imgui.h"

AutoAimModule::AutoAimModule()
	: Module()
{
	this->name = "Auto Aim";
	this->enabled = false;
	this->category = ModuleCategory::AUTO;
	this->type = ModuleList::AutoAim;
	this->has_gui_elements = true;

	this->reverse_cult_staff = true;
	this->target_mode = AutoAim_Target(1);

	this->ready();
}

void AutoAimModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
	this->setAutoFire(true);
}

void AutoAimModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
	this->setAutoFire(true);
}

void AutoAimModule::renderGUI()
{
	const char* target_modes[] = {
		"Any",					// AutoAim_Target::Any,
		"Closest to Mouse",		// AutoAim_Target::ClosestMouse,
		"Closest to Player",	// AutoAim_Target::ClosestPos,
		"Highest Defense",		// AutoAim_Target::HighestDef,
		"Highest Max HP",		// AutoAim_Target::HighestMaxHP
	};

	static int selected_mode = 1;
	ImGui::SetNextItemWidth(ImGui::GetTextLineHeightWithSpacing() * strlen(target_modes[2]) / 2); // set width to the widest string
	if (ImGui::Combo("Target Mode", &selected_mode, target_modes, IM_ARRAYSIZE(target_modes), IM_ARRAYSIZE(target_modes)))
	{
		this->target_mode = AutoAim_Target(selected_mode);
		this->log << "Target Mode set to " << target_modes[selected_mode] << std::endl;
	}

	if (ImGui::Checkbox("Reverse Cult Staff", &this->reverse_cult_staff))
	{
		this->log.floatingText(Color32_BLUE);
		this->log << "Reverse Cult Staff: " << (this->reverse_cult_staff ? "ON" : "OFF") << std::endl;
	}
}

void AutoAimModule::onPlayerShoot(Player* player, float& angle)
{
	bool attack_held = GetKeyDown(SettingsKeyCode::UseWeaponAttack); // allow user to override autoaim but holding left click
	if (this->enabled && !attack_held)
	{
		Character* enemy = this->chooseEnemy();
		if (enemy)
		{
			Vector2 player_pos = GetEntityPos((BasicObject*)player);
			Vector2 enemy_pos = GetEntityPos((BasicObject*)enemy);

			float diff_x = enemy_pos.x - player_pos.x;
			float diff_y = enemy_pos.y - player_pos.y;
			angle = atan2(diff_y, diff_x);
		}
	}

	if (reverse_cult_staff)
	{
		EquipmentSlot* weapon = GetEquipmentSlot(0);
		ObjectProperties* object_properties = weapon->fields._._.object_properties;
		if (!object_properties) return;

		bool cult_staff = il2cppi_to_string(object_properties->fields.displayId) == "Staff of Unholy Sacrifice";
		if (cult_staff)
		{
			angle -= (float)M_PI;
		}
	}
}

Character* AutoAimModule::chooseEnemy()
{
	Player* player = GetPlayer();
	if (!player) return nullptr;

	Character* chosen_enemy = nullptr;
	for (Character* enemy : g_aEnemyList)
	{
		if (!enemy) continue; // probably need to hook the dispose function that is actually called, rn we're getting random crashes

		if (this->target_mode == AutoAim_Target::Any)
			return enemy;

		if (chosen_enemy == nullptr)
		{
			chosen_enemy = enemy;
			continue;
		}

		Vector2 player_pos = GetEntityPos((BasicObject*)player);
		Vector2 current_enemy_pos = GetEntityPos((BasicObject*)enemy);
		Vector2 chosen_enemy_pos = GetEntityPos((BasicObject*)chosen_enemy);

		if (this->target_mode == AutoAim_Target::ClosestMouse)
		{
			Camera* camera = GetMainCamera();
			ImVec2 cursor_pos = ImGui::GetMousePos();
			Vector3 mouse_world_pos3 = Camera_ScreenToWorldPoint(camera, { cursor_pos.x, cursor_pos.y * -1, 0.0f }, nullptr);
			Vector2 mouse_world_pos = { mouse_world_pos3.x, mouse_world_pos3.y * -1 };

			float chosen_distance = CalculateDistance(chosen_enemy_pos, mouse_world_pos);
			float current_distance = CalculateDistance(current_enemy_pos, mouse_world_pos);
			if (current_distance < chosen_distance)
				chosen_enemy = enemy;
		}

		if (this->target_mode == AutoAim_Target::ClosestPos)
		{
			float chosen_distance = CalculateDistance(player_pos, chosen_enemy_pos);
			float current_distance = CalculateDistance(player_pos, current_enemy_pos);
			if (current_distance < chosen_distance)
				chosen_enemy = enemy;
		}

		if (this->target_mode == AutoAim_Target::HighestDef)
		{
			int chosen_defense = chosen_enemy->fields._.defense;
			int current_defense = enemy->fields._.defense;
			if (current_defense > chosen_defense)
				chosen_enemy = enemy;
		}

		if (this->target_mode == AutoAim_Target::HighestMaxHP)
		{
			int chosen_maxhp = chosen_enemy->fields._.max_hp;
			int current_maxhp = enemy->fields._.max_hp;
			if (current_maxhp > chosen_maxhp)
				chosen_enemy = enemy;
		}
	}

	return chosen_enemy;
}

void AutoAimModule::setAutoFire(bool enabled)
{
	static InputManager* input_manager = (InputManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Options.InputManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	InputManager_set_AutoFire(input_manager, enabled, nullptr);
}