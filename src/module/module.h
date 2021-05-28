#pragma once

#include <string>
#include "module_logger.h"

class Module {
public:

	bool initialized;

	// set in parent ctor
	std::string name;
	bool enabled;
	bool has_gui_elements;
	ModuleCategory category;
	ModuleList type;
	ModuleLogger log;

	Module();

	void ready();
	void setEnabled(bool enabled, bool force_call_handlers=false);
	void toggleModule();
	virtual void renderGUI() = 0;

	// Module Events, to be overrided in parent
	virtual void onMainLoop() { };
	virtual void onMapChange() { };
	virtual void onCheckTileWalkable(bool& walkable) { };
	virtual void onPlayerShoot(app::Player* __this, float& angle) { };

protected:
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};