#include "pch.h"
#include "../module.h"
#include "../module_manager.h"

#include "imgui/imgui.h"
#include "unlimited_zoom.h"

UnlimitedZoomModule::UnlimitedZoomModule()
    : Module()
{
    this->name = "Unlimited Zoom";
    this->enabled = false;
    this->type = ModuleList::UnlimitedZoom;
    this->category = ModuleCategory::VIEW;
    this->hasGuiElements = true;

    this->zoomAmount = 7.2f;
    this->perspectiveEditorEnabled = false;
    this->cameraPerspectiveEditor = 0;

    this->ready();
}

void UnlimitedZoomModule::onEnable()
{
    this->log.color = Color32_GREEN;
    this->log.floatingText = true;
    this->log << this->name << " enabled" << std::endl;
}

void UnlimitedZoomModule::onDisable()
{
    this->log.color = Color32_RED;
    this->log.floatingText = true;
    this->log << this->name << " disabled" << std::endl;
}

void UnlimitedZoomModule::renderGUI()
{
    if (ImGui::SliderFloat("Zoom Amount", &this->zoomAmount, 0.0f, 20.0f))
        this->Zoom(this->zoomAmount);

    if (ImGui::Checkbox("Perspective Editor", &this->perspectiveEditorEnabled))
        this->TogglePerspectiveEditor(this->perspectiveEditorEnabled);
}

bool UnlimitedZoomModule::onEvent(ModuleEvent event, CDataPack* dp)
{
    switch (event)
    {
    case ModuleEvent::CameraManager_Update:
        return this->onCameraManagerUpdate();
    default:
        return true;
    }
}

bool UnlimitedZoomModule::onCameraManagerUpdate()
{
    uintptr_t cameraPerspectiveEditor = *(uintptr_t*)(g_pCameraManager + 0x48); // OOJJDIANIBF
    this->cameraPerspectiveEditor = cameraPerspectiveEditor;
    this->perspectiveEditorEnabled = Behaviour_get_enabled(cameraPerspectiveEditor);
    return true;
}

void UnlimitedZoomModule::Zoom(float amount)
{
    // TODO: GetObjectByType
    if (!g_pMainCamera)
    {
        std::cout << "[" << this->name << "] g_pMainCamera is nullptr!" << std::endl;
        return;
    }

    this->zoomAmount = amount;
    Camera_set_orthographicSize(g_pMainCamera, this->zoomAmount);
}

void UnlimitedZoomModule::TogglePerspectiveEditor(bool enabled)
{
    if (!this->cameraPerspectiveEditor)
    {
        std::cout << "[" << this->name << "] cameraPerspectiveEditor is nullptr!" << std::endl;
        return;
    }

    this->perspectiveEditorEnabled = enabled;
    Behaviour_set_enabled(this->cameraPerspectiveEditor, enabled);
}
