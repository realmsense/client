#include "pch.h"
#include <sstream>

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
    const float diffX = a.x - b.x;
    const float diffY = a.y - b.y;
    return sqrt((diffX * diffX) + (diffY * diffY));
}

std::string PtrToHex(uintptr_t ptr)
{
    std::stringstream stream;
    stream << std::hex << ptr;
    std::string result(stream.str());
    return result;
}

std::string ReadUnityString(String* str)
{
    return ReadUnityString((uintptr_t)str);
}

std::string ReadUnityString(uintptr_t addr)
{
    std::stringstream sstream;
    const int length = *(int*)(addr + 0x10);
    for (int i = 0; i < length; i++)
    {
        const wchar_t charAt = *(wchar_t*)(addr + 0x14 + (0x2 * i));
        sstream << (char)charAt;
    }
    return sstream.str();
}

uintptr_t FindGameObject(const char* name)
{
    String* obj_name = il2cpp_string_new(name);
    const uintptr_t gameObject = GameObject_Find(obj_name);
    return gameObject;
}

uintptr_t FindObjectByQualifiedName(const char* assemblyQualifiedName)
{
    String* qualified_name = il2cpp_string_new(assemblyQualifiedName);
    const uintptr_t type = System_GetType(qualified_name);
    const uintptr_t obj = Object_FindObjectOfType(type);
    return obj;
}

std::vector<uintptr_t> GetChildTransforms(uintptr_t gameObject)
{
    std::vector<uintptr_t> vec;

    const uintptr_t main_transform = GameObject_GetTransform(gameObject);
    const int child_count = Transform_get_childCount(main_transform);
    for (int i = 0; i < child_count; i++)
    {
        uintptr_t child_transform = Transform_GetChild(main_transform, i);
        vec.push_back(child_transform);
    }

    return vec;
}

std::vector<uintptr_t> FindChildTransforms(uintptr_t parentTransform, std::vector<std::string> names)
{
    std::vector<uintptr_t> vec;
    for (auto& name : names)
    {
        String* str = il2cpp_string_new(name.c_str());
        uintptr_t childTransform = Transform_Find(parentTransform, str);
        vec.push_back(childTransform);
    }
    return vec;
}

void ShowFloatingText(const char* text, FloatingTextType type, __int64 colour)
{
    const uintptr_t guiManager = (uintptr_t)g_pPlayer->view_handler->gui_manager;
    String* msg = il2cpp_string_new(text);

    uintptr_t player = *(uintptr_t*)g_pPlayer;
    __ShowFloatingText(guiManager, type, msg, colour, 0.0f);
}
