#include "pch.h"
#include "module.h"

Module::Module()
{
	this->initialized = false;
	this->log = ModuleLogger();
}

void Module::ready()
{
	std::cout << "Loaded Module: " << this->name << std::endl;
	this->log.module_name = this->name;
	this->initialized = true;
}

void Module::setEnabled(bool enable, bool force_call_handlers)
{
	bool call_handlers = force_call_handlers || this->enabled != enable; // don't call handlers if module isn't being toggled (already enabled or disabled)
	if (enable)
	{
		this->enabled = true;
		if (call_handlers)
			this->onEnable();
	}
	else
	{
		this->enabled = false;
		if (call_handlers)
			this->onDisable();
	}
}

void Module::toggleModule()
{
	this->setEnabled(!this->enabled);
}
