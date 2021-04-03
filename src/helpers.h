#include <vector>

void CreateConsole();
void RemoveConsole();

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);