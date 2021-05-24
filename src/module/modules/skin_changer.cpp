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
	this->player_skin_id = 0;
	this->pet_skin_id = 0;

	this->ready();
}

void SkinChangerModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void SkinChangerModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
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
				this->changePlayerSkin(skin->skin_id);
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
	if (!this->enabled) return;

	if (this->player_skin_id != 0)
		this->changePlayerSkin(this->player_skin_id);

	if (this->pet_skin_id != 0)
		this->changePetSkin(this->pet_skin_id);
}

void SkinChangerModule::changePlayerSkin(int skin_id)
{
	this->player_skin_id = skin_id;

	JFNHHLNJJKP* player = GetPlayer();
	if (!player) return;

	((LAAIPMHLFJN*)player)->fields.PHNLNOOLAIO = this->player_skin_id;

	// TODO: store old skin id so we can toggle enable
}


void SkinChangerModule::changePetSkin(int skin_id)
{
	static DAFEAHGLBGL* pet = this->pet;

	static JFNHHLNJJKP* old_player = GetPlayer();
	JFNHHLNJJKP* current_player = GetPlayer();
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

	DAFEAHGLBGL_KOBJNFBMICI(this->pet, this->pet_skin_id, nullptr);
}