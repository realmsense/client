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

	this->skin_id = 0;

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
	static std::map<ClassList, std::vector<Skin*>> skin_list;
	static bool init = false;
	if (!init)
	{
		#include "../../other/skins.h"
		init = true;
	}

	static int img_size = 30;
	ImGui::SliderInt("Icon Size", &img_size, 0, 100);

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

	for (int i = 0; i < skin_list[current_class].size(); i++)
	{
		Skin* skin = skin_list[current_class][i];
		void* texture_id = (void*)skin->load();
		if (!texture_id) continue;

		if (ImGui::ImageButton(texture_id, ImVec2(img_size, img_size)))
		{
			this->changeSkin(skin->skin_id);
			this->log << "Changed Skin to " << skin->name << " (" << skin->skin_id << ")" << std::endl;
			this->enabled = true;
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(skin->name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}

		GUI_WrapInLoop(i, skin_list[current_class].size());
	}
}

void SkinChangerModule::changeSkin(int skin_id)
{
	this->skin_id = skin_id;

	JFNHHLNJJKP* player = GetPlayer();
	if (!player) return;

	((LAAIPMHLFJN*)player)->fields.PHNLNOOLAIO = this->skin_id;

	// TODO: store old skin id so we can toggle enable
}
