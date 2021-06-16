#pragma once

#include "../module.h"

class DisableChatFilterModule : public Module {
public:
	DisableChatFilterModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;

	void onChatFilterValidate(bool& filter) override;
};

