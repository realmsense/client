#pragma once

enum class ModuleEvent
{
    MainLoop,
    UnityThread_Update,
    GetMousePos,
    Tile_SetColor,
    SocketManager_Connect,
    TMP_SetText,
    Pet_Update,
    MapChange
};

enum class ModuleCategory {
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
    WalkModule,
    DisableFog,
    UnlimitedZoom,
    AntiLag,
    NameChange,
    AntiAFK,
    SkinChange
};
