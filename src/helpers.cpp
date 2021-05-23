#include "pch.h"
#include <codecvt>

using namespace app;

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

Object_1* FindObjectByQualifiedName(const char* assemblyQualifiedName)
{
    String* qualified_name = (String*)il2cpp_string_new(assemblyQualifiedName);
    Type* type = Type_GetType_2(qualified_name, nullptr);
    Object_1* object = Object_1_FindObjectOfType(type, nullptr);
    return object;
}

Camera* GetMainCamera()
{
    static GameController* game_controller = (GameController*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.Game.GameController, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static Camera* main_camera = game_controller->fields.mainCamera;
    return main_camera;
}

JFNHHLNJJKP* GetPlayer()
{
    static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static DKMLMKFGPCC* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);
    JFNHHLNJJKP* player = map_view_service->fields.HFLGDFNPKPM;
    return player;
}

DAFEAHGLBGL* GetPet()
{
    // Really hard to get pet
    // There's a list of pets (and other objects) in DKMLMKFGPCC.
    // We can get the ObjectProps for our pet's ToolTip through: DKMLMKFGPCC->EFNINMGLFDC->HMLEONMOKBC->NLODPDOFMKB
    // so we just iterate the list and check if the object props are the same object.

    static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static DKMLMKFGPCC* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);
    JFNHHLNJJKP* player = GetPlayer();

    ObjectProperties* pet_skin_props1 = map_view_service->fields.EFNINMGLFDC->fields.HMLEONMOKBC->fields.NLODPDOFMKB;

    auto list = map_view_service->fields.CIEBEOHNLJM;
    auto items = list->fields._items->vector;
    for (int i = 0; i < list->fields._size; i++)
    {
        NIIFJAMEHDD* character = items[i];
        DAFEAHGLBGL* pet = (DAFEAHGLBGL*)character; // casting non types

        ObjectProperties* pet_skin_props2 = pet->fields.BKHBOCPPAOM;

        if (pet_skin_props1 == pet_skin_props2)
            return pet;
    }

    return nullptr;
}

Vector2 GetEntityPos(GJLIMCBOCJG* entity)
{
    float pos_x = entity->fields.EOOJAMLJAOM;
    float pos_y = entity->fields.JDEKCEFBJFP;
    Vector2 pos = { pos_x, pos_y };
    return pos;
}

void ShowFloatingText(const char* message, CLEPBEMBHAJ__Enum type, __int64 color)
{
    JFNHHLNJJKP* player = GetPlayer();
    if (!player) return;

    static ApplicationManager* application_manager = (ApplicationManager*)FindObjectByQualifiedName("DecaGames.RotMG.Managers.ApplicationManager, Assembly-CSharp, Version=3.7.1.6, Culture=neutral, PublicKeyToken=null");
    static DKMLMKFGPCC* map_view_service = ApplicationManager_get_MapViewService(application_manager, nullptr);

    ViewHandler* view_handler = reinterpret_cast<GJLIMCBOCJG*>(player)->fields.NJGEIJDFFND;
    MapObjectUIManager* gui_manager = view_handler->fields.GUIManager;
    String* text = reinterpret_cast<String*>(il2cpp_string_new(message));

    MapObjectUIManager_ShowFloatingText(gui_manager, type, text, color, 0.0f, nullptr);
}