#pragma once

#include <string>

using namespace app;

uintptr_t GetBaseAddress();
void CreateConsole();
void RemoveConsole();

float CalculateDistance(Vector2 a, Vector2 b);

std::string il2cppi_to_string(Il2CppString* str);
std::string il2cppi_to_string(String* str);

Object* FindObjectByQualifiedName(const char* assemblyQualifiedName);
Camera* GetMainCamera();
Player* GetPlayer();
Pet* GetPet();
Vector2 GetEntityPos(BasicObject* entity);
EquipmentSlot* GetEquipmentSlot(int index);
void ShowFloatingText(const char* message, FloatingTextType type, __int64 color);