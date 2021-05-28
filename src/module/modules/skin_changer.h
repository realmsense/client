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
    void onSpriteShader_UpdateMask(app::SpriteShader* sprite_shader, int32_t& large_cloth, int32_t& small_cloth) override;

private:
	int player_skin_id;
    int old_player_skin_id;
    int large_outfit;
    int small_outfit;

    app::Pet* pet;
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
