#pragma once

#include "../module.h"

class DisableChatFilterModule : public Module {
public:
	DisableChatFilterModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	bool hookPre_ChatFilter_Validate(ChatFilter*& __this, String*& message, MethodInfo*& method, bool& return_value) override;
};

