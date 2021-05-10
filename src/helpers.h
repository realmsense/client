#pragma once

void CreateConsole();
void RemoveConsole();

float CalculateDistance(Vector2 a, Vector2 b);

std::string PtrToHex(uintptr_t ptr);
std::string ReadUnityString(String* str);
std::string ReadUnityString(uintptr_t addr);

uintptr_t FindGameObject(const char* name);
uintptr_t FindObjectByQualifiedName(const char* assemblyQualifiedName);
std::vector<uintptr_t> GetChildTransforms(uintptr_t gameObject);
std::vector<uintptr_t> FindChildTransforms(uintptr_t parentTransform, std::vector<std::string> names);

void ResizeCharacter(uintptr_t characterTransform, Vector3 newScale);

template<class T>
std::vector<T> ReadUnityList(List* source)
{
    std::vector<T> arr;
    int length = source->size;
    uintptr_t addr = (uintptr_t)source->items;
    for (int i = 0; i < length; i++)
    {
        T item = *(T*)(addr + 0x20 + (0x8 * i));
        arr.push_back(item);
    }
    return arr;
}

void ShowFloatingText(const char* text, FloatingTextType type, __int64 colour);
