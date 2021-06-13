#pragma once

#include "../module.h"

class CameraSettingsModule : public Module {
public:
	CameraSettingsModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	void onMapChange() override;

private:
	float zoom_amount;
	float rotate_speed;
	void updatePositionShift();

	bool disable_fog;
	float fog_range;
	int view_distance;

	float old_fog_range;
	int old_view_distance;
	void updateFogSettings(float fog_range, int view_distance);
};

