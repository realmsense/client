#pragma once

#include "../module.h"

class NoclipModule : public Module {
public:
	NoclipModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;
};

