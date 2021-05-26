#include "pch.h"
#include "helpers.h"
#include "camera_settings.h"

#include "imgui/imgui.h"

CameraSettingsModule::CameraSettingsModule()
	: Module()
{
	this->name = "Camera Settings";
	this->enabled = false;
	this->category = ModuleCategory::VIEW;
	this->type = ModuleList::CameraSettings;
	this->has_gui_elements = true;

	this->zoom_amount = 7.2f;
	this->rotate_speed = 1.25f;

	this->ready();
}

void CameraSettingsModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void CameraSettingsModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void CameraSettingsModule::renderGUI()
{
	if (ImGui::SliderFloat("Zoom Amount", &this->zoom_amount, 0.01f, 20.0f))
	{
		Camera* camera = GetMainCamera();
		Camera_set_orthographicSize(camera, this->zoom_amount, nullptr);
		this->updatePositionShift();
		this->setEnabled(true);
	}

	if (ImGui::SliderFloat("Rotate Speed", &this->rotate_speed, 0.01f, 4.0f))
	{
		static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
		Settings* settings = game_controller->fields.settings;
		settings->fields.rotate_speed = this->rotate_speed;
		this->setEnabled(true);
	}

	if (ImGui::CollapsingHeader("Fog Settings"))
	{
		// TODO: needs cleaing up
		FogController* fog_controller = (*MapViewService__TypeInfo)->static_fields->DILPMFEEJCP;

		static float fog_range = 89.97056f;
		if (ImGui::SliderFloat("Fog Range", &fog_range, 0.0f, 400.0f))
			fog_controller->fields.fog_range = fog_range;

		static float fog_opacity = 9.485281f;
		if (ImGui::SliderFloat("Fog Opacity", &fog_opacity, 0.0f, 11.0f))
			fog_controller->fields.fog_opacity = fog_opacity;

		static float unloaded_tiles = 320.2829f;
		if (ImGui::SliderFloat("Unloaded Tiles", &unloaded_tiles, 0.0f, 600.0f))
			fog_controller->fields.unloaded_tile_distance = unloaded_tiles;

		static int view_distance = 17;
		if (ImGui::SliderInt("View Dist", &view_distance, 0, 20))
			(*FogController__TypeInfo)->static_fields->view_distance = view_distance;
	}
}

void CameraSettingsModule::updatePositionShift()
{
	// CameraManager_ONKBCEJOCH line 42 - https://i.imgur.com/cFtjAOh.png
	float orthographicSize = this->zoom_amount;
	float positionShift = (10.0f / orthographicSize) * 0.5f;

	static CameraManager* camera_manager = (CameraManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.CameraManager, Assembly-CSharp, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null");
	static CameraPerspectiveEditor* camera_perspective_editor = camera_manager->fields.perspective_editor;
	camera_perspective_editor->fields.positionShift.y = positionShift;
}