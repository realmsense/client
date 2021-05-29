#pragma once

extern std::unordered_set<app::Character*> g_aEnemyList;
void CleanEnemyList();

extern bool g_bGuiOpen;

void LoadSettings();
void SaveSettings();