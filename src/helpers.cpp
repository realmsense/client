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
    float diffX = a.x - b.x;
    float diffY = a.y - b.y;
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
    int length = *(int*)(addr + 0x10);
    for (int i = 0; i < length; i++)
    {
        wchar_t charAt = *(wchar_t*)(addr + 0x14 + (0x2 * i));
        sstream << (char)charAt;
    }
    return sstream.str();
}

uintptr_t FindGameObject(const char* name)
{
    String* objName = il2cpp_string_new(name);
    uintptr_t gameObject = GameObject_Find(objName);
    return gameObject;
}

std::vector<uintptr_t> GetChildTransforms(uintptr_t gameObject)
{
    std::vector<uintptr_t> vec;

    uintptr_t mainTransform = GameObject_GetTransform(gameObject);
    int childCount = Transform_get_childCount(mainTransform);
    for (int i = 0; i < childCount; i++)
    {
        uintptr_t childTransform = Transform_GetChild(mainTransform, i);
        vec.push_back(childTransform);
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

void ShowFloatingText(const char* text, FloatingText type, __int64 colour)
{
    uintptr_t guiManager = (uintptr_t)g_pPlayer->viewHandler->guiManager;
    String* msg = il2cpp_string_new(text);

    uintptr_t player = *(uintptr_t*)g_pPlayer;
    __ShowFloatingText(guiManager, type, msg, colour, 0.0f);
}
