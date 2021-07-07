#pragma once

#include "../module.h"

enum class AutoAim_Target
{
	Any,
	ClosestMouse,
	ClosestPos,
	HighestDef,
	HighestMaxHP
};

class AutoAimModule : public Module {
public:
	AutoAimModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	bool hook_Player_Shoot(Player*& player, float& angle, MethodInfo*& method, bool& NOP);

private:
	AutoAim_Target target_mode;
	bool reverse_cult_staff;
	Character* chooseEnemy();

	void setAutoFire(bool enabled);
};

