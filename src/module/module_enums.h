#pragma once

enum class ModuleCategory
{
    VIEW,
    MOVEMENT,
    AUTO,
    OTHER,
    Count
};

enum class ModuleList
{
	Noclip,
    AutoAim,
    Debug,
    Count
};

enum class ModuleEvent
{
    MainLoop,
    Check_TileWalkable
};