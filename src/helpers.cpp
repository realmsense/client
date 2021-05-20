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