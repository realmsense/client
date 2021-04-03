#include "pch.h"

void CreateConsole()
{
   AllocConsole();
   freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

void RemoveConsole()
{
   fclose(stdout);
   FreeConsole();
}
