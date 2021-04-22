#include <cstdint>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

///////////////////
// BEGIN RECLASS //
///////////////////

enum class EntityType : int32_t
{
    ArenaPortal = 5,
    BasicMapObject = 0,
    Blacksmith = 43,
    CaveWall = 6,
    Character = 7,
    CharacterChanger = 8,
    ClosedGiftChest = 9,
    ClosedVaultChest = 10,
    ConnectedObject = 11,
    ConnectedWall = 12,
    Container = 13,
    DailyLoginRewards = 14,
    DoubleWall = 37,
    Empty = 38,
    GuildBoard = 17,
    GuildChronicle = 18,
    GuildHallPortal = 15,
    GuildMerchant = 19,
    GuildRegister = 16,
    MapObject = 4,
    Merchant = 20,
    MoneyChanger = 21,
    MysteryBoxGround = 22,
    NameChanger = 23,
    OneWayContainer = 24,
    Particle = 2,
    ParticleEffect = 3,
    Pet = 25,
    PetUpgrader = 26,
    Player = 27,
    Portal = 28,
    PremiumVaultContainer = 42,
    Projectile = 1,
    QuestRewards = 30,
    ReskinVendor = 29,
    SellableObject = 31,
    Sign = 34,
    SpiderWeb = 32,
    Stalagmite = 33,
    VaultContainer = 41,
    VaultGiftContainer = 40,
    Wall = 35,
    WallOfFame = 39,
    YardUpgrader = 36
};

