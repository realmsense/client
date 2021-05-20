// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#include "pch.h"
#include "helpers.h"
#include <codecvt>

// Helper function to get the module base address
uintptr_t il2cppi_get_base_address() {
    return (uintptr_t) GetModuleHandleW(L"GameAssembly.dll");
}

// Helper function to open a new console window and redirect stdout there
void il2cppi_new_console() {
    AllocConsole();
    freopen_s((FILE**) stdout, "CONOUT$", "w", stdout);
}

#if _MSC_VER >= 1920
// Helper function to convert Il2CppString to std::string
std::string il2cppi_to_string(Il2CppString* str) {
    std::u16string u16(reinterpret_cast<const char16_t*>(str->chars));
    return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
}

// Helper function to convert System.String to std::string
std::string il2cppi_to_string(app::String* str) {
    return il2cppi_to_string(reinterpret_cast<Il2CppString*>(str));
}
#endif