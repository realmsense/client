#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "anti_afk.h"

AntiAfkModule::AntiAfkModule(std::string name, bool enabled, ModuleCategory category)
    : Module(name, enabled, category)
{
    this->idleWatcherObj = 0;
}

void AntiAfkModule::onEnable()
{
    if (!this->GetIdleWatcher())
        return;

    std::cout << std::hex << this->idleWatcherObj << std::endl;
    Behaviour_set_enabled(this->idleWatcherObj, false);

    std::cout << this->name << " enabled" << std::endl;
}

void AntiAfkModule::onDisable()
{
    if (!this->GetIdleWatcher())
        return;

    std::cout << std::hex << this->idleWatcherObj << std::endl;
    Behaviour_set_enabled(this->idleWatcherObj, true);

    std::cout << this->name << " disabled" << std::endl;
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

    String* idleWatcher_QualifiedName = il2cpp_string_new("DecaGames.RotMG.Managers.Services.IdleWatcher, Assembly-CSharp, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null");
    uintptr_t idleWatcher_Type = System_GetType(idleWatcher_QualifiedName);
    uintptr_t idleWatcher_Obj = Object_FindObjectOfType(idleWatcher_Type);
    if (idleWatcher_Obj)
    {
        this->idleWatcherObj = (uintptr_t)idleWatcher_Obj; // pointer??
        return true;
    }

    return false;
}
