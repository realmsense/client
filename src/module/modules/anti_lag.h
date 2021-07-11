#pragma once

#include "../module.h"

class AntiLagModule : public Module {
public:
	AntiLagModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	bool hook_GameController_FixedUpdate(GameController* __this, MethodInfo*& method, bool& NOP) override;
	bool hookPost_Player_GetSpriteColor(Player*& __this, MethodInfo*& method, Color& return_value) override;
	bool hook_CharacterGUIInfoSection_ChangeTransparencyValue(CharacterGUIInfoSection*& __this, float& transparency, MethodInfo*& method, bool& NOP) override;

	bool hook_Detour_List_1_System_Object_Add(List_1_System_Object_*& __this, Object*& item, MethodInfo*& method, bool& NOP) override;
	bool hookPre_Detour_List_1_System_Object_Remove(List_1_System_Object_*& __this, Object*& item, MethodInfo*& method, bool& return_value) override;

private:
	float player_transparency;
	std::unordered_set<Pet*> pet_list;
	float pet_transparency;
	bool unlimited_fps;


	void setUnlimitedFPS(bool enabled);
};

