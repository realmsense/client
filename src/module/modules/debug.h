#pragma once

#include "../module.h"

class DebugModule : public Module {
public:
	DebugModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	bool draw_enemy_tracers;
};

