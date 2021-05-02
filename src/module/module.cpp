#include "pch.h"
#include "module.h"
#include "module_list.h"
#include "module_logger.h"


Module::Module(std::string name, bool enabled, ModuleCategory category)
{
    this->name = name;
    this->enabled = enabled;
    this->category = category;
    this->log = ModuleLogger();

    this->log.floatingText = true;
    this->log << "Loaded Module: " << this->name << std::endl;

    //std::cout << "Loaded Module: " << this->name << std::endl;
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
