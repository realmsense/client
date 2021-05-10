// Created with ReClass.NET 1.2 by KN4CK3R

enum class EntityType : int32_t
{
    BasicMapObject = 0,
    Projectile = 1,
    Particle = 2,
    ParticleEffect = 3,
    MapObject = 4,
    ArenaPortal = 5,
    CaveWall = 6,
    Character = 7,
    CharacterChanger = 8,
    ClosedGiftChest = 9,
    ClosedVaultChest = 10,
    ConnectedObject = 11,
    ConnectedWall = 12,
    Container = 13,
    DailyLoginRewards = 14,
    GuildHallPortal = 15,
    GuildRegister = 16,
    GuildBoard = 17,
    GuildChronicle = 18,
    GuildMerchant = 19,
    Merchant = 20,
    MoneyChanger = 21,
    MysteryBoxGround = 22,
    NameChanger = 23,
    OneWayContainer = 24,
    Pet = 25,
    PetUpgrader = 26,
    Player = 27,
    Portal = 28,
    ReskinVendor = 29,
    QuestRewards = 30,
    SellableObject = 31,
    SpiderWeb = 32,
    Stalagmite = 33,
    Sign = 34,
    Wall = 35,
    YardUpgrader = 36,
    DoubleWall = 37,
    Empty = 38,
    WallOfFame = 39,
    VaultGiftContainer = 40,
    VaultContainer = 41,
    PremiumVaultContainer = 42,
    Blacksmith = 43
};

enum class FloatingTextType : int32_t
{
    Xp = 0,
    Damage = 1,
    Fame = 2,
    LevelUp = 3,
    QuestComplete = 4,
    NewClassUnlock = 5,
    ConditionEffect = 6,
    Notification = 7,
    Exaltation = 8
};

enum class ClassList : int32_t
{
    Any = 0,
    Rogue = 1,
    Archer = 2,
    Wizard = 3,
    Priest = 4,
    Warrior = 5,
    Knight = 6,
    Paladin = 7,
    Assassin = 8,
    Necromancer = 9,
    Huntress = 10,
    Mystic = 11,
    Trickster = 12,
    Sorcerer = 13,
    Ninja = 14,
    Samurai = 15,
    Bard = 16,
    Summoner = 17,
    Count = 18
};

class Entity
{
public:
    char pad_0000[16]; //0x0000
    class ViewHandler* view_handler; //0x0010
    class ObjectProperties* object_props; //0x0018
    char pad_0020[28]; //0x0020
    Vector2 pos; //0x003C
    char pad_0044[20]; //0x0044
    class Tile* standing_tile; //0x0058
    bool alive; //0x0060
    char pad_0061[91]; //0x0061
    EntityType entity_type; //0x00BC
    char pad_00C0[8]; //0x00C0
    class Settings* settings; //0x00C8
    char pad_00D0[136]; //0x00D0
    class String* name; //0x0158
    char pad_0160[52]; //0x0160
    int32_t skin_id; //0x0194
    char pad_0198[52]; //0x0198
    int32_t max_hp; //0x01CC
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
    int32_t max_mp; //0x0458
    float mp; //0x045C
    char pad_0460[8280]; //0x0460
}; //Size: 0x24B8

class Tile
{
public:
    char pad_0000[60]; //0x0000
    int32_t pos_x; //0x003C
    int32_t pos_y; //0x0040
    char pad_0044[20]; //0x0044
    class ObjectProperties* properties; //0x0058
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
    void* gui_manager; //0x0048
    char pad_0050[48]; //0x0050
    class Entity* destroy_entity; //0x0080
    char pad_0088[32]; //0x0088
    void* view_transform; //0x00A8
    void* content_transform; //0x00B0
    void* shadow_transform; //0x00B8
    char pad_00C0[16]; //0x00C0
    class String* prefab_name; //0x00D0
    char pad_00D8[3960]; //0x00D8
}; //Size: 0x1050

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
    int32_t count; //0x0018
    char pad_001C[4]; //0x001C
    void* items_arr; //0x0020
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
    void* account_name_tmp; //0x0020
    void* guild_info_obj; //0x0028
    void* guild_name_tmp; //0x0030
    void* guild_icon_img; //0x0038
    char pad_0040[320]; //0x0040
}; //Size: 0x0180

class MapViewHelper
{
public:
    char pad_0000[16]; //0x0000
    int32_t map_width; //0x0010
    int32_t map_height; //0x0014
    char pad_0018[36]; //0x0018
    float fog_distance; //0x003C
    float fog_opacity; //0x0040
    float loaded_tile_distance; //0x0044
    float unloaded_tile_distance; //0x0048
    int32_t pos_x; //0x004C
    int32_t pos_y; //0x0050
    char pad_0054[92]; //0x0054
    void* game_controller; //0x00B0
    char pad_00B8[144]; //0x00B8
}; //Size: 0x0148

class Settings
{
public:
    char pad_0000[212]; //0x0000
    float rotate_speed; //0x00D4
    char pad_00D8[1896]; //0x00D8
}; //Size: 0x0840

class CameraManager
{
public:
    char pad_0000[32]; //0x0000
    void* main_camera_container_transf; //0x0020
    char pad_0028[8]; //0x0028
    void* pro_camera_2d; //0x0030
    void* pro_camera_2d_pixelperf; //0x0038
    void* main_camera; //0x0040
    void* camera_perspective_editor; //0x0048
    char pad_0050[24]; //0x0050
    class DKMLMKFGPCC* N00000A56; //0x0068
    char pad_0070[80]; //0x0070
}; //Size: 0x00C0

class DKMLMKFGPCC
{
public:
    char pad_0000[56]; //0x0000
    class Entity* player; //0x0038
    char pad_0040[144]; //0x0040
    int32_t map_width; //0x00D0
    int32_t map_height; //0x00D4
    class String* map_name; //0x00D8
    char pad_00E0[64]; //0x00E0
    void* socket_manager; //0x0120
    void* game_controller; //0x0128
    char pad_0130[56]; //0x0130
    class ServerInfo* server_info; //0x0168
    char pad_0170[664]; //0x0170
}; //Size: 0x0408

class ServerInfo
{
public:
    char pad_0000[16]; //0x0000
    class String* name; //0x0010
    class String* server_address; //0x0018
    int32_t port; //0x0020
    char pad_0024[996]; //0x0024
}; //Size: 0x0408
