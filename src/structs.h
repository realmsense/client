#include <cstdint>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

typedef uintptr_t (__cdecl* GetMainCamera)(void);

class String
{
public:
    char pad_0000[16]; //0x0000
    int32_t length; //0x0010
    wchar_t value[8]; //0x0014
}; //Size: 0x0024

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

class Player
{
public:
    char pad_0000[60]; //0x0000
    Vector2 pos; //0x003C
    char pad_0044[20]; //0x0044
    class Tile* standingTile; //0x0058
    char pad_0060[248]; //0x0060
    class String* name; //0x0158
    char pad_0160[108]; //0x0160
    int32_t maxHP; //0x01CC
    int32_t hp; //0x01D0
    char pad_01D4[464]; //0x01D4
    int32_t attack; //0x03A4
    float speed; //0x03A8
    float dexterity; //0x03AC
    int32_t vitality; //0x03B0
    int32_t wisdom; //0x03B4
    char pad_03B8[80]; //0x03B8
    int32_t defense; //0x0408
    char pad_040C[76]; //0x040C
    int32_t maxMP; //0x0458
    float mp; //0x045C
    char pad_0460[8280]; //0x0460
}; //Size: 0x24B8

class OBGKICHNIDN
{
public:
    char pad_0000[56]; //0x0000
    class String* name; //0x0038
}; //Size: 0x0040

// UnityEngine.Camera.get_main
#define OFFSET_GET_MAINCAMERA 0x220fc10

// UnityEngine.Camera.set_orthographicSize
#define OFFSET_SET_ORTHOGRAPHICSIZE 0x2210430

// DecaGames.RotMG.Managers.CameraManager.Update
#define OFFSET_CAMERAMANAGER_UPDATE 0x301a70

// UnityEngine.SpriteRenderer.set_color
#define OFFSET_SPRITE_SET_COLOR 0x209c7c0

// DecaGames.RotMG.Extensions.UnityThread.Update
#define OFFSET_UNITYTHREAD_UPDATE 0x498900

// JFNHHLNJJKP.JJCAKPHMLKD - random method that runs every tick to get player
#define OFFSET_GETPLAYER 0x2f2850

// UnityEngine.Behaviour.set_enabled
#define OFFSET_BEHAVIOUR_SET_ENABLED 0x220d5f0

// UnityEngine.Behaviour.get_enabled
#define OFFSET_BEHAVIOUR_GET_ENABLED 0x220d570

// UnityEngine.Camera.WorldToScreenPoint
#define OFFSET_WORLD_TO_SCREEN 0x220f640

// UnityEngine.Camera.ScreenToWorldPoint
#define OFFSET_SCREEN_TO_WORLD 0x220f230
