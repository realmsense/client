#pragma once

#include "../module.h"

class NoclipModule : public Module {
public:
	NoclipModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	virtual bool hookPost_MapViewService_CheckTileWalkable(MapViewService*& __this, float& x, float y, MethodInfo*& method, bool& return_value) override;

private:
	bool safe_mode;
	bool on_walkable_tile;
	void toggleNoclip();
};

