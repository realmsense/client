#pragma once
#include "../structs.h"
#include <stdint.h>

// Created with ReClass.NET 1.2 by KN4CK3R

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

enum class FloatingText : int32_t
{
    ConditionEffect = 6,
    Damage = 1,
    Exaltation = 8,
    Fame = 2,
    LevelUp = 3,
    NewClassUnlock = 5,
    Notification = 7,
    QuestComplete = 4,
    Xp = 0
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
    wchar_t value[11]; //0x0014
}; //Size: 0x002A

class ViewHandler
{
public:
    char pad_0000[72]; //0x0000
    void* guiManager; //0x0048
    char pad_0050[48]; //0x0050
    class Entity* destroyEntity; //0x0080
    char pad_0088[32]; //0x0088
    void* viewTransform; //0x00A8
    void* contentTransform; //0x00B0
    void* shadowTransform; //0x00B8
    char pad_00C0[16]; //0x00C0
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

class SocketManager
{
public:
    char pad_0000[56]; //0x0000
    bool connecting; //0x0038
    bool connected; //0x0039
    char pad_003A[2054]; //0x003A
}; //Size: 0x0840

class CharacterInfo_GUI
{
public:
    char pad_0000[32]; //0x0000
    void* accountName_TMP; //0x0020
    void* guildInfo_Obj; //0x0028
    void* guildName_TMP; //0x0030
    void* guildIcon_Img; //0x0038
    char pad_0040[320]; //0x0040
}; //Size: 0x0180
