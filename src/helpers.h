#include <vector>

void CreateConsole();
void RemoveConsole();

float CalculateDistance(Vector2 a, Vector2 b);

std::string PtrToHex(uintptr_t ptr);
std::string ReadUnityString(String* str);
void WriteUnityString(String* target, const char* source);


uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);

char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
char* ScanModIn(char* pattern, char* mask, std::string modName);
