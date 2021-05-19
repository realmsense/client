#pragma once

#include <string>

class Module {
public:

	bool initialized;
	std::string name;
	bool enabled;
	ModuleCategory category;
	ModuleList type;

	Module();

	void ready();
	void setEnabled(bool enabled, bool callHandlers);
	void toggleModule();
	virtual void renderGUI() = 0;

protected:
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};