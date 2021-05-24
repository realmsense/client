#pragma once

#include "../module.h"

class UnlimitedZoomModule : public Module {
public:
	UnlimitedZoomModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

private:
	float zoom;
	void updatePositionShift();
};

