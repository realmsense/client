#pragma once

extern std::unordered_set<app::Character*> g_aEnemyList;
void CleanEnemyList();

void LoadSettings();
void SaveSettings();