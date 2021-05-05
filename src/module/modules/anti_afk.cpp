#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "anti_afk.h"

AntiAfkModule::AntiAfkModule()
    : Module()
{
    this->name = "Anti AFK";
    this->enabled = false;
    this->type = ModuleList::AntiAFK;
    this->category = ModuleCategory::OTHER;

    this->idleWatcherObj = 0;
    this->ready();
}

void AntiAfkModule::onEnable()
{
    if (!this->GetIdleWatcher())
        return;

    //std::cout << std::hex << this->idleWatcherObj << std::endl;
    Behaviour_set_enabled(this->idleWatcherObj, false);

    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void AntiAfkModule::onDisable()
{
    if (!this->GetIdleWatcher())
        return;

    //std::cout << std::hex << this->idleWatcherObj << std::endl;
    Behaviour_set_enabled(this->idleWatcherObj, true);

    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void AntiAfkModule::renderGUI()
{

}

bool AntiAfkModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    //switch (event)
    //{
    //default:
    //    return true;
    //}

    return true;
}

bool AntiAfkModule::GetIdleWatcher()
{
    if (this->idleWatcherObj)
        return true;

    this->idleWatcherObj = FindObjectByQualifiedName("DecaGames.RotMG.Managers.Services.IdleWatcher, Assembly-CSharp, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null");
    if (this->idleWatcherObj)
        return true;

    return false;
}
