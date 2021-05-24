#pragma once

#include "../module.h"

class CameraSettingsModule : public Module {
public:
	CameraSettingsModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

private:
	float zoom_amount;
	float rotate_speed;
	void updatePositionShift();
};

