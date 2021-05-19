#include "pch.h"
#include "noclip.h"

#include "imgui/imgui.h"

NoclipModule::NoclipModule()
	: Module()
{
	this->name = "Noclip";
	this->enabled = false;
	this->category = ModuleCategory::MOVEMENT;
	this->type = ModuleList::Noclip;
	this->ready();
}

void NoclipModule::onEnable()
{
	std::cout << "[" << this->name << "] " << "enabled" << std::endl;

	// Disable UnityThread
}

void NoclipModule::onDisable()
{
	std::cout << "[" << this->name << "] " << "disabled" << std::endl;

	// Enable UnityThread
}

void NoclipModule::renderGUI()
{
	ImGui::Text("hiii");
}