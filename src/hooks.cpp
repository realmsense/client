#include "pch.h"
#include <iostream>
#include "minhook/include/MinHook.h"
#include "globals.h"

bool InitHooks()
{
    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(NULL, "Faild To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }

    return true;
}
