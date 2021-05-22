#include "pch.h"
#include "noclip.h"
#include "helpers.h"

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
	this->log.floatingText(Color32_GREEN);
	this->log << "ON" << std::endl;

	this->toggleNoclip();
}

void NoclipModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << "OFF" << std::endl;

	this->toggleNoclip();
}

void NoclipModule::renderGUI()
{
	ImGui::Text("hiii");
}

void NoclipModule::toggleNoclip()
{
	static UnityThread* unity_thread = (UnityThread*)FindObjectByQualifiedName("DecaGames.RotMG.Extensions.UnityThread, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	Behaviour_set_enabled((Behaviour*)unity_thread, !this->enabled, nullptr);
}

bool NoclipModule::onCheckTileWalkable(bool& override)
{
	if (this->enabled)
	{
		override = true;
		return true;
	}
}