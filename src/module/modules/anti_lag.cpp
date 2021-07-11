#include "pch.h"
#include "helpers.h"
#include "anti_lag.h"

#include "thirdparty/imgui/imgui.h"

AntiLagModule::AntiLagModule()
	: Module()
{
	this->name = "Anti Lag";
	this->enabled = false;
	this->category = ModuleCategory::VIEW;
	this->type = ModuleList::AntiLag;
	this->has_gui_elements = true;

	this->player_transparency = 1.0f;
	this->pet_transparency = 1.0f;
	this->unlimited_fps = false;

	this->ready();
}

void AntiLagModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void AntiLagModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void AntiLagModule::renderGUI()
{
	static int player_transparency = 100;
	if (ImGui::SliderInt("Player Transparency", &player_transparency, 0, 100, "%d%%"))
	{
		this->player_transparency = (float)player_transparency / 100;
		this->setEnabled(true);
	}

	static int pet_transparency = 100;
	if (ImGui::SliderInt("Pet Transparency", &pet_transparency, 0, 100))
	{
		this->pet_transparency = (float)pet_transparency / 100;
		this->setEnabled(true);
	}

	if (ImGui::Checkbox("Unlimited FPS", &this->unlimited_fps))
	{
		this->setUnlimitedFPS(this->unlimited_fps);
		if (this->unlimited_fps)
			this->setEnabled(true);
	}
}

bool AntiLagModule::hook_GameController_FixedUpdate(GameController* __this, MethodInfo*& method, bool& NOP)
{
	if (!this->enabled) return false;

	// TODO: Don't hide our own pet, or add an option
	for (Pet* pet : this->pet_list)
	{
		SpriteRenderer* sprite_renderer = pet->fields._._.sprite_renderer;
		if (!sprite_renderer) continue;

		Color color = { 1.0f, 1.0f, 1.0f, this->pet_transparency };
		SpriteRenderer_set_color(sprite_renderer, color, nullptr);
	}

	return false;
}

bool AntiLagModule::hookPost_Player_GetSpriteColor(Player*& __this, MethodInfo*& method, Color& return_value)
{
	if (!this->enabled) return false;

    // TOOD: don't do this!!
	if (__this == GetPlayer())
		return false;

	return_value.a = this->player_transparency;
	return true;
}

bool AntiLagModule::hook_CharacterGUIInfoSection_ChangeTransparencyValue(CharacterGUIInfoSection*& __this, float& transparency, MethodInfo*& method, bool& NOP)
{
	if (!this->enabled) return false;
	
	// TODO: This is only set once, when a Character enters the map
	// would be nice to see the transparency change with the imgui slider.
	transparency = this->player_transparency;
	return true;
}

bool AntiLagModule::hook_Detour_List_1_System_Object_Add(List_1_System_Object_*& __this, Object*& item, MethodInfo*& method, bool& NOP)
{
	if (method == *List_1_NIIFJAMEHDD__Add__MethodInfo)
	{
		NIIFJAMEHDD* entity = (NIIFJAMEHDD*)item;
		if (entity->fields._.map_item_type == MapItemType::Pet)
		{
			Pet* pet = (Pet*)entity;
			this->pet_list.insert(pet);
		}
	}

	return false;
}

bool AntiLagModule::hookPre_Detour_List_1_System_Object_Remove(List_1_System_Object_*& __this, Object*& item, MethodInfo*& method, bool& return_value)
{
	if (method == *List_1_NIIFJAMEHDD__Add__MethodInfo)
	{
		NIIFJAMEHDD* entity = (NIIFJAMEHDD*)item;
		if (entity->fields._.map_item_type == MapItemType::Pet)
		{
			Pet* pet = (Pet*)entity;
			this->pet_list.erase(pet);
		}
	}

	return false;
}

void AntiLagModule::setUnlimitedFPS(bool enabled)
{
	if (enabled)
	{
		QualitySettings_set_vSyncCount(0, nullptr);
		Application_set_targetFrameRate(999, nullptr);
	}
	else
	{
		QualitySettings_set_vSyncCount(1, nullptr);
	}
}