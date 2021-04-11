#include <cstdint>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

typedef uintptr_t* (__cdecl* GetMainCamera)(void);
typedef Vector3 (__cdecl* WorldToScreenPoint)(void* camera, Vector3 position);
typedef void* (__cdecl* Camera_set_orthographicSize)(void* __this, float zoomAmount);

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

//UnityEngine.Camera.get_main
#define OFFSET_GET_MAINCAMERA 0x220fc10

//DecaGames.RotMG.Extensions.UnityThread.Update
#define OFFSET_UNITYTHREAD_UPDATE 0x498900

// LAAIPMHLFJN.ADGGLKHIJFF - random method that runs every tick to get player
#define OFFSET_GETPLAYER 0x392670

// DecaGames.RotMG.Managers.Net.SocketManager.GotMessageHandler
#define OFFSET_RECIEVE_PACKET 0x64fa40

// DecaGames.RotMG.Managers.Net.SocketManager.GotMessageHandler
#define OFFSET_SEND_PACKET 0x650e40

class Player2
{
public:
    char pad_0000[60]; //0x0000
    Vector2 pos; //0x003C
    char pad_0044[20]; //0x0044
    class Tile* standingTile; //0x0058
    char pad_0060[9092]; //0x0060
}; //Size: 0x23E4

class String
{
public:
    char pad_0000[16]; //0x0000
    int32_t length; //0x0010
    wchar_t value[255]; //0x0014
}; //Size: 0x002E

class Tile
{
public:
    char pad_0000[60]; //0x0000
    int32_t posX; //0x003C
    int32_t posY; //0x0040
    char pad_0044[20]; //0x0044
    class OBGKICHNIDN* OBGKICHNIDN; //0x0058
    char pad_0060[1000]; //0x0060
}; //Size: 0x0448

class OBGKICHNIDN
{
public:
    char pad_0000[56]; //0x0000
    class String* name; //0x0038
}; //Size: 0x0040
