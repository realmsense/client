#include "pch.h"
#include "helpers.h"
#include "skin_changer.h"

#include "imgui/imgui.h"

Skin::Skin(std::string name, std::string file_name, int skin_id)
	: GuiImage(file_name)
{
	this->name = name;
	this->skin_id = skin_id;
}

SkinChangerModule::SkinChangerModule()
	: Module()
{
	this->name = "Skin Changer";
	this->enabled = false;
	this->category = ModuleCategory::VIEW;
	this->type = ModuleList::SkinChanger;
	this->has_gui_elements = true;

	this->pet = nullptr;
	this->player_skin_id = -1;
	this->large_outfit = -1;
	this->small_outfit = -1;
	this->pet_skin_id = -1;

	this->ready();
}

void SkinChangerModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;

	if (this->player_skin_id != -1)
		this->changePlayerSkin(this->player_skin_id);
}

void SkinChangerModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;

	this->changePlayerSkin(this->old_player_skin_id);
}

void SkinChangerModule::renderGUI()
{
	static int img_size = 30;
	ImGui::SliderInt("Icon Size", &img_size, 0, 100);

	if (ImGui::CollapsingHeader("Player Skin"))
	{
		static std::map<ClassList, std::vector<Skin*>> player_skins;
		static bool init = false;
		if (!init)
		{
			#include "../../other/player_skins.h"
			init = true;
		}

		const char* class_names[] = { "Any", "Rogue", "Archer", "Wizard", "Priest", "Warrior", "Knight", "Paladin", "Assassin", "Necromancer", "Huntress", "Mystic", "Trickster", "Sorcerer", "Ninja", "Samurai", "Bard", "Summoner" };
		static ClassList current_class = ClassList(0);
		for (int i = 0; i < (int)ClassList::Count; i++)
		{
			const char* class_name = class_names[i];
			if (ImGui::Button(class_name))
			{
				current_class = ClassList(i);
			}

			GUI_WrapInLoop(i, (int)ClassList::Count);
		}

		for (int i = 0; i < player_skins[current_class].size(); i++)
		{
			Skin* skin = player_skins[current_class][i];
			void* texture_id = (void*)skin->load();
			if (!texture_id) continue;

			if (ImGui::ImageButton(texture_id, ImVec2((float)img_size, (float)img_size)))
			{
				this->player_skin_id = skin->skin_id;
				this->changePlayerSkin(this->player_skin_id);
				this->log << "Changed Player Skin to " << skin->name << " (" << skin->skin_id << ")" << std::endl;
				this->setEnabled(true);
			}

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(skin->name.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			GUI_WrapInLoop(i, (int)player_skins[current_class].size());
		}
	}

	if (ImGui::CollapsingHeader("Outfit"))
	{
		if (ImGui::Button("Reset Small Outfit"))
			this->small_outfit = -1;

		ImGui::SameLine();

		if (ImGui::Button("Reset Large Outfit"))
			this->large_outfit = -1;

		static std::vector<Skin*> player_outfits;
		static bool init = false;
		if (!init)
		{
			#include "../../other/player_outfits.h"
			init = true;
		}

		for (int i = 0; i < player_outfits.size(); i++)
		{
			Skin* skin = player_outfits[i];
			void* texture_id = (void*)skin->load();
			if (!texture_id) continue;

			if (ImGui::ImageButton(texture_id, ImVec2((float)img_size, (float)img_size)))
			{
				if (skin->name.rfind("Small") == 0)
				{
					this->small_outfit = skin->skin_id;
					this->log << "Changed Small Outfit to " << skin->name << " (" << skin->skin_id << ")" << std::endl;

				}
				else if (skin->name.rfind("Large") == 0)
				{
					this->large_outfit = skin->skin_id;
					this->log << "Changed Large Outfit to " << skin->name << " (" << skin->skin_id << ")" << std::endl;
				}
				else
				{
					this->log.floatingText(Color32_BLUE);
					this->log << "Unknown outfit selected!" << std::endl;
				}

				this->setEnabled(true);
			}

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(skin->name.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			GUI_WrapInLoop(i, (int)player_outfits.size());
		}
	}

	if (ImGui::CollapsingHeader("Pet Skin"))
	{
		// [PetFamily][Rarity] = Skin[];
		static std::map <PetFamily, std::map<PetRarity, std::vector<Skin*>>> pet_skins;
		static bool init = false;
		if (!init)
		{
			#include "../../other/pet_skins.h"
			init = true;
		}

		const char* pet_families[] = { "Any", "Aquatic", "Automation", "Avian", "Canine", "Exotic", "Farm", "Feline", "Humanoid", "Insect", "Penguin", "Reptile", "Spooky", "Woodland", "? ? ? ?" };
		static PetFamily current_family = PetFamily(0);
		for (int i = 0; i < (int)PetFamily::Count; i++)
		{
			const char* pet_family = pet_families[i];
			if (ImGui::Button(pet_family))
			{
				current_family = PetFamily(i);
			}

			GUI_WrapInLoop(i, (int)PetFamily::Count);
		}

		const char* pet_rarities[] = { "Common", "Uncommon", "Rare", "Legendary", "Divine" };
		static PetRarity current_rarity = PetRarity(0);
		for (auto x : pet_skins[current_family])
		{
			PetRarity rarity = x.first;
			const char* rarity_name = pet_rarities[(int)rarity];
			 
			ImGui::Text(rarity_name);

			for (int i = 0; i < x.second.size(); i++)
			{
				Skin* skin = x.second[i];
				void* texture_id = (void*)skin->load();
				if (!texture_id) continue;

				if (ImGui::ImageButton(texture_id, ImVec2((float)img_size, (float)img_size)))
				{
					this->changePetSkin(skin->skin_id);
					this->log << "Changed Pet Skin to " << skin->name << " (" << skin->skin_id << ")" << std::endl;
					this->setEnabled(true);
				}

				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
					ImGui::TextUnformatted(skin->name.c_str());
					ImGui::PopTextWrapPos();
					ImGui::EndTooltip();
				}

				GUI_WrapInLoop(i, (int)x.second.size());
			}
		}
	}
}

void SkinChangerModule::onMapChange()
{
	if (Player* player = GetPlayer())
		this->old_player_skin_id = ((MapObject*)player)->fields.skin_id;

	if (!this->enabled) return;

	if (this->player_skin_id != -1)
		this->changePlayerSkin(this->player_skin_id);

	if (this->pet_skin_id != -1)
		this->changePetSkin(this->pet_skin_id);
}

void SkinChangerModule::onSpriteShader_UpdateMask(app::SpriteShader* sprite_shader, int32_t& large_cloth, int32_t& small_cloth)
{
	if (!this->enabled) return;

	BasicObject* player = (BasicObject*)GetPlayer();
	SpriteShader* player_spriteshader = player->fields.NJGEIJDFFND->fields.spriteShader;
	if (sprite_shader == player_spriteshader)
	{
		if (this->large_outfit != -1)
			large_cloth = this->large_outfit;

		if (this->small_outfit != -1)
			small_cloth = this->small_outfit;
	}
}

void SkinChangerModule::changePlayerSkin(int skin_id)
{
	Player* player = GetPlayer();
	if (!player) return;

	if (this->old_player_skin_id == -1)
		this->old_player_skin_id = ((MapObject*)player)->fields.skin_id;

	((MapObject*)player)->fields.skin_id = skin_id;
}


void SkinChangerModule::changePetSkin(int skin_id)
{
	static Pet* pet = this->pet;

	static Player* old_player = GetPlayer();
	Player* current_player = GetPlayer();
	if (!this->pet || old_player != current_player)
	{
		this->pet = GetPet();
		old_player = current_player;
	}

	this->pet_skin_id = skin_id;
	if (!this->pet)
	{
		this->log.floatingText(Color32_BLUE);
		this->log << "No Pet Found!" << std::endl;
		return;
	}

	Pet_ChangeSkin(this->pet, this->pet_skin_id, nullptr);
}