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
	virtual bool hook_GameController_FixedUpdate(GameController* __this, bool& NOP) { return false; };
	virtual bool hookPre_ChatFilter_Validate(ChatFilter*& __this, String*& message, bool& return_value) { return false; };
	virtual bool hookPost_ChatFilter_Validate(ChatFilter*& __this, String*& message, bool& return_value) { return false; };
	virtual bool hookPre_MapViewService_CheckTileWalkable(MapViewService*& __this, float& x, float y, bool& return_value) { return false; };
	virtual bool hookPost_MapViewService_CheckTileWalkable(MapViewService*& __this, float& x, float y, bool& return_value) { return false; };
	virtual bool hook_SpriteShader_UpdateMask(SpriteShader*& __this, CGPOGAAKLFL*& DLNMEAOOHKA, int32_t& large_cloth, int32_t& small_cloth, bool& NOP) { return false; };
	virtual bool hook_Player_Shoot(Player*& player, float& angle, MethodInfo*& method, bool& NOP) { return false; };


protected:
	virtual void onEnable() = 0;
	virtual void onDisable() = 0;
};