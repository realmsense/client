#include "pch.h"
#include <vector>
#include "fake_ntdl.h"

#include <sstream>
#include <locale>
#include <codecvt>

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
    uintptr_t addr = (uintptr_t)str;
    std::stringstream sstream;
    int length = str->length;
    for (int i = 0; i < length; i++) {
        wchar_t charAt = *(wchar_t*)(addr + 0x14 + (0x2 * i));
        sstream << (char)charAt;
    }
    return sstream.str();
}

String* CreateUnityString(const char* str)
{
    // 0x14 is where the string's value is stored
    // 0x2 is the size of each wchar_t
    size_t size = 0x14 + (0x2 * strlen(str));
    void* addr = malloc(size);

    // Use placement new to not allocate memory - https://stackoverflow.com/q/29327950
    String* string = new(addr) String();
    WriteUnityString(string, str);
    return string;
}

void WriteUnityString(String* target, const char* source)
{
    uintptr_t addr = (uintptr_t)target;
    size_t length = strlen(source);
    target->length = length;
    for (int i = 0; i < length; i++)
    {
        *(wchar_t*)(addr + 0x14 + (0x2 * i)) = (char)source[i];
    }
}

uintptr_t FindGameObject(const char* name)
{
    String objName;
    WriteUnityString(&objName, name);
    uintptr_t gameObject = GameObject_Find(&objName);
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
        String str;
        WriteUnityString(&str, name.c_str());
        uintptr_t childTransform = Transform_Find(parentTransform, &str);
        vec.push_back(childTransform);
    }
    return vec;
}

void ResizeCharacter(uintptr_t characterTransform, Vector3 newScale)
{
    std::vector<std::string> names { "Content", "CharacterGUI", "Shadow" };
    std::vector<uintptr_t> transformList = FindChildTransforms(characterTransform, names);
    for (int i = 0; i < transformList.size(); i++)
        Transform_set_localScale(transformList[i], newScale);
}

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }
    return addr;
}

char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
{
    intptr_t patternLen = strlen(mask);

    for (size_t i = 0; i < size; i++)
    {
        bool found = true;
        for (int j = 0; j < patternLen; j++)
        {
            if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            return (begin + i);
    }
}
    return nullptr;
}

char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size)
{
    char* match{ nullptr };
    MEMORY_BASIC_INFORMATION mbi{};

    for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
    {
        if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

        match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

        if (match != nullptr)
        {
            break;
        }
    }
    return match;
}

char* TO_CHAR(wchar_t* string)
{
    size_t len = wcslen(string) + 1;
    char* c_string = new char[len];
    size_t numCharsRead;
    wcstombs_s(&numCharsRead, c_string, len, string, _TRUNCATE);
    return c_string;
}

PEB* GetPEB()
{
#ifdef _WIN64
    PEB* peb = (PEB*)__readgsqword(0x60);

#else
    PEB* peb = (PEB*)__readfsdword(0x30);
#endif

    return peb;
}

LDR_DATA_TABLE_ENTRY* GetLDREntry(std::string name)
{
    LDR_DATA_TABLE_ENTRY* ldr = nullptr;
    PEB* peb = GetPEB();

    LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;
    LIST_ENTRY curr = head;

    while (curr.Flink != head.Blink)
    {
        LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        if (mod->FullDllName.Buffer)
        {
            char* cName = TO_CHAR(mod->BaseDllName.Buffer);

            if (_stricmp(cName, name.c_str()) == 0)
            {
                ldr = mod;
                break;
            }
            delete[] cName;
        }
        curr = *curr.Flink;
    }
    return ldr;
}

char* ScanModIn(char* pattern, char* mask, std::string modName)
{
    LDR_DATA_TABLE_ENTRY* ldr = GetLDREntry(modName);

    char* match = ScanInternal(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);

    return match;
}

