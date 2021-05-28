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

	void onPlayerShoot(app::Player* __this, float& angle) override;

private:
	AutoAim_Target target_mode;
	app::Character* chooseEnemy();
};

