#pragma once

#include "../module.h"

class AntiAFKModule : public Module {
public:
	AntiAFKModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

private:
	IdleWatcher* GetIdleWatcher();
};