class Entity
{
public:
    char pad_0000[16]; //0x0000
    class ViewHandler* viewHandler; //0x0010
    class ObjectProperties* objectProps; //0x0018
    char pad_0020[28]; //0x0020
    Vector2 pos; //0x003C
    char pad_0044[20]; //0x0044
    class Tile* standingTile; //0x0058
    bool alive; //0x0060
    char pad_0061[91]; //0x0061
    EntityType entityType; //0x00BC
    char pad_00C0[152]; //0x00C0
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

class Tile
{
public:
    char pad_0000[60]; //0x0000
    int32_t posX; //0x003C
    int32_t posY; //0x0040
    char pad_0044[20]; //0x0044
    class ObjectProperties* OBGKICHNIDN; //0x0058
    char pad_0060[1000]; //0x0060
}; //Size: 0x0448

class ObjectProperties
{
public:
    char pad_0000[56]; //0x0000
    class String* name; //0x0038
}; //Size: 0x0040

class String
{
public:
    char pad_0000[16]; //0x0000
    int32_t length; //0x0010
    wchar_t value[99]; //0x0014
}; //Size: 0x00DA

class ViewHandler
{
public:
    char pad_0000[128]; //0x0000
    class Entity* destroyEntity; //0x0080
    char pad_0088[32]; //0x0088
    void* viewTransform; //0x00A8
    void* contentTransform; //0x00B0
    char pad_00B8[24]; //0x00B8
    class String* prefabName; //0x00D0
    char pad_00D8[3960]; //0x00D8
}; //Size: 0x1050

class NBJLMDOACBC
{
public:
    char pad_0000[32]; //0x0000
    class List* playerList; //0x0020
    char pad_0028[280]; //0x0028
}; //Size: 0x0140

class List
{
public:
    char pad_0000[16]; //0x0000
    class ListItems* items; //0x0010
    int32_t size; //0x0018
    int32_t version; //0x001C
    char pad_0020[8]; //0x0020
}; //Size: 0x0028

class ListItems
{
public:
    char pad_0000[24]; //0x0000
    int32_t Count; //0x0018
    char pad_001C[4]; //0x001C
    void* itemsArr; //0x0020
    char pad_0028[32]; //0x0028
}; //Size: 0x0048

/////////////////
// END RECLASS //
/////////////////

// Global Functions
typedef uintptr_t(__cdecl* _GetMainCamera)(void);
typedef void* (__cdecl* _Camera_set_orthographicSize)(uintptr_t UnityEngine_Camera, float amount);
typedef void* (__cdecl* _Behaviour_set_enabled)(uintptr_t __this, bool value);
typedef bool (__cdecl* _Behaviour_get_enabled)(uintptr_t __this);
typedef uintptr_t (__cdecl* _Component_GetGameObject)(uintptr_t __this);
typedef uintptr_t (__cdecl* _GameObject_Find)(String* name);
typedef uintptr_t (__cdecl* _GameObject_GetTransform)(uintptr_t gameObject);
typedef bool (__cdecl* _GameObject_GetActive)(uintptr_t gameObject);
typedef void (__cdecl* _GameObject_SetActive)(uintptr_t gameObject, bool value);
typedef uintptr_t (__cdecl* _Transform_GetChild)(uintptr_t transform, int index);
typedef uintptr_t (__cdecl* _Transform_Find)(uintptr_t transform, String* name);
typedef int (__cdecl* _Transform_get_childCount)(uintptr_t transform);
typedef Vector3(__cdecl* _Transform_get_position)(uintptr_t transform);
typedef void(__cdecl* _Transform_set_position)(uintptr_t transform, Vector3 scale);
typedef Vector3 (__cdecl* _Transform_get_localScale)(uintptr_t transform);
typedef void (__cdecl* _Transform_set_localScale)(uintptr_t transform, Vector3 scale);
typedef Vector3 (__cdecl* _WorldToScreen)(uintptr_t camera, Vector3 position);
typedef Vector3 (__cdecl* _ScreenToWorld)(uintptr_t camera, Vector3 position);
typedef void(__cdecl* _SetVsync)(int value);
typedef void(__cdecl* _SetFpsTarget)(int value);

// Global Structs
enum AutoAimTarget
{
    ClosestMouse,
    ClosestPos,
    HighestDef,
    HighestMaxHP
};

// Offsets
#define OFFSET_GET_MAINCAMERA                   0x220fc10   // UnityEngine.Camera.get_main
#define OFFSET_SET_ORTHOGRAPHICSIZE             0x2210430   // UnityEngine.Camera.set_orthographicSize
#define OFFSET_WORLD_TO_SCREEN                  0x220f640   // UnityEngine.Camera.WorldToScreenPoint
#define OFFSET_SCREEN_TO_WORLD                  0x220f230   // UnityEngine.Camera.ScreenToWorldPoint
#define OFFSET_BEHAVIOUR_GET_ENABLED            0x220d570   // UnityEngine.Behaviour.get_enabled
#define OFFSET_BEHAVIOUR_SET_ENABLED            0x220d5f0   // UnityEngine.Behaviour.set_enabled
#define OFFSET_COMPONENT_GET_GAMEOBJECT         0x2211ef0   // UnityEngine.Component.get_gameObject
#define OFFSET_GAMEOBJECT_FIND                  0x22160c0   // UnityEngine.GameObject.Find
#define OFFSET_GAMEOBJECT_GET_TRANSFORM         0x2216870   // UnityEngine.GameObject.get_transform
#define OFFSET_GAMEOBJECT_GET_ACTIVE            0x2216750   // UnityEngine.GameObject.get_activeSelf
#define OFFSET_GAMEOBJECT_SET_ACTIVE            0x2216450   // UnityEngine.GameObject.SetActive
#define OFFSET_TRANSFORM_GET_CHILD              0x20a3de0   // UnityEngine.Transform.GetChild
#define OFFSET_TRANSFORM_FIND                   0x20a3d40   // UnityEngine.Transform.Find
#define OFFSET_TRANSFORM_GET_CHILD_COUNT        0x20a4bb0   // UnityEngine.Transform.get_childCount
#define OFFSET_TRANSFORM_GET_POSITION           0x20a51a0   // UnityEngine.Transform.get_position
#define OFFSET_TRANSFORM_SET_POSITION           0x20a59f0   // UnityEngine.Transform.set_position
#define OFFSET_TRANSFORM_GET_LOCAL_SCALE        0x20a4fb0   // UnityEngine.Transform.get_localScale
#define OFFSET_TRANSFORM_SET_LOCAL_SCALE        0x20a58a0   // UnityEngine.Transform.set_localScale
#define OFFSET_SPRITE_SET_COLOR                 0x209c7c0   // UnityEngine.SpriteRenderer.set_color
#define OFFSET_GET_MOUSEPOS                     0x30ad000   // UnityEngine.Input.get_mousePosition
#define OFFSET_ADD_DYNAMIC_OBJECT               0x1716760   // DecaGames.RotMG.Managers.MiniMap.MiniMapManager.AddDynamicObjectToMap
#define OFFSET_REMOVE_DYNAMIC_OBJECT            0x1721ab0   // DecaGames.RotMG.Managers.MiniMap.MiniMapManager.RemoveDynamicObjectFromMap
#define OFFSET_SOCKET_SENDMESSAGE               0x650e40    // DecaGames.RotMG.Managers.Net.SocketManager.NPMFAPBMCPI (SendMessage)
#define OFFSET_CAMERAMANAGER_UPDATE             0x301a70    // DecaGames.RotMG.Managers.CameraManager.Update
#define OFFSET_UNITYTHREAD_UPDATE               0x498900    // DecaGames.RotMG.Extensions.UnityThread.Update
#define OFFSET_GET_PLAYER                       0x2f2850    // JFNHHLNJJKP.JJCAKPHMLKD - Random method that runs every tick to get player
#define OFFSET_GET_ENEMY                        0xe5a1d0    // COEDKELBKMI.(HOGFGOPEKAE or FFHEDOAINJH) - Random method to get enemy 
#define OFFSET_GET_PLAYER_LIST                  0xa3b030    // NBJLMDOACBC.CDKKNNAJIBG - random method that runs every tick, the class contains `List<JFNHHLNJJKP>` of players.
#define OFFSET_GET_PET                          0x916bc0    // DAFEAHGLBGL.AOOJCNNGNGI - random method that runs every tick to get pets
#define OFFSET_SET_VSYNC                        0x232fdb0   // UnityEngine.QualitySettings.set_vSyncCount
#define OFFSET_SET_FPS_TARGET                   0x220b6e0   // UnityEngine.Application.set_targetFrameRate
