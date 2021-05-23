#pragma once

#include "../module.h"

class ExampleModule : public Module {
public:
	ExampleModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

};

