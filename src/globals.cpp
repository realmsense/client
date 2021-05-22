#include "pch.h"
#include <unordered_set>

using namespace app;

std::unordered_set<COEDKELBKMI*> g_aEnemyList;
void CleanEnemyList()
{
	// Remove enemies that have become dormant

	// https://stackoverflow.com/a/15662547
	for (auto it = g_aEnemyList.begin(); it != g_aEnemyList.end();)
	{
		auto enemy = (GJLIMCBOCJG*)*it;
		if (!enemy->fields.BIHICFBJDCC)
			it = g_aEnemyList.erase(it);
		else
			it++;
	}

	std::cout << g_aEnemyList.size() << std::endl;

}

void LoadSettings()
{
	// iterate modules, run a loadSettings() method to override variables
}

void SaveSettings()
{
	// iterate modules, pass object by reference so settings can override
}