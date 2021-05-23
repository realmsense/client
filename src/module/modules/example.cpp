#include "pch.h"
#include "helpers.h"
#include "example.h"

#include "imgui/imgui.h"

ExampleModule::ExampleModule()
	: Module()
{
	this->name = "Example";
	this->enabled = false;
	this->category = ModuleCategory::MOVEMENT;
	//this->type = ModuleList::Example;
	this->has_gui_elements = false;
	this->ready();
}

void ExampleModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void ExampleModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void ExampleModule::renderGUI()
{
	//
}
