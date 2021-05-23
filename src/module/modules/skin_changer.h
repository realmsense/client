#pragma once

#include "gui.h"
#include "../module.h"

class SkinChangerModule : public Module {
public:
	SkinChangerModule();

	void onEnable() override;
	void onDisable() override;
	void renderGUI() override;
    void onMapChange() override;

private:
	int skin_id;
    void changeSkin(int skin_id);
};

struct Skin : GuiImage
{
	Skin(std::string name, std::string file_name, int skin_id);

	std::string name;
	int skin_id;
};

// TODO: move to a separate file for custom struct includes. we can #define Color32 there to
enum class ClassList : int32_t
{
    Any = 0,
    Rogue = 1,
    Archer = 2,
    Wizard = 3,
    Priest = 4,
    Warrior = 5,
    Knight = 6,
    Paladin = 7,
    Assassin = 8,
    Necromancer = 9,
    Huntress = 10,
    Mystic = 11,
    Trickster = 12,
    Sorcerer = 13,
    Ninja = 14,
    Samurai = 15,
    Bard = 16,
    Summoner = 17,
    Count = 18
};