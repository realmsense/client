#include <cstdint>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

enum AutoAimTarget
{
    ClosestMouse,
    ClosestPos,
    HighestDef,
    HighestMaxHP
};

enum class EntityType : int32_t
{
    BasicMapObject          = 0,
    Projectile              = 1,
    Particle                = 2,
    ParticleEffect          = 3,
    MapObject               = 4,
    ArenaPortal             = 5,
    CaveWall                = 6,
    Character               = 7,
    CharacterChanger        = 8,
    ClosedGiftChest         = 9,
    ClosedVaultChest        = 10,
    ConnectedObject         = 11,
    ConnectedWall           = 12,
    Container               = 13,
    DailyLoginRewards       = 14,
    GuildHallPortal         = 15,
    GuildRegister           = 16,
    GuildBoard              = 17,
    GuildChronicle          = 18,
    GuildMerchant           = 19,
    Merchant                = 20,
    MoneyChanger            = 21,
    MysteryBoxGround        = 22,
    NameChanger             = 23,
    OneWayContainer         = 24,
    Pet                     = 25,
    PetUpgrader             = 26,
    Player                  = 27,
    Portal                  = 28,
    ReskinVendor            = 29,
    QuestRewards            = 30,
    SellableObject          = 31,
    SpiderWeb               = 32,
    Stalagmite              = 33,
    Sign                    = 34,
    Wall                    = 35,
    YardUpgrader            = 36,
    DoubleWall              = 37,
    Empty                   = 38,
    WallOfFame              = 39,
    VaultGiftContainer      = 40,
    VaultContainer          = 41,
    PremiumVaultContainer   = 42,
    Blacksmith              = 43
};

class Entity
{
public:
    char pad_0000[24];                      /*0x0000*/
    class ObjectProperties* objectProps;    /*0x0018*/  char pad_0020[28];      /*0x0020*/
    Vector2 pos;                            /*0x003C*/  char pad_0044[20];      /*0x0044*/
    class Tile* standingTile;               /*0x0058*/
    bool alive;                             /*0x0060*/  char pad_0061[91];      /*0x0061*/
    EntityType entityType;                  /*0x00BC*/  char pad_00C0[152];     /*0x00C0*/
    class String* name;                     /*0x0158*/  char pad_0160[108];     /*0x0160*/
    int32_t maxHP;                          /*0x01CC*/
    int32_t hp;                             /*0x01D0*/  char pad_01D4[464];     /*0x01D4*/
    int32_t attack;                         /*0x03A4*/
    float speed;                            /*0x03A8*/
    float dexterity;                        /*0x03AC*/
    int32_t vitality;                       /*0x03B0*/
    int32_t wisdom;                         /*0x03B4*/  char pad_03B8[80];      /*0x03B8*/
    int32_t defense;                        /*0x0408*/  char pad_040C[76];      /*0x040C*/
    int32_t maxMP;                          /*0x0458*/
    float mp;                               /*0x045C*/  char pad_0460[8280];    /*0x0460*/
}; //Size: 0x24B8

class Tile
{
public:
    char pad_0000[60];                      /*0x0000*/
	int32_t posX;                           /*0x003C*/
	int32_t posY;                           /*0x0040*/  char pad_0044[20];      /*0x0044*/
	class ObjectProperties *OBGKICHNIDN;    /*0x0058*/  char pad_0060[1000];    /*0x0060*/
}; //Size: 0x0448

class ObjectProperties
{
public:
    char pad_0000[56];                      /*0x0000*/
	class String *name;                     /*0x0038*/
}; //Size: 0x0040

class String
{
public:
    char pad_0000[16];                      /*0x0000*/
	int32_t length;                         /*0x0010*/
	wchar_t value[8];                       /*0x0014*/
}; //Size: 0x0024

// Global Functions
typedef uintptr_t(__cdecl* _GetMainCamera)(void);
typedef void* (__cdecl* _Camera_set_orthographicSize)(uintptr_t UnityEngine_Camera, float amount);
typedef void* (__cdecl* _Behaviour_set_enabled)(uintptr_t __this, bool value);
typedef bool(__cdecl* _Behaviour_get_enabled)(uintptr_t __this);
typedef Vector3(__cdecl* _WorldToScreen)(uintptr_t camera, Vector3 position);
typedef Vector3(__cdecl* _ScreenToWorld)(uintptr_t camera, Vector3 position);

// Offsets
#define OFFSET_GET_MAINCAMERA 0x220fc10         // UnityEngine.Camera.get_main
#define OFFSET_SET_ORTHOGRAPHICSIZE 0x2210430   // UnityEngine.Camera.set_orthographicSize
#define OFFSET_WORLD_TO_SCREEN 0x220f640        // UnityEngine.Camera.WorldToScreenPoint
#define OFFSET_SCREEN_TO_WORLD 0x220f230        // UnityEngine.Camera.ScreenToWorldPoint
#define OFFSET_BEHAVIOUR_SET_ENABLED 0x220d5f0  // UnityEngine.Behaviour.set_enabled
#define OFFSET_BEHAVIOUR_GET_ENABLED 0x220d570  // UnityEngine.Behaviour.get_enabled
#define OFFSET_SPRITE_SET_COLOR 0x209c7c0       // UnityEngine.SpriteRenderer.set_color
#define OFFSET_GET_MOUSEPOS 0x30ad000           // UnityEngine.Input.get_mousePosition
#define OFFSET_ADD_DYNAMIC_OBJECT 0x1716760     // DecaGames.RotMG.Managers.MiniMap.MiniMapManager.AddDynamicObjectToMap
#define OFFSET_REMOVE_DYNAMIC_OBJECT 0x1721ab0  // DecaGames.RotMG.Managers.MiniMap.MiniMapManager.RemoveDynamicObjectFromMap
#define OFFSET_SOCKET_SENDMESSAGE 0x650e40      // DecaGames.RotMG.Managers.Net.SocketManager.NPMFAPBMCPI (SendMessage)
#define OFFSET_CAMERAMANAGER_UPDATE 0x301a70    // DecaGames.RotMG.Managers.CameraManager.Update
#define OFFSET_UNITYTHREAD_UPDATE 0x498900      // DecaGames.RotMG.Extensions.UnityThread.Update
#define OFFSET_GET_PLAYER 0x2f2850              // JFNHHLNJJKP.JJCAKPHMLKD - Random method that runs every tick to get player
#define OFFSET_GET_ENEMY 0xe5a1d0               // COEDKELBKMI.(HOGFGOPEKAE or FFHEDOAINJH) - Random method to get enemy 
