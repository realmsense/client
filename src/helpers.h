#include <vector>

void CreateConsole();
void RemoveConsole();

float CalculateDistance(Vector2 a, Vector2 b);

std::string PtrToHex(uintptr_t ptr);
std::string ReadUnityString(String* str);
void WriteUnityString(String* target, const char* source);

uintptr_t FindGameObject(const char* name);
std::vector<uintptr_t> GetChildTransforms(uintptr_t gameObject);

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

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanModIn(char* pattern, char* mask, std::string modName);
