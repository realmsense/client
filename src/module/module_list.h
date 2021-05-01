#pragma once

#include "modules/noclip.h"
#include "modules/autoaim.h"
#include "modules/walk.h"
#include "modules/disable_fog.h"
#include "modules/unlimited_zoom.h"
#include "modules/anti_lag.h"
#include "modules/name_change.h"
#include "modules/anti_afk.h"

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
