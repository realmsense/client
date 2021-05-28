#include "pch.h"
#include "helpers.h"
#include "debug.h"

#include "gui.h"
#include "imgui/imgui.h"

DebugModule::DebugModule()
	: Module()
{
	this->name = "Debug";
	this->enabled = false;
	this->category = ModuleCategory::OTHER;
	this->type = ModuleList::Debug;
	this->has_gui_elements = true;

	this->draw_enemy_tracers = false;

	this->ready();
}

void DebugModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void DebugModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;

	this->draw_enemy_tracers = false;
}

void DebugModule::renderGUI()
{
	if (ImGui::Checkbox("Draw Enemy Tracers", &this->draw_enemy_tracers))
		this->setEnabled(true);

	if (this->draw_enemy_tracers && this->enabled)
	{
		Player* player = GetPlayer();

		RECT window_rect;
		if (GetClientRect(g_hWindow, &window_rect) && player)
		{
			ImDrawList* draw = ImGui::GetBackgroundDrawList();

			Vector2 player_pos = GetEntityPos((BasicObject*)player);
			Vector3 player_world_pos = { player_pos.x, player_pos.y * -1, 0.0f };
			Vector3 player_screen_pos = Camera_WorldToScreenPoint(GetMainCamera(), player_world_pos, nullptr);

			for (Character* enemy : g_aEnemyList)
			{
				Vector2 enemy_pos = GetEntityPos((BasicObject*)enemy);
				Vector3 enemy_world_pos = { enemy_pos.x, enemy_pos.y * -1, 0.0f };
				Vector3 enemy_screen_pos = Camera_WorldToScreenPoint(GetMainCamera(), enemy_world_pos, nullptr);
			
				// Invert y coordinate, unity is weird and uses y coordinate as a negative
				float window_height = (float)(window_rect.bottom - window_rect.top);
				enemy_screen_pos.y = window_height - enemy_screen_pos.y;
			
				ImVec2 origin = ImVec2(player_screen_pos.x, player_screen_pos.y);
				ImVec2 target = ImVec2(enemy_screen_pos.x, enemy_screen_pos.y);
				draw->AddLine(origin, target, IM_COL32_BLACK, 3.0f);
			}
		}
	}
}
