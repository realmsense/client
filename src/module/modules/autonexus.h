#pragma once

#include "../module.h"

class AutoNexusModule : public Module {
public:
	AutoNexusModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	void onMainLoop() override;
	void onMapChange() override;

private:
	int nexus_percent;
	bool nexused;

	void checkHP();
	void nexus();

	void calculateHPValues(Player* player, int& hp_percent, int& nexus_hp);
};

