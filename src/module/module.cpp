#include "pch.h"
#include "module.h"
#include "module_list.h"

Module::Module(std::string name, bool enabled, ModuleCategory category)
{
    this->name = name;
    this->enabled = enabled;
    this->category = category;

    std::cout << "Loaded Module: " << this->name << std::endl;
}

void Module::toggleModule()
{
    this->setEnabled(!this->enabled, true);
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
