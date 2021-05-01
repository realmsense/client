#pragma once
#include <vector>
#include <string>

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanModIn(char* pattern, char* mask, std::string modName);
