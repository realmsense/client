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
	this->has_gui_elements = false;
	this->ready();
}

void NoclipModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;

	this->toggleNoclip();
}

void NoclipModule::onDisable()
{
	if (!this->on_walkable_tile)
	{
		this->log.floatingText(Color32_BLUE);
		this->log << "On Unwalkable Tile!" << std::endl;
		this->enabled = true;
		return;
	}

	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;

	this->toggleNoclip();
}

void NoclipModule::renderGUI()
{
	//
}

void NoclipModule::toggleNoclip()
{
	static UnityThread* unity_thread = (UnityThread*)FindObjectByQualifiedName("DecaGames.RotMG.Extensions.UnityThread, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	Behaviour_set_enabled((Behaviour*)unity_thread, !this->enabled, nullptr);
}

void NoclipModule::onCheckTileWalkable(bool& walkable)
{
	if (this->enabled)
	{
		this->on_walkable_tile = walkable;
		walkable = true;
	}
}