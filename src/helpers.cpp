#include "pch.h"
#include <codecvt>

uintptr_t GetBaseAddress()
{
    return (uintptr_t)GetModuleHandle(L"GameAssembly.dll");
}

void CreateConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

void RemoveConsole()
{
    fclose(stdout);
    FreeConsole();
}

float CalculateDistance(Vector2 a, Vector2 b)
{
    const float diff_x = a.x - b.x;
    const float diff_y = a.y - b.y;
    return sqrt((diff_x * diff_x) + (diff_y * diff_y));
}

// Convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str)
{
    std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

// Convert System.String to std::string - can simply be casted
std::string il2cppi_to_string(String* str)
{
    return il2cppi_to_string(reinterpret_cast<Il2CppString*>(str));
}

Object* FindObjectByQualifiedName(const char* assemblyQualifiedName)
{
    String* qualified_name = (String*)il2cpp_string_new(assemblyQualifiedName);
    Type* type = Type_GetType(qualified_name, nullptr);
    Object* object = Object_FindObjectOfType(type, nullptr);
    return object;
}

Camera* GetMainCamera()
{
    static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static Camera* main_camera = game_controller->fields.mainCamera;
    return main_camera;
}

Player* GetPlayer()
{
    static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static MapViewService* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);
    Player* player = map_view_service->fields.player;
    return player;
}

Pet* GetPet()
{
    // Really hard to get pet
    // There's a list of pets (and other objects) in MapViewService.
    // We can get the ObjectProps for our pet's ToolTip through: MapViewService->EFNINMGLFDC->HMLEONMOKBC->NLODPDOFMKB
    // so we just iterate the list and check if the object props are the same object.

    //static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    //static MapViewService* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);
    //Player* player = GetPlayer();
    //
    //ObjectProperties* pet_skin_props1 = map_view_service->fields.EFNINMGLFDC->fields.HMLEONMOKBC->fields.NLODPDOFMKB;
    //
    //auto list = map_view_service->fields.CIEBEOHNLJM;
    //auto items = list->fields._items->vector;
    //for (int i = 0; i < list->fields._size; i++)
    //{
    //    NIIFJAMEHDD* character = items[i];
    //    Pet* pet = (Pet*)character; // casting non types
    //
    //    ObjectProperties* pet_skin_props2 = pet->fields.object_props;
    //
    //    if (pet_skin_props1 == pet_skin_props2)
    //        return pet;
    //}
    //
    return nullptr;
}

Vector2 GetEntityPos(BasicObject* entity)
{
    float pos_x = entity->fields.EOOJAMLJAOM;
    float pos_y = entity->fields.JDEKCEFBJFP;
    Vector2 pos = { pos_x, pos_y };
    return pos;
}

EquipmentSlot* GetEquipmentSlot(int index)
{
    static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    EquipmentManager* equipment_manager = game_controller->fields.equipmentManager;
    EquipmentSlot** items = equipment_manager->fields.equipmentSlots->vector;
    return items[index];
}

void ShowFloatingText(const char* message, FloatingTextType type, __int64 color)
{
    Player* player = GetPlayer();
    if (!player) return;

    static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static MapViewService* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);

    ViewHandler* view_handler = player->fields._._._.NJGEIJDFFND;
    MapObjectUIManager* gui_manager = view_handler->fields.GUIManager;
    String* text = reinterpret_cast<String*>(il2cpp_string_new(message));

    MapObjectUIManager_ShowFloatingText(gui_manager, type, text, color, 0.0f, nullptr);
}

bool GetKeyDown(SettingsKeyCode code)
{
    static SettingsManager* settings_manager = (SettingsManager*)FindObjectByQualifiedName("DecaGames.RotMG.UI.Managers.SettingsManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    KeyCode key_code = SettingsManager_GetKeyCode(settings_manager, code, nullptr);
    return Input_GetKey(key_code, nullptr);
}

bool GetKeyDown(KeyCode code)
{
    return Input_GetKey(code, nullptr);
}