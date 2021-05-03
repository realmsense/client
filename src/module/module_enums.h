#pragma once

enum class ModuleEvent
{
    MainLoop,
    UnityThread_Update,
    GetMousePos,
    Tile_SetColor,
    CameraManager_Update,
    SocketManager_Connect,
    TMP_SetText,
    Pet_Update
};

enum class ModuleCategory {
    VIEW,
    MOVEMENT,
    AUTO,
    OTHER
};

enum class ModuleList
{
    NoclipModule,
    AutoAimModule,
    WalkModule,
    DisableFogModule,
    UnlimitedZoom,
    AntiLag,
    NameChange,
    AntiAFK
};
