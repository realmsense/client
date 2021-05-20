#pragma once

#include <string>

uintptr_t GetBaseAddress();
void CreateConsole();
void RemoveConsole();

std::string il2cppi_to_string(Il2CppString* str);
std::string il2cppi_to_string(app::String* str);