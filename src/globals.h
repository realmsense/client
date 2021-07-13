#pragma once

extern std::unordered_set<Character*> g_aEnemyList;
void CleanEnemyList();

extern bool g_bGuiOpen;

void LoadSettings();
void SaveSettings();