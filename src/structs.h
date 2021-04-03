#include <cstdint>

struct Vector3 { float x, y, z; };

class Player
{
public:
    char pad_0000[56]; //0x0000
    int32_t N000000F1; //0x0038
    Vector3 pos; //0x003C
    char pad_0048[32]; //0x0048
    Vector3 pos2; //0x0068
    char pad_0074[344]; //0x0074
    int32_t maxHP; //0x01CC
    int32_t hp; //0x01D0
    char pad_01D4[644]; //0x01D4
    int32_t maxMP; //0x0458
    float mp; //0x045C
    char pad_0460[1040]; //0x0460
}; //Size: 0x0870
