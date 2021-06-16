#include "pch.h"
#include "helpers.h"
#include "disable_chat_filter.h"

#include "thirdparty/imgui/imgui.h"

DisableChatFilterModule::DisableChatFilterModule()
	: Module()
{
	this->name = "Disable Chat Filter";
	this->enabled = false;
	this->category = ModuleCategory::OTHER;
	this->type = ModuleList::DisableChatFilter;
	this->has_gui_elements = false;
	this->ready();
}

void DisableChatFilterModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void DisableChatFilterModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void DisableChatFilterModule::renderGUI()
{
	//
}


void DisableChatFilterModule::onChatFilterValidate(bool& filter)
{
	if (this->enabled)
	{
		filter = false;
	}
}