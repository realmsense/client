#include "pch.h"
#include "helpers.h"
#include "anti_afk.h"

#include "thirdparty/imgui/imgui.h"

AntiAFKModule::AntiAFKModule()
	: Module()
{
	this->name = "Anti AFK";
	this->enabled = false;
	this->category = ModuleCategory::OTHER;
	//this->type = ModuleList::AntiAFK;
	this->has_gui_elements = false;
	this->ready();
}

void AntiAFKModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;

	IdleWatcher* idle_watcher = this->GetIdleWatcher();
	Behaviour_set_enabled((Behaviour*)idle_watcher, false, nullptr);
}

void AntiAFKModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;

	IdleWatcher* idle_watcher = this->GetIdleWatcher();
	Behaviour_set_enabled((Behaviour*)idle_watcher, true, nullptr);
}

void AntiAFKModule::renderGUI()
{
	//
}


IdleWatcher* AntiAFKModule::GetIdleWatcher()
{
	static IdleWatcher* idle_watcher = (IdleWatcher*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Services.IdleWatcher, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
	return idle_watcher;
}