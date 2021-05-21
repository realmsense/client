#pragma once

#include <string>

class Module {
public:

	bool initialized;

	// set in parent ctor
	std::string name;
	bool enabled;
	ModuleCategory category;
	ModuleList type;

	Module();

	void ready();
	void setEnabled(bool enabled, bool callHandlers);
	void toggleModule();
	virtual void renderGUI() = 0;

	// Module Events, to be overrided in parent

protected:
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};