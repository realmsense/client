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
    app::DAFEAHGLBGL* pet;
	int player_skin_id;
    int pet_skin_id;
    void changePetSkin(int skin_id);
    void changePlayerSkin(int skin_id);
};

struct Skin : GuiImage
{
	Skin(std::string name, std::string file_name, int skin_id);

	std::string name;
	int skin_id;
};

// TODO: move to a separate file for custom struct includes. we can #define Color32 there to
enum class ClassList
{
    Any,
    Rogue,
    Archer,
    Wizard,
    Priest,
    Warrior,
    Knight,
    Paladin,
    Assassin,
    Necromancer,
    Huntress,
    Mystic,
    Trickster,
    Sorcerer,
    Ninja,
    Samurai,
    Bard,
    Summoner,
    Count
};

enum class PetFamily
{
    Any,
    Aquatic,
    Automaton,
    Avian,
    Canine,
    Exotic,
    Farm,
    Feline,
    Humanoid,
    Insect,
    Penguin,
    Reptile,
    Spooky,
    Woodland,
    Question,
    Count
};

enum class PetRarity
{
    Common,
    Uncommon,
    Rare,
    Legendary,
    Divine,
    Count
};
