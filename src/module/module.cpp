#include "pch.h"
#include "module.h"

Module::Module()
{
	this->initialized = false;
}

void Module::ready()
{
	std::cout << "Loaded Module: " << this->name << std::endl;
	this->initialized = true;
}

void Module::setEnabled(bool enable, bool callHandlers)
{
	if (enable)
	{
		this->enabled = true;
		if (callHandlers)
			this->onEnable();
	}
	else
	{
		this->enabled = false;
		if (callHandlers)
			this->onDisable();
	}
}

void Module::toggleModule()
{
	this->setEnabled(!this->enabled, true);
}