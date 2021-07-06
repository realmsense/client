#include "pch.h"
#include "helpers.h"
#include "skin_changer.h"
#include "gui/gui_image.h"

#include "thirdparty/imgui/imgui.h"

#include "other/skins/player_skins_bytes.h"
#include "other/skins/player_textiles_bytes.h"
#include "other/skins/pet_skins_bytes.h"

Skin::Skin(std::string name, std::string file_name, int skin_id)
	: GuiImage(file_name)
{
	this->name = name;
	this->skin_id = skin_id;
}

Skin::Skin(std::string name, unsigned char* bytes, int bytes_len, int skin_id)
	: GuiImage(bytes, bytes_len)
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
	this->rainbow_oufit = false;
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

	// TODO: too much duplicate code, probably have to break it out into multiple functions

	if (ImGui::CollapsingHeader("Player Skin"))
	{
		static std::map<ClassList, std::vector<Skin*>> player_skins;
		static bool init = false;
		if (!init)
		{
			#include "other/skins/player_skins_init.h"
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
		{
			this->small_outfit = 0x0;
			this->setEnabled(true);
		}

		ImGui::SameLine();

		if (ImGui::Button("Reset Large Outfit"))
		{
			this->large_outfit = 0x0;
			this->setEnabled(true);
		}
	
		ImGuiColorEditFlags coloredit_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_DisplayRGB;

		static float small_dye[3];
		if (ImGui::ColorEdit3("Small Dye", small_dye, coloredit_flags))
		{
			this->small_outfit = this->RGBToDye(small_dye);
			this->setEnabled(true);
		}

		ImGui::SameLine();

		static float large_dye[3];
		if (ImGui::ColorEdit3("Large Dye", large_dye, coloredit_flags))
		{
			this->large_outfit = this->RGBToDye(large_dye);
			this->setEnabled(true);
		}

		ImGui::SameLine();

		if (ImGui::Checkbox("Rainbow Outfit", &this->rainbow_oufit))
		{
			if (!this->rainbow_oufit)
			{
				this->small_outfit = 0x0;
				this->large_outfit = 0x0;
			}
			this->setEnabled(true);
		}

		static std::vector<Skin*> player_textiles;
		static bool init = false;
		if (!init)
		{
			#include "other/skins/player_textiles_init.h"
			init = true;
		}
	
		for (int i = 0; i < player_textiles.size(); i++)
		{
			Skin* skin = player_textiles[i];
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
	
			GUI_WrapInLoop(i, (int)player_textiles.size());
		}
	}

	if (ImGui::CollapsingHeader("Pet Skin"))
	{
		// [PetFamily][Rarity] = Skin[];
		static std::map <PetFamily, std::map<PetRarity, std::vector<Skin*>>> pet_skins;
		static bool init = false;
		if (!init)
		{
			#include "other/skins/pet_skins_init.h"
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

unsigned int SkinChangerModule::RGBToDye(float color[3])
{
	int r = (int)(color[0] * 255);
	int g = (int)(color[1] * 255);
	int b = (int)(color[2] * 255);

	unsigned int hex = (0x01 << 24) | (r << 16) | (g << 8) | b;
	return hex;
}

void SkinChangerModule::onMapChange()
{
	if (Player* player = GetPlayer())
		this->old_player_skin_id = player->fields._._.skin_id;

	if (!this->enabled) return;

	if (this->player_skin_id != -1)
		this->changePlayerSkin(this->player_skin_id);

	if (this->pet_skin_id != -1)
		this->changePetSkin(this->pet_skin_id);
}

void SkinChangerModule::onMainLoop()
{
	if (!this->enabled) return;

	if (this->rainbow_oufit)
	{
		static float hue = 1.0f;
		static float speed = 0.0035f;
		hue += speed;
		if (hue > 360.0f) hue = 1.0f;
		ImVec4 rainbow = (ImVec4)(ImColor)ImColor::HSV(hue, 1.0f, 1.0f);

		float color[3] = { rainbow.x, rainbow.y, rainbow.z };
		this->small_outfit = RGBToDye(color);
		this->large_outfit = RGBToDye(color);
	}
}

void SkinChangerModule::onSpriteShader_UpdateMask(SpriteShader* sprite_shader, int32_t& large_cloth, int32_t& small_cloth)
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
		this->old_player_skin_id = player->fields._._.skin_id;

	player->fields._._.skin_id = skin_id;
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