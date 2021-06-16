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
	virtual void onSpriteShader_UpdateMask(app::SpriteShader* sprite_shader, int32_t& large_cloth, int32_t& small_cloth) { };
	virtual void onChatFilterValidate(bool& filter) { };

protected:
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};