#pragma once

#include <string>

using namespace app;

uintptr_t GetBaseAddress();
void CreateConsole();
void RemoveConsole();

std::string il2cppi_to_string(Il2CppString* str);
std::string il2cppi_to_string(String* str);

Object_1* FindObjectByQualifiedName(const char* assemblyQualifiedName);
JFNHHLNJJKP* GetPlayer();