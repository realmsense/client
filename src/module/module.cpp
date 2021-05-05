#include "pch.h"
#include "module.h"
#include "module_list.h"
#include "module_logger.h"

Module::Module()
{
    this->intialized = false;
    this->log = ModuleLogger();
}

void Module::ready()
{
    this->log.floatingText = false;
    this->log << "Loaded Module: " << this->name << std::endl;
    this->intialized = true;
}

void Module::toggleModule()
{
    this->setEnabled(!this->enabled, true);
}

void Module::toggleModule(bool enabled)
{
    this->setEnabled(enabled, true);
}

void Module::setEnabled(bool enabled, bool callHandlers)
{
    if (enabled)
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
