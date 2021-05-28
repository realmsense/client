#pragma once

#include "../module.h"

class NoclipModule : public Module {
public:
	NoclipModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	virtual void onCheckTileWalkable(bool& walkable) override;

private:
	bool safe_mode;
	bool on_walkable_tile;
	void toggleNoclip();
};

