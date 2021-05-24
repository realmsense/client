#include "pch.h"
#include "helpers.h"
#include "unlimited_zoom.h"

#include "imgui/imgui.h"

UnlimitedZoomModule::UnlimitedZoomModule()
	: Module()
{
	this->name = "Unlimited Zoom";
	this->enabled = false;
	this->category = ModuleCategory::VIEW;
	this->type = ModuleList::UnlimitedZoom;
	this->has_gui_elements = true;
	this->ready();
}

void UnlimitedZoomModule::onEnable()
{
	this->log.floatingText(Color32_GREEN);
	this->log << this->name << " ON" << std::endl;
}

void UnlimitedZoomModule::onDisable()
{
	this->log.floatingText(Color32_RED);
	this->log << this->name << " OFF" << std::endl;
}

void UnlimitedZoomModule::renderGUI()
{
	if (ImGui::SliderFloat("Zoom Amount", &this->zoom, 0.01f, 20.0f))
	{
		Camera* camera = GetMainCamera();
		Camera_set_orthographicSize(camera, this->zoom, nullptr);
		this->updatePositionShift();
		this->setEnabled(true);
	}
}

void UnlimitedZoomModule::updatePositionShift()
{
	// CameraManager_ONKBCEJOCH line 42 - https://i.imgur.com/cFtjAOh.png
	float orthographicSize = this->zoom;
	float positionShift = (10.0 / orthographicSize) * 0.5;

	static CameraManager* camera_manager = (CameraManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.CameraManager, Assembly-CSharp, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null");
	static CameraPerspectiveEditor* camera_perspective_editor = camera_manager->fields.OOJJDIANIBF;
	camera_perspective_editor->fields.positionShift.y = positionShift;
}