#include "il2cpp-internal-types.h"

namespace app {

struct __declspec(align(8)) String__Fields {
    int32_t m_stringLength;
    uint16_t m_firstChar;
};

struct String {
    struct String__Class *klass;
    MonitorData *monitor;
    struct String__Fields fields;
};

struct RuntimeTypeHandle {
    void *value;
};

struct __declspec(align(8)) Type__Fields {
    struct RuntimeTypeHandle _impl;
};

struct Type {
    struct Type__Class *klass;
    MonitorData *monitor;
    struct Type__Fields fields;
};

enum class Allocator__Enum : int32_t {
    Invalid = 0x00000000,
    None = 0x00000001,
    Temp = 0x00000002,
    TempJob = 0x00000003,
    Persistent = 0x00000004,
    AudioKernel = 0x00000005,
};

struct __declspec(align(8)) Object__Fields {
    void *m_CachedPtr;
};

struct Object {
    struct Object__Class *klass;
    MonitorData *monitor;
    struct Object__Fields fields;
};

struct Component__Fields {
    struct Object__Fields _;
};

struct Component {
    struct Component__Class *klass;
    MonitorData *monitor;
    struct Component__Fields fields;
};

struct Behaviour__Fields {
    struct Component__Fields _;
};

struct Behaviour {
    struct Behaviour__Class *klass;
    MonitorData *monitor;
    struct Behaviour__Fields fields;
};

struct Camera__Fields {
    struct Behaviour__Fields _;
};

struct Camera {
    struct Camera__Class *klass;
    MonitorData *monitor;
    struct Camera__Fields fields;
};

struct Color {
    float r;
    float g;
    float b;
    float a;
};

struct Rect {
    float m_XMin;
    float m_YMin;
    float m_Width;
    float m_Height;
};

struct Matrix4x4 {
    float m00;
    float m10;
    float m20;
    float m30;
    float m01;
    float m11;
    float m21;
    float m31;
    float m02;
    float m12;
    float m22;
    float m32;
    float m03;
    float m13;
    float m23;
    float m33;
};

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector2 {
    float x;
    float y;
};

struct Transform__Fields {
    struct Component__Fields _;
};

struct Transform {
    struct Transform__Class *klass;
    MonitorData *monitor;
    struct Transform__Fields fields;
};

struct MonoBehaviour__Fields {
    struct Behaviour__Fields _;
};

struct MonoBehaviour {
    struct MonoBehaviour__Class *klass;
    MonitorData *monitor;
    struct MonoBehaviour__Fields fields;
};

struct float3 {
    float x;
    float y;
    float z;
};

struct EntityManager {
    struct EntityDataAccess *m_EntityDataAccess;
};

enum class MapObjectType : int32_t {
    BasicMapObject = 0x00000000,
    Projectile = 0x00000001,
    Particle = 0x00000002,
    ParticleEffect = 0x00000003,
    MapObject = 0x00000004,
    ArenaPortal = 0x00000005,
    CaveWall = 0x00000006,
    Character = 0x00000007,
    CharacterChanger = 0x00000008,
    ClosedGiftChest = 0x00000009,
    ClosedVaultChest = 0x0000000a,
    ConnectedObject = 0x0000000b,
    ConnectedWall = 0x0000000c,
    Container = 0x0000000d,
    DailyLoginRewards = 0x0000000e,
    GuildHallPortal = 0x0000000f,
    GuildRegister = 0x00000010,
    GuildBoard = 0x00000011,
    GuildChronicle = 0x00000012,
    GuildMerchant = 0x00000013,
    Merchant = 0x00000014,
    MoneyChanger = 0x00000015,
    MysteryBoxGround = 0x00000016,
    NameChanger = 0x00000017,
    OneWayContainer = 0x00000018,
    Pet = 0x00000019,
    PetUpgrader = 0x0000001a,
    Player = 0x0000001b,
    Portal = 0x0000001c,
    ReskinVendor = 0x0000001d,
    QuestRewards = 0x0000001e,
    SellableObject = 0x0000001f,
    SpiderWeb = 0x00000020,
    Stalagmite = 0x00000021,
    Sign = 0x00000022,
    Wall = 0x00000023,
    YardUpgrader = 0x00000024,
    DoubleWall = 0x00000025,
    Empty = 0x00000026,
    WallOfFame = 0x00000027,
    VaultGiftContainer = 0x00000028,
    VaultContainer = 0x00000029,
    PremiumVaultContainer = 0x0000002a,
    Blacksmith = 0x0000002b,
    Summon = 0x0000002c,
};

struct __declspec(align(8)) BasicObject__Fields {
    struct ViewHandler *NJGEIJDFFND;
    struct ObjectProperties *BEHCPLKDAFD;
    struct CGPOGAAKLFL *KFGNMNGIAKM;
    struct CGPOGAAKLFL *DLNMEAOOHKA;
    int32_t OGBGLIIENMF;
    int32_t LADFHJEFKEC;
    bool BEBPECHFJON;
    bool GLLGFJJGBGB;
    bool IAOPFAHDOLJ;
    float EOOJAMLJAOM;
    float JDEKCEFBJFP;
    float POOCHBEKLMN;
    bool ADIDHKFFJBG;
    int32_t GKKEDMEEOGB;
    float CMPGLPIOJEB;
    struct OHMNEJGNIPN *EJHKGKHGEBM;
    bool is_active;
    int32_t MAKNEMCCDAB;
    struct float3 AEEEJDNCDKI;
    struct float3 OGJBKGCIKDD;
    bool KFHEILLOJGN;
    struct float3 BNFGLAPPMNF;
    struct MapViewService *OHLHEKBJMOO;
    bool MKIBGHFFBAA;
    float ILDPPGOMHEE;
    struct HMFBHFKGKEP *KKHAPGIAKBN;
    bool OGLPABGHHCI;
    struct MiniMapObject *IPPIHBDHPFC;
    bool EKKENGPCCEM;
    #if defined(_CPLUSPLUS_)
    MapObjectType CDNHIOHCAIB;
    #else
    int32_t CDNHIOHCAIB;
    #endif
    int32_t CNKEDAHLBPC;
    bool FNIFMCLMAGG;
    bool JOGMLOIAHLH;
    struct Settings *DKCDBOLECHM;
    struct MiniMapManager *MPDIMLPFNBE;
    bool HAKNGHGPLEG;
    bool JKEOLFDJLDG;
    struct float3 IBAGIHEDPHP;
    bool NHJINJIKENB;
    int32_t AGMABKNHEIA;
    uint64_t KAOINAPOCHA;
    struct SoundManager *MOCLPINOOBK;
    struct FKNJGNBCGON *CCCPOAHGGKK;
    bool KBPIHBDMKCB;
    bool FGCBPKGAOMG;
    float KAFMCNEJCFN;
};

struct BasicObject {
    struct BasicObject__Class *klass;
    MonitorData *monitor;
    struct BasicObject__Fields fields;
};

enum class MapItem : int32_t {
    Interaction = 0x00000000,
    LootBag = 0x00000001,
    Death = 0x00000002,
    YardUpgrader = 0x00000003,
    Wardrobe = 0x00000004,
    Pet = 0x00000005,
};

enum class EFBAFDICAFG : int32_t {
    Right = 0x00000000,
    Left = 0x00000001,
    Down = 0x00000002,
    Up = 0x00000003,
    None = 0x00000004,
    First = 0x00000005,
};

enum class BJHJLINJFAI : int32_t {
    Stand = 0x00000000,
    Walk = 0x00000001,
    Attack = 0x00000002,
    NumAction = 0x00000003,
};

struct MapObject__Fields {
    struct BasicObject__Fields _;
    struct MapObject_OHFEFBLKENE *GCADFJIJILJ;
    struct MapObject_DONNNAHFHFL *ONFIGLJIIKE;
    struct MapObject_DONNNAHFHFL *IBLNHFPBLCJ;
    struct MapObject_DONNNAHFHFL *HHAJNDJDEHF;
    struct MapObject_DONNNAHFHFL *ECDIDHKLCOB;
    struct MapObject_DONNNAHFHFL *JCOMFCKCNIM;
    struct MapObject_CKABBMAGJCF *KOHAEPMPCPE;
    struct JOBKMIIMCJN *GOHBCMBOHOC;
    struct String *HHAAMEHHGGP;
    float AMGIPKNPNDP;
    float LODCFMOPDCN;
    int32_t PFOKGMJMDCI;
    bool NGMGBCDHOFF;
    struct List_1_KLKDLLPEACH_ *NMJGKDNIMLO;
    struct LOKHOLAAFEC *FIHDCPPCCFP;
    struct IBBIAKAFDKN *ABJEJBDMDLE;
    uint32_t KNNDAHMCGHH;
    int32_t EGBMEMDIHDA;
    int32_t defense;
    int32_t skin_id;
    int32_t LLAPDDNMNEA;
    struct ObjectProperties *COEAPMHIJPJ;
    struct String *GMMFCEFMDAG;
    int32_t KHCOJOOFEMO;
    struct LADIMDKOPJO *CCNPAIFMHAD;
    bool FBLOKBOPOOC;
    int32_t HNBJJFDLAKN;
    int32_t MMFKLFOFMEK;
    int32_t HFLFELILPIK;
    int32_t MGOMLEAAGEM;
    bool HCPADPBCLAE;
    int32_t ENPPCKKNLKM;
    int32_t max_hp;
    int32_t DPPBIPLPHJB;
    bool OCOMOLCKIMN;
    bool IACPCCIMDAD;
    bool GEKMCEOBGEO;
    bool FGPNDJOEMMP;
    bool GOIPHNDELBA;
    bool ADIGIBDADHI;
    struct CGPOGAAKLFL *CHOKCFLIIFI;
    struct AnimatedTexture *IEILAJJCMGC;
    struct CGPOGAAKLFL *JFJEEDCCPIJ;
    bool BGJKEDLJKOC;
    bool ABLDLEOGABI;
    double HDHLOKPBNLO;
    struct Int32__Array *NBKFIKODCFJ;
    #if defined(_CPLUSPLUS_)
    MapItem ECPELIFEJPI;
    #else
    int32_t ECPELIFEJPI;
    #endif
    int32_t ONDEDPJMPAH;
    int32_t PMMGHENKENN;
    struct Vector2 IJBJFDLLAKB;
    struct Vector2 NBPNOECJCKN;
    struct Vector2 DBLDNDPCGPB;
    int32_t EKOLJKLMBGJ;
    int32_t CKLDGPCPDJJ;
    #if defined(_CPLUSPLUS_)
    EFBAFDICAFG MBLPMJAIBBJ;
    #else
    int32_t MBLPMJAIBBJ;
    #endif
    bool BDNEAINFICG;
    #if defined(_CPLUSPLUS_)
    BJHJLINJFAI EHLAPMNLCFD;
    #else
    int32_t EHLAPMNLCFD;
    #endif
    struct List_1_System_Int32_ *GGCLLLEHNJA;
    struct List_1_System_Int32_ *IMLLNEFIMGC;
    struct List_1_System_Int32_ *PECDCJPMBNE;
    struct Dictionary_2_System_Int32_System_Int32_ *IDIKNDDDMGD;
    struct MOECBPFNCOJ *JHFLGACOKMI;
    bool IHFKFGEHHFB;
    struct ObjectProperties *IOKJINGPABB;
    struct KLKDLLPEACH *CKGLELJOACI;
    struct IPLLFANOFGD *CIJKGNOLCAO;
    struct SpriteMask *JNIJOIAHCEC;
    struct SortingGroup *LMEBLKJIFCK;
    struct SpriteRenderer *HGLIEJOCNMI;
    bool JBINFIHJKBA;
    int32_t EAMFMEIBKJH;
    bool DHEPPKMKIGP;
    float OPCKGJDNLKB;
    float JBFMFBGJIOG;
    bool MEMFMGKBLBG;
    int32_t EBNCNAALEII;
    bool HGDGBILHLMG;
};

struct MapObject {
    struct MapObject__Class *klass;
    MonitorData *monitor;
    struct MapObject__Fields fields;
};

struct Character__Fields {
    struct MapObject__Fields _;
    struct String *IAEKKFGGEMM;
    struct String *ANDGJEEIBOE;
    bool CBLBBOMJJAJ;
};

struct Character {
    struct Character__Class *klass;
    MonitorData *monitor;
    struct Character__Fields fields;
};

struct Nullable_1_UnityEngine_Vector2_ {
    struct Vector2 value;
    bool has_value;
};

struct Player__Fields {
    struct Character__Fields _;
    struct Player_MLMCBBKGONG *FCIEBGPMHNK;
    struct Player_MLMCBBKGONG *KPPKMGPOFNP;
    struct Player_MLMCBBKGONG *LHPMIHBOOPM;
    struct Player_MLMCBBKGONG *FCIHLFOKMFN;
    struct Player_MLMCBBKGONG *NBDOMFJHELN;
    struct Player_MLMCBBKGONG *NANBJLEJJPI;
    struct Player_MLMCBBKGONG *AADHLIGDDPL;
    struct Player_MLMCBBKGONG *IAOPCPHBDFC;
    struct Player_MLMCBBKGONG *KJHAPJGCDNK;
    struct Player_MLMCBBKGONG *GHFPMFOKBLK;
    struct Player_MLMCBBKGONG *GJPKDPMOEPD;
    struct Player_MLMCBBKGONG *JLDIILNLHIK;
    struct Player_MLMCBBKGONG *PJEDNBPDHDE;
    struct Player_MLMCBBKGONG *KOEHHFOIHLD;
    struct Player_MLMCBBKGONG *FEMLKOBJCKP;
    struct Player_MLMCBBKGONG *AFANALBKNKG;
    struct Player_MLMCBBKGONG *PLJMHFJLMFA;
    struct Player_GEBIFPOPIIN *HEHKHJGBCIJ;
    struct Dictionary_2_System_Int32_Sources_DecaGames_RotMG_Data_QuickSlotData_ *ILGEFDCGFGG;
    int32_t EFKNDAAKGAG;
    int32_t DOGJDJIKIAI;
    int32_t EENAJPFHADM;
    int32_t GPFGJLACHDC;
    int32_t FCGBOJHFIOG;
    bool NKIELALMAME;
    float MEBMEKDHIGB;
    bool EOEFBDJDGBE;
    int32_t PBOEOIGCJDP;
    int32_t GNJMIDCOGGG;
    struct String *FLCOMAGIJOI;
    bool NCKGHPFNNFK;
    int32_t HJBCGDPGDKC;
    float POIGCBNJFGI;
    float IEMNCCPAMML;
    int32_t OKHDFNLCLDB;
    int32_t GHIJMFHMMBN;
    double ODNDBGHBKJH;
    bool IABDPDAGMAO;
    int32_t OMLDBKLEENE;
    int32_t GABNFGIEECE;
    int32_t ICGEAABOPBP;
    struct String *EHOJFLPHFKI;
    bool DPDMBFLALBE;
    bool LDJIHBKOJBP;
    float KDOAGDPBDFD;
    float IBBBNGGNDAO;
    int32_t CPJMNEEDNEM;
    int32_t LOLGDFIBIBI;
    int32_t JCAHMOFBMKJ;
    int32_t EDNEPOLKEMP;
    int32_t PGFCDDBDBLO;
    int32_t FDNHLFIOPFH;
    int32_t IHMGHGBFAGK;
    int32_t KKCCACOJFIA;
    int32_t CLACCNODHPK;
    int32_t GGMMPNEPOLF;
    int32_t JLODOCOIOOG;
    int32_t JFPIFIEDIKO;
    int32_t FIMKPEMHJNN;
    int32_t ININHHOCDPG;
    int32_t IJMJCGGNAFO;
    int32_t JDEKJDBAOPJ;
    int32_t CMACAOMAAOA;
    int32_t DHFIHOMGJEM;
    float DKCLHEIEMJB;
    bool IMFCINFDMKK;
    bool MFAHJBIFENI;
    bool ICPMFIFFACJ;
    int32_t LAFABEDFNCK;
    int32_t MNBLAJKMPJG;
    int32_t AOHKAGOOECE;
    int32_t JIFIGGMMKPE;
    double KLDJNFIGKMG;
    int32_t EKGJIAODBEO;
    int32_t JGKCMPDMCKC;
    int32_t OPAKKHFJCPG;
    float EBOMCCHKMDG;
    int32_t EOEJCCAPAAM;
    bool GFLINEPPCGF;
    bool HJEDBABNBHB;
    int32_t JJGHMAPBNFN;
    float BHENNKFJGFD;
    bool BKPGKDMDMHI;
    int32_t ACKDOMMPGMA;
    int32_t FKNOJDFGHPI;
    bool BGMEMOKNOLC;
    float MGMIFMDFEND;
    float CLJMDPCPEPM;
    float JJEPOPEEJND;
    float FEODDMEDHLL;
    float HAPJNKGHNMB;
    float MGALECNLMJE;
    int32_t PGFIALLNCNI;
    int32_t CGIDBGGCLCP;
    float OPCCNAJKBGL;
    float ONMEPMHBHJM;
    float INENFAFGICA;
    float IGCIKJFPBOF;
    struct Pet *GPMIPLJHOKI;
    int32_t _DLLILOLCDCF_k__BackingField;
    struct Vector2 EEJNGAKNKPN;
    float KJFCCGPEJOL;
    struct Nullable_1_UnityEngine_Vector2_ PMGBHKADICL;
    float KFDOAINDCOO;
    uint32_t BFFFDDGGMLO;
    struct Vector2 KBCPDPODBNB;
    struct String *PAFDOCOLCKK;
    struct String *CEFANDOPCHC;
    struct HNCCPCHKKHG *EOBDBMDFFGH;
    struct MICPFEDBHDI *DNECBJNINEO;
    struct FLNIEEPOHLH *HIOPMJOJABO;
    int32_t GHBLFKNKCNN;
    struct NotificationManager *ENHOLOIBILG;
    struct NBNNMHCOFNH *MNFKKEFLNPC;
    bool FNACOFALAOP;
    struct LADIMDKOPJO *MOHIIEJKIAO;
    struct SoundSettings *EEJGKMKGENO;
    float BLCDBJICMOD;
    struct DKLDOPCAIHJ *NJLANKIJPDK;
    struct List_1_HDLHMJGAGEI_ *AFBNANPFPCD;
    struct float3 LPCIMNBBHKL;
    bool NCFHHAPPBEM;
    struct Action *JMNILMDEAGN;
    struct Action *PGEIFEKLKJF;
};

struct Player {
    struct Player__Class *klass;
    MonitorData *monitor;
    struct Player__Fields fields;
};

struct ViewHandler__Fields {
    struct MonoBehaviour__Fields _;
    struct GameObject *value;
    struct SpriteRenderer *content;
    struct Renderer__Array *renderers;
    struct Material *rendererMaterial;
    struct Color rendererMaterialColor;
    struct MapObjectUIManager *GUIManager;
    struct JOBKMIIMCJN *iGUIManager;
    struct SpriteShader *spriteShader;
    struct GameObject *shadow;
    struct SpriteRenderer *shadowRenderer;
    struct ShadowShader *shadowShader;
    struct TextMeshPro *label;
    struct PHFEMIPMDEK *destroyEntity;
    bool hasShadow;
    bool OGAOHDGAFJH;
    bool isParticle;
    bool isBitmapParticle;
    bool isStaticSizeParticle;
    struct SpriteMask *spriteMask;
    struct SortingGroup *sortingGroup;
    bool hasContent;
    struct Transform *viewTransform;
    struct Transform *contentTransform;
    struct Transform *shadowTransform;
    struct GameObject *contentGameObject;
    bool hasRenderers;
    bool isDrawOnGround;
    bool hideOnStart;
    struct String *prefabName;
    bool CBHDGGBKGDF;
    float JEANKOGLJDB;
    bool isVisible;
    struct String *objectName;
    bool used;
    struct Transform *lootBagContainer;
};

struct ViewHandler {
    struct ViewHandler__Class *klass;
    MonitorData *monitor;
    struct ViewHandler__Fields fields;
};

struct MapObjectUIManager__Fields {
    struct MonoBehaviour__Fields _;
    struct GUIInfoSection *infoSection;
    struct Transform *floatingTextsContainer;
    struct CharacterConditionUIManager *conditionUiManager;
    struct List_1_DecaGames_RotMG_UI_Controllers_FloatingTextController_ *floatingTextPool;
    struct SpeechBalloon *speechBalloon;
    struct MapObject *CKEINDDMPKI;
    bool ECINHEJBKBL;
    bool BOMCJCJPKEN;
    float MOFILCGLDHH;
    struct Transform *KALELMALCCC;
    bool OAFEFMPBEOL;
    int32_t BDLCHNMAKMA;
    bool JMPKHFGDNJG;
    struct FloatingTextController *PFEFEEGLGFO;
    bool GDFLFIOMPNP;
    int32_t KAPPAFBCLJK;
    bool CBHDGGBKGDF;
};

struct MapObjectUIManager {
    struct MapObjectUIManager__Class *klass;
    MonitorData *monitor;
    struct MapObjectUIManager__Fields fields;
};

struct __declspec(align(8)) Settings__Fields {
    struct Settings_ABEAHFANHDO *EJMEBHGBJCL;
    struct Settings_ABEAHFANHDO *PPIABFJPNLB;
    struct Settings_ABEAHFANHDO *GEDNBBJBOJH;
    struct Settings_ABEAHFANHDO *AIHFFEAPLEP;
    struct Settings_ABEAHFANHDO *JDOMBMEFIMA;
    struct Settings_ABEAHFANHDO *EKIBLFIHLNA;
    struct Settings_ABEAHFANHDO *LMNBIIKCIBC;
    struct Settings_ABEAHFANHDO *GJLIPDKMNKL;
    struct Settings_ABEAHFANHDO *HOLHJKGBBBG;
    bool MFKGHCMCOAO;
    bool DFNNJCDKMPP;
    struct String *GMMFCEFMDAG;
    struct String *NCADAPAJGCH;
    bool IABDPDAGMAO;
    bool AAFACMHNKOA;
    bool GHABKCFFJNE;
    bool OAJDBALANDA;
    bool GPMJPIBAPLB;
    int32_t IIIEOIBDJCO;
    int32_t KDAJCCBJIFP;
    double KLDJNFIGKMG;
    int32_t EAIOBDNIODE;
    bool LDFJJGAHLND;
    bool GNNEPFDIDNJ;
    bool CKPECENJEPE;
    bool FGPPMAMHCPN;
    bool NPKDDILEDCD;
    bool ALFKAAAEEGC;
    bool MAOPEEBOHGI;
    bool KLFLNIPLNIJ;
    int32_t NDOPPGPKOKP;
    int32_t AOEMJOHJCIC;
    int32_t IBHCCBKKJHA;
    bool HDPNFFDLEJF;
    bool NIBDDENCPGK;
    double ODNDBGHBKJH;
    int32_t KNAHPICGENG;
    int32_t HBJHMDHJIBJ;
    bool BGOABDKDJJO;
    bool MJBCFEMAOMG;
    bool OLBFCLMENMC;
    bool EGBIDAANLNB;
    bool FDKAHNJODHG;
    bool MOGJAOLLHBO;
    bool NKENHCNFHCN;
    bool JFPGLFJDLML;
    bool PCEIIGFIFCE;
    bool OAKPEEAGEEM;
    bool JODODJHDPNC;
    bool MMGCLKNNLBN;
    bool CAJHFPEDINI;
    int32_t FOIDIEKGGMO;
    int32_t ELMKAAFGKFO;
    bool MMGDJDGJOGN;
    bool AFFNEDANILP;
    bool AAJPJBNDHDB;
    bool OHHMPHLPJHP;
    float rotate_speed;
    bool PIFIHFFFKHD;
    bool BPEOBLKFKIH;
    bool NDIJJMMMALJ;
    bool BLOCEKENAHL;
    bool KMLPHNPNLBM;
    bool INNFCIIFNPH;
    bool NNONKGGJJAA;
    bool JIOOCMJGEFF;
    int32_t JFPJIIKHHJI;
    int32_t LDGNLMGNHCM;
    bool CFDLPMPOIPI;
    bool HIHJLHDFICA;
    bool FIGJIDMIILA;
    bool GJLAPELHIJK;
    bool BDECNBLGEPJ;
    bool CCNOACAHBGP;
    bool PJGBHBBAOJN;
    bool DPEJPKFIAMN;
    bool IOMNIJLINAJ;
    bool LHGOHECAFKO;
    bool NAEPDAHPBLO;
    bool OICBJGINGNM;
    float NCEGLLAMBKF;
    struct FAKKOGNGKAB *POLGNNDOBKL;
    int32_t GOMLFOOMJKC;
    int32_t JKMPMNOBDBL;
    int32_t EAEFNGJLNPM;
    int32_t IGLKBGPGJIA;
    struct Dictionary_2_System_Int32_System_Int32_ *FDGEJMMBPDG;
    struct HCLAMODFNBI *LPKIADKODHC;
    struct List_1_AMLJNMDMPNG_ *BDBPDGJIFKK;
    struct Dictionary_2_System_Int32_AMLJNMDMPNG_ *JDMGMPKFJEE;
    struct Dictionary_2_System_String_System_Int32_ *CNDGPOIDADC;
    struct List_1_FDHMOPKKNGI_ *DBOJDIPICKN;
    struct AMLJNMDMPNG *JEMEEPKJCCA;
    struct CKMLLKPOBKP *IPNPGOLNLAC;
    bool GNMINIBGBEG;
    struct List_1_System_String_ *NFKNFKDFEID;
    struct String *_NMGDJEDLAGK_k__BackingField;
    struct String *_CLAPFHFJMJK_k__BackingField;
    struct String *_FFIJPPMKHJC_k__BackingField;
    struct String *_FPIKBBOPAGD_k__BackingField;
    struct String *_MMGODEBMBML_k__BackingField;
    struct String *_LBDCDELDPAE_k__BackingField;
};

struct Settings {
    struct Settings__Class *klass;
    MonitorData *monitor;
    struct Settings__Fields fields;
};

struct __declspec(align(8)) ChatSlot__Fields {
    struct String *name;
    struct String *original_message;
    int32_t LIEBMCAGCIF;
    int32_t JJGHMAPBNFN;
    struct String *KJGCHNILDOK;
    bool IEKNBEECMJC;
    bool KMOHFBJAPMP;
    bool NDGGAABFLKK;
    int32_t IINBPOKGDOO;
    struct Object *DMDLMNDFNHG;
    struct String *formatted_message;
    bool AMMDBPEJJGP;
};

struct ChatSlot {
    struct ChatSlot__Class *klass;
    MonitorData *monitor;
    struct ChatSlot__Fields fields;
};

struct __declspec(align(8)) TextureProperties__Fields {
    struct Texture_1 *TextureAttribute;
    struct RandomTexture *RandomTextureAttribute;
    struct KLKDLLPEACH *_textureData;
};

struct TextureProperties {
    struct TextureProperties__Class *klass;
    MonitorData *monitor;
    struct TextureProperties__Fields fields;
};

struct BaseProperties__Fields {
    struct TextureProperties__Fields _;
    struct Top *TopTextureElement;
    struct EffectProperties *Effect;
};

struct BaseProperties {
    struct BaseProperties__Class *klass;
    MonitorData *monitor;
    struct BaseProperties__Fields fields;
};

struct ObjectProperties__Fields {
    struct BaseProperties__Fields _;
    struct String *id;
    struct TopAnimation__Array *TopAnimation;
    struct String *DisplayId;
    struct String *BagType;
    struct String *TypeAttribute;
    struct String *SetTypeAttribute;
    struct String *SetNameAttribute;
    struct String *Model;
    struct String *NoTexture;
    struct String *OccupySquareElement;
    struct String *NoCoverElement;
    struct String *ShadowSizeElement;
    struct String *PlayerElement;
    struct String *EnemyElement;
    struct String *AlwaysPositiveHealth;
    struct String *DrawOnGroundElement;
    struct String *DrawUnderElement;
    struct String *FullOccupyElement;
    struct String *EnemyOccupySquareElement;
    struct String *StaticElement;
    struct String *NoMiniMapElement;
    struct String *HealthBarElement;
    struct String *ProtectFromGroundDamageElement;
    struct String *ProtectFromSinkElement;
    struct String *FlyingElement;
    struct String *ShowNameElement;
    struct String *DontFaceAttacksElement;
    struct String *DontFaceMovementElement;
    struct String *ZElement;
    struct String *ColorElement;
    struct String *SizeElement;
    struct String *MinSizeElement;
    struct String *MaxSizeElement;
    struct String *SizeStepElement;
    struct String *LargeSkillPotionElement;
    struct String *SmallSkillPotionElement;
    struct String *BloodProbElement;
    struct String *BloodColorElement;
    struct String *ShadowColorElement;
    struct String *ClassElement;
    struct String *RotationElement;
    struct String *AngleCorrectionElement;
    struct String *SlotTypesElement;
    struct String *NexusPortalElement;
    struct String *LockedPortalElement;
    struct ProjectileProperties__Array *Projectiles;
    struct ShortLineTexture *ShortLineTextureElement;
    struct LTexture *LTextureElement;
    struct LineTexture *LineTextureElement;
    struct String *BaseIndentElement;
    struct String *TopIndentElement;
    struct String *HeightElement;
    struct String *NoWallTextureRepeatElement;
    struct String *NoTopTextureRepeatElement;
    struct String *NumProjectilesElement;
    struct String *ArcGapElement;
    struct String *SlotTypeElement;
    struct String *LotElement;
    struct String *CanPutSoulboundObjectsElement;
    struct String *SoulboundElement;
    struct String *DropTradableElement;
    struct String *ConsumableElement;
    struct QuickslotAllowed *QuickslotAllowedElement;
    struct QuickslotCooldown *QuickslotCooldownElement;
    struct String *OnlyDraggableToQuickslotElement;
    struct String *OnlyUsableFromQuickslotElement;
    struct String *AddsQuickslot;
    struct String *MarkElement;
    struct String *TokenElement;
    struct String *TreasureElement;
    struct String *PetFoodElement;
    struct String *TierElement;
    struct String *InvUseElement;
    struct String *DescriptionElement;
    struct String *FeedPowerElement;
    struct String *UsableElement;
    struct String *PotionElement;
    struct String *XPBonusElement;
    struct String *MpEndCostElement;
    struct String *MpCostElement;
    struct UnlockLevel__Array *UnlockLevel;
    struct LevelIncrease__Array *LevelIncrease;
    struct String *EquipmentElement;
    struct MaxHitPoints *MaxHitPointsElement;
    struct MaxMagicPoints *MaxMagicPointsElement;
    struct Attack *AttackElement;
    struct Defense *DefenseElement;
    struct Speed *SpeedElement;
    struct Dexterity *DexterityElement;
    struct String *BurstCountElement;
    struct String *BurstDelayElement;
    struct String *BurstMinDelayElement;
    struct String *Fame;
    struct String *Price;
    struct HpRegen *HpRegenElement;
    struct MpRegen *MpRegenElement;
    struct String *UnlockCostElement;
    struct Activate__Array *Activators;
    struct ActivateOnEquip__Array *ActivateOnEquip;
    struct String *CooldownElement;
    struct String *StunImmuneElement;
    struct String *ParalyzeImmuneElement;
    struct String *InvincibleElement;
    struct String *DazedImmuneElement;
    struct String *StasisImmuneElement;
    struct String *RateOfFireElement;
    struct HealthBarBoss *HealthBarBossElement;
    struct String *DosesElement;
    struct String *QuantityElement;
    struct ExtraTooltipData *ExtraTooltipDataElement;
    struct String *VaultItemElement;
    struct AnimatedTexture *AnimatedTextureElement;
    struct Animation_1__Array *AnimationElement;
    struct String *IntergamePortalElement;
    struct String *DungeonNameElement;
    struct String *MultiPhaseElement;
    struct String *PetBehaviorElement;
    struct String *PetSkin;
    struct String *DefaultSkin;
    struct String *PetAbilityElement;
    struct String *Family;
    struct String *Rarity;
    struct String *NoHatchOrFuse;
    struct String *BasicPet;
    struct WhileMoving *WhileMoving;
    struct AltTexture__Array *AltTexture;
    struct DotTexture *DotTexture;
    struct TTexture *TTexture;
    struct CrossTexture *CrossTexture;
    struct String *GroupElement;
    struct Portrait *Portrait;
    struct String *HitSound;
    struct String *DeathSound;
    struct Sound__Array *Sound;
    struct String *OldSound;
    struct String *Tex1Element;
    struct String *Tex2Element;
    struct Texture_1 *Mask_1;
    struct String *NoSkinSelect;
    struct String *UnlockSpecial;
    struct String *PlayerClassType;
    struct String *IngredeintElement;
    struct String *BgObjectElement;
    struct String *ForbidUseOnMaxHPElement;
    struct String *ForbidUseOnMaxMPElement;
    struct ForbidUseOnState *ForbidUseOnStateElement;
    struct MinimapIcon *MinimapIconElement;
    struct FollowMouse *FollowMouseElement;
    bool occupySquare;
    int32_t type;
    int32_t shadowSize;
    int32_t maxStack;
    float qsCooldownDuration;
    struct String *displayId;
    bool isPlayer;
    bool isEnemy;
    bool drawOnGround;
    bool drawUnder;
    bool fullOccupy;
    bool enemyOccupySquare;
    bool isStatic;
    bool noMiniMap;
    bool noHealthBar;
    int32_t healthBar;
    bool protectFromGroundDamage;
    bool protectFromSink;
    float z;
    bool flying;
    int32_t color;
    bool showName;
    bool dontFaceAttacks;
    bool dontFaceMovement;
    bool isUsable;
    float bloodProb;
    int32_t mpCost;
    int32_t mpEndCost;
    float cooldown;
    bool hasCooldown;
    int32_t bloodColor;
    bool ignoreHit;
    bool isForbidUseOnMaxHP;
    bool isForbidUseOnMaxMP;
    bool isForbidUseStat;
    uint32_t forbidStatId;
    int32_t feedPowerValue;
    bool alwaysPositiveHealth;
    int32_t minSize;
    int32_t maxSize;
    int32_t sizeStep;
    float angleCorrection;
    float rotation;
    int32_t slotTypeElementValue;
    struct String *className;
    float baseIndent;
    float topIndent;
    float height;
    bool wallRepeat;
    bool topRepeat;
    int32_t numProjectiles;
    float arcGap;
    bool hasTopAnimation;
    bool isSoulbound;
    bool is3dObject;
    int32_t connectType;
    int32_t questBarDistance;
    float questBarXOffset;
    float questBarYOffset;
    bool hasAnimationFrame;
    struct List_1_System_Int32_ *slotTypes;
    float rateOfFire;
    bool isGravestone;
    struct Dictionary_2_System_Byte_System_String_ *sounds;
    float abilityUseDiscount;
    int32_t tex1;
    int32_t tex2;
    struct WhileMovingProperties *whileMovingProperties;
    bool hasMinimapIcon;
    int32_t burstCountValue;
    int32_t burstDelayValue;
    int32_t burstMinDelay;
    float _pixelPerUnit;
    struct Vector2 _pivot;
    struct Vector2 inventoryIconOffset;
    struct ForgeProperties *forgeProperties;
    float summonSpeed;
};

struct ObjectProperties {
    struct ObjectProperties__Class *klass;
    MonitorData *monitor;
    struct ObjectProperties__Fields fields;
};

enum class FloatingTextType : int32_t {
    Xp = 0x00000000,
    Damage = 0x00000001,
    Fame = 0x00000002,
    LevelUp = 0x00000003,
    QuestComplete = 0x00000004,
    NewClassUnlock = 0x00000005,
    ConditionEffect = 0x00000006,
    Notification = 0x00000007,
    Exaltation = 0x00000008,
};

struct SpriteShader__Fields {
    struct MonoBehaviour__Fields _;
    struct Material *_material;
    struct Rect PCCKLFFKGJK;
    struct Vector2 GDKGLGPAFLF;
    float JNEAHLKBIDI;
    float NMAKJHLCMAF;
    float NOLIANINOPG;
    float CAEIBOOBFBD;
    bool BFANJMOOOOC;
    struct Color HFNKCLKAIPJ;
    struct Color GOCNPEOLHFM;
    struct Color CCGHNLLBBNE;
    struct Color BAPFKFALEFP;
    float IIBJFCIIALE;
    bool FMNONLFMDGJ;
    bool COMFECJAEPL;
    int32_t MFOIMKEOOAO;
    int32_t BANBNGGGHJL;
    struct MaterialPropertyBlock *JJCBPGEAGHL;
    struct SpriteRenderer *HGLIEJOCNMI;
    bool CBHDGGBKGDF;
    struct CGPOGAAKLFL *BBNEIDIMNED;
};

struct SpriteShader {
    struct SpriteShader__Class *klass;
    MonitorData *monitor;
    struct SpriteShader__Fields fields;
};

struct __declspec(align(8)) MapViewService__Fields {
    bool KEBGPCLOFJH;
    bool JAEGLFBKDCP;
    struct MapViewService_DHGDODKJNJN *DFDGAGGPLEH;
    struct MapViewService_OGJFGACDEKE *KDCGIKPHJFA;
    struct MapViewService_MBLHFLLOMLG *FBMOOHBCNNJ;
    int32_t BMPFOBPIKCA;
    struct Player *player;
    bool LKIENLEAKCC;
    struct OHMNEJGNIPN__Array *GGBKLACPDJG;
    struct List_1_OHMNEJGNIPN_ *BHNEFPBDEJD;
    struct List_1_System_Int32_ *CADHHCKOIMJ;
    struct List_1_System_Int32_ *ODPFOMDICHO;
    struct List_1_System_String_ *OMELIBMGGEM;
    int32_t GALCMPEJEGI;
    struct EJBODKMBEFD *HNLNPENOIMG;
    struct HMFEDLBIEAO *BNFMGIOKBKI;
    struct List_1_NIIFJAMEHDD_ *CIEBEOHNLJM;
    struct Dictionary_2_System_Int32_MapObject_ *HPMOKNAFJDF;
    struct Dictionary_2_System_Int32_BasicObject_ *EOJEMPFIIKE;
    struct Dictionary_2_System_Int32_BasicObject_ *ECKBPNLBBNE;
    struct Dictionary_2_System_Int32_NBNNMHCOFNH_ *GBAOPNLELNC;
    uint32_t MOGLIILDEIF;
    uint32_t ECOFENPBFEP;
    uint32_t IABDDGDNMNJ;
    struct List_1_BasicObject_ *DMCOAMBABIP;
    float FJDCBDNKPIK;
    float PIOFJNLBNPE;
    int32_t HGIHNBDFGAH;
    int32_t AEFPEAPINFO;
    struct String *CPPJGLAJKED;
    int32_t ODFIDOHGPMM;
    struct DKEACECICEK *DIDLHGAIBPK;
    int32_t BNPKHIHMFHE;
    struct HCLAMODFNBI *LPKIADKODHC;
    struct Settings *DKCDBOLECHM;
    bool KNJGHIJFLEM;
    bool FJPFDCDBLKI;
    bool ELCOJPBJIKC;
    bool MNKIKAPOBOE;
    bool GOHAALMACCK;
    int32_t AOECHPEAAAC;
    bool NMLFLDHNEDF;
    struct MiniMapManager *MPDIMLPFNBE;
    struct SocketManager_1 *HPIPJDMLKLK;
    struct GameController *LDNGFMMIBCA;
    struct HNCCPCHKKHG *EOBDBMDFFGH;
    struct JILKFLHPEGF *JBLCEJJJMEA;
    struct NBJLMDOACBC *FHBAKPDKKGL;
    struct BALKBFECMDM *EJFBENGLNBJ;
    struct BGBHFKICMIM *EFNINMGLFDC;
    bool FNECHJCLHHG;
    struct String *AJHKGIIGFOI;
    struct CLJPCEEAFLB *FIIHLJDNBII;
    bool DFCANKGHGPN;
    struct String *COHMCOPEGEA;
    bool DPDMBFLALBE;
    struct ErrorHandlerManager *OMKOFPHFHMH;
    struct HEHABDBIFHE *HPBIJEAGJBK;
    bool CBHDGGBKGDF;
    struct FHLKOBABPEJ *EAPKKHBLMOM;
    struct FHLKOBABPEJ *NKJOBLBIDOD;
    struct MapViewService_HLDDJHLCJBJ *EIGANIOKCDO;
    struct MapViewService_HLDDJHLCJBJ *GDGDJPDMCME;
};

struct MapViewService {
    struct MapViewService__Class *klass;
    MonitorData *monitor;
    struct MapViewService__Fields fields;
};

struct NativeList_1_Unity_Mathematics_float3_ {
    struct UnsafeList *m_ListData;
    #if defined(_CPLUSPLUS_)
    Allocator__Enum m_DeprecatedAllocator;
    #else
    int32_t m_DeprecatedAllocator;
    #endif
};

struct NativeList_1_FCMKBLMGMBJ_ {
    struct UnsafeList *m_ListData;
    #if defined(_CPLUSPLUS_)
    Allocator__Enum m_DeprecatedAllocator;
    #else
    int32_t m_DeprecatedAllocator;
    #endif
};

struct NativeList_1_NMLINFHMBBH_ {
    struct UnsafeList *m_ListData;
    #if defined(_CPLUSPLUS_)
    Allocator__Enum m_DeprecatedAllocator;
    #else
    int32_t m_DeprecatedAllocator;
    #endif
};

struct __declspec(align(8)) FogController__Fields {
    int32_t AEFPEAPINFO;
    int32_t HGIHNBDFGAH;
    int32_t GKKEDMEEOGB;
    struct Transform *ADGILOMJLLN;
    struct List_1_OHMNEJGNIPN_ *EGOLEIDJMHH;
    bool HGJJHGOMFGG;
    int32_t NIIHPNEMAKF;
    int32_t MOFGPKCPEHP;
    float fog_range;
    float fog_opacity;
    float FBOAOELABOJ;
    float unloaded_tile_distance;
    int32_t IBPDNCPHBHE;
    int32_t ENLLPBKDEOK;
    int32_t DFFCDMIBDBH;
    int32_t LJOCJCALFLO;
    int32_t JHCFBPBDPBI;
    int32_t NIHJNFBEANE;
    int32_t DMOJKMGBALA;
    struct Matrix4x4 LBADPIPNJOC;
    int32_t PMPHBJKGDEE;
    struct MapViewService *OHLHEKBJMOO;
    struct GameController *LDNGFMMIBCA;
    struct MJHLPJMCALH *HNAJLILMDIK;
    struct EKPPFMHGBLO *KFPMIDMMFBK;
    struct CFDIAGGALCM *AIJHBCJMHBG;
    struct PPONHNHPPIG *FNLOADIDJIG;
    struct AFCEEOKAIHB *INJOOPCFLEI;
    struct FKKEDNEGEEC *MPGGDLCIBAO;
    struct EKFIKBBDDIJ *KCCEEDBEMAG;
    struct HAAOMPPIGDK *EIPHPEOCHKN;
    struct CameraManager *KEIBIEADOBC;
    struct List_1_System_Int32_ *GENPDIOAPAJ;
    struct NativeList_1_Unity_Mathematics_float3_ PPPPCJNDEGK;
    struct NativeList_1_FCMKBLMGMBJ_ HPLGDNDNBMA;
    struct List_1_UnityEngine_Transform_ *CBDOOJGIBNC;
    struct List_1_UnityEngine_Transform_ *ECBIMBDEEGH;
    struct List_1_BasicObject_ *NOHFMNBMIOK;
    struct NativeList_1_NMLINFHMBBH_ NNACKCHOCEJ;
    struct List_1_System_Int32_ *IFJGNBANEMI;
    struct Settings *DKCDBOLECHM;
    int32_t BALPFPGCACI;
    int32_t ENLKJADEKGD;
    struct OHMNEJGNIPN *HEFOCAJCOHJ;
    struct Vector2 GMDFAGEOKHO;
};

struct FogController {
    struct FogController__Class *klass;
    MonitorData *monitor;
    struct FogController__Fields fields;
};

struct GameController__Fields {
    struct MonoBehaviour__Fields _;
    struct WaitForEndOfFrame *GFPMIDMHPON;
    struct Transform *mapElementsContainer;
    struct Transform *tilesElementContainer;
    struct Transform *projectileContainer;
    struct Transform *playerContainer;
    struct ExternalShopController *externalShopController;
    struct SteamOffersController *steamOffersController;
    struct OverlayController *overlayController;
    struct GuiManager *guiManager;
    struct ChatManager *chatManager;
    struct UnlockClassManager *unlockClassManager;
    struct NotificationManager *notificationManager;
    struct Camera *mainCamera;
    struct MiniMapManager *miniMapManager;
    struct EquipmentManager *equipmentManager;
    struct TutorialAnimationController *tutorialAnimationController;
    struct PartyUIManager *partyUiManager;
    struct List_1_Com_LuisPedroFonseca_ProCamera2D_ProCamera2D_ *cameras;
    struct Settings *settings;
    struct SocketManager_1 *HPIPJDMLKLK;
    struct HCLAMODFNBI *LPKIADKODHC;
    struct GOJNAJGEICA *JJAJGGLJGPE;
    struct OBBDHEMCCLH *IAOBHHOGKLA;
    struct Action *MGGOAFDGJDP;
};

struct GameController {
    struct GameController__Class *klass;
    MonitorData *monitor;
    struct GameController__Fields fields;
};

struct ItemSlot__Fields {
    struct MonoBehaviour__Fields _;
    struct GameObject *slotImageContainer;
    struct GameObject *slotBackgroundContainer;
    struct TextMeshProUGUI *tierLabel;
    struct TextMeshProUGUI *quantityLabel;
    int32_t JIPDPBJPGGE;
    struct MapObject *KCKGPAMMOOD;
    bool CBHDGGBKGDF;
    struct ObjectProperties *object_properties;
    int32_t GGDJDKOPBPK;
    struct UIMapObjectShader *PAPCHKNDPMA;
    struct Image *JJNOHCLNAEL;
    struct UIIconLoader *NNPNABHPEAE;
    struct RectTransform *iconRectTransform;
    bool allowAdjustIconPosition;
    struct Settings *DKCDBOLECHM;
    struct HNCCPCHKKHG *EOBDBMDFFGH;
    int32_t MJIPCOPNAKL;
};

struct ItemSlot {
    struct ItemSlot__Class *klass;
    MonitorData *monitor;
    struct ItemSlot__Fields fields;
};

enum class EMOPGKHHDGD : int32_t {
    Player = 0x00000000,
    OtherPlayer = 0x00000001,
    Npc = 0x00000002,
    Lootbag = 0x00000003,
};

enum class ItemLocationType : int32_t {
    None = 0x00000000,
    Map = 0x00000001,
    Equipment = 0x00000002,
    Inventory = 0x00000003,
    Backpack = 0x00000004,
    Quickslot = 0x00000005,
    VaultPanel = 0x00000006,
    PotionPanel = 0x00000007,
};

struct InteractiveItemSlot__Fields {
    struct ItemSlot__Fields _;
    struct Sprite *emptySlotBackground;
    struct Sprite *usedSlotBackground;
    bool ignoreDrag;
    bool FCAFCEMCHLF;
    int32_t JACEFHMDMFN;
    bool DOHLGBANCLE;
    bool HJAMBFGKFBM;
    #if defined(_CPLUSPLUS_)
    EMOPGKHHDGD DNOJABLKJHG;
    #else
    int32_t DNOJABLKJHG;
    #endif
    struct Transform *KALELMALCCC;
    struct CanvasGroup *KCEDINDNJFK;
    struct EquipmentManager *HCCCOFFFJJI;
    bool LEIOIENOGPM;
    struct PointerEventData *CPHAKFOMJHE;
    #if defined(_CPLUSPLUS_)
    ItemLocationType dragPlaceType;
    #else
    int32_t dragPlaceType;
    #endif
};

struct InteractiveItemSlot {
    struct InteractiveItemSlot__Class *klass;
    MonitorData *monitor;
    struct InteractiveItemSlot__Fields fields;
};

struct EquipmentManager__Fields {
    struct MonoBehaviour__Fields _;
    struct EquipmentManager_DLOBHGAFJPJ *MHMEGLCFADE;
    struct EquipmentManager_DLOBHGAFJPJ *JKPEMKJBAAP;
    struct GameObject *inputBlocker;
    struct Transform *dragObjectContainer;
    struct EquipmentSlot__Array *equipmentSlots;
    struct InventorySlot__Array *inventorySlots;
    struct QuickSlot__Array *quickSlots;
    struct Sprite *secondSlotCenter;
    struct Sprite *secondSlotRight;
    struct Image *secondSlot;
    struct GameObject *thirdQuickslot;
    struct DropItemHelper *IOEDNEBKAPA;
    struct MapViewService *OHLHEKBJMOO;
    struct SocketManager_1 *HPIPJDMLKLK;
    struct Player *NCEPPPOAADJ;
    int32_t IGLKBGPGJIA;
    bool CBHDGGBKGDF;
    #if defined(_CPLUSPLUS_)
    ItemLocationType KBMFHPACBOG;
    #else
    int32_t KBMFHPACBOG;
    #endif
    struct HCLAMODFNBI *LPKIADKODHC;
    struct InteractiveItemSlot *OKKPHBNPFJI;
    struct InteractiveItemSlot *PFDHCOJJIEJ;
    struct JILKFLHPEGF *GEFPKKENNGM;
    struct TooltipManager *HMLJCEJHPBN;
    struct MFJFDOPGBHL *MOFGBPJLIMF;
    struct Dictionary_2_System_Int32_Dictionary_2_System_Int32_System_Single_ *AFALBJACJJM;
};

struct EquipmentManager {
    struct EquipmentManager__Class *klass;
    MonitorData *monitor;
    struct EquipmentManager__Fields fields;
};

struct EquipmentSlot__Fields {
    struct InteractiveItemSlot__Fields _;
    struct Image *slotBackgroundImage;
    struct UIIconLoader *_iconLoader;
    struct GameObject *_slotCooldown;
    struct Image *_slotCooldownSlider;
    struct TextMeshProUGUI *_slotCooldownLabel;
    struct TextMeshProUGUI *_tierLabel;
    struct Animator *_anim;
    struct RectTransform *slotRectTransform;
    struct MapViewService *OHLHEKBJMOO;
    struct Player *NCEPPPOAADJ;
    struct Image *EPHNMJDPIGG;
    bool activeVisualCooldown;
    int32_t PANGLOGEKON;
    bool PMCABEDCKHI;
    bool JONFEEHJENG;
    float AHNLFICKHOP;
    bool GFCMAFMFJFK;
    bool MDHEMNHFKOB;
    bool LEFIPNFIKEP;
};

struct EquipmentSlot {
    struct EquipmentSlot__Class *klass;
    MonitorData *monitor;
    struct EquipmentSlot__Fields fields;
};

struct EquipmentSlot__Array {
    struct EquipmentSlot__Array__Class *klass;
    MonitorData *monitor;
    Il2CppArrayBounds *bounds;
    il2cpp_array_size_t max_length;
    struct EquipmentSlot *vector[32];
};

struct ChatManager__Fields {
    struct MonoBehaviour__Fields _;
    struct WaitForEndOfFrame *GFPMIDMHPON;
    struct WaitForSeconds *BOMOMAJHOBA;
    struct RectTransform *chatBox;
    struct TMP_InputField *inputField;
    struct ScrollRect *outputScrollView;
    struct Image *outputBackground;
    struct CanvasGroup *chatStatus;
    struct Transform *scrollViewContainer;
    struct List_1_DecaGames_RotMG_Chat_UI_ChatSlotController_ *CIIOPNMANMM;
    struct List_1_ChatSlot_ *LIHBAFIGCOO;
    struct SocketManager_1 *HPIPJDMLKLK;
    struct PMJKJDNIDML *GIKEICFBIML;
    bool OJDMDBNGJJG;
    struct TMP_SelectionCaret *FJEBIKINBGO;
    struct Image *AFKKKILEAHH;
    struct List_1_System_String_ *PEBOJIOLAPM;
    int32_t IILGDCNOANN;
    struct SettingsManager *BOJJBEJPDHF;
    struct PopupManager *KHFEOFMPGGG;
    struct Image *EJIDGDNMOAO;
    bool NPKAPFOJHHH;
    struct HCLAMODFNBI *LPKIADKODHC;
    bool interactKeyIsActive;
    struct DelayMethodManager *EMIPKAKCMPG;
    struct MapViewService *OHLHEKBJMOO;
};

struct ChatManager {
    struct ChatManager__Class *klass;
    MonitorData *monitor;
    struct ChatManager__Fields fields;
};

struct CameraManager__Fields {
    struct MonoBehaviour__Fields _;
    bool JGOPOFJJPMM;
    bool AGDBAFOEPGO;
    float CGHMEBPNPNJ;
    struct Transform *mainCameraContainer;
    struct Transform *miniMapCameraTransform;
    struct ProCamera2D *proCamera2D;
    struct ProCamera2DPixelPerfect *BDAEGGDPHCK;
    struct Camera *EHHILFMGPMB;
    struct CameraPerspectiveEditor *perspective_editor;
    bool FPNMHACOHEK;
    struct MADPOKNCADM *COCCGGGBDFP;
    float Z;
    struct MapViewService *OHLHEKBJMOO;
    struct MiniMapManager *MPDIMLPFNBE;
    int32_t IKDDKAAFLEH;
    struct Single__Array *DCGGEJPEBEC;
    bool IGFKDKCGFAL;
};

struct CameraManager {
    struct CameraManager__Class *klass;
    MonitorData *monitor;
    struct CameraManager__Fields fields;
};

struct CameraPerspectiveEditor__Fields {
    struct MonoBehaviour__Fields _;
    struct Vector2 lensShift;
    bool lensShiftProportionalToAspect;
    struct Vector2 lensTilt;
    struct Vector2 positionShift;
    struct Vector2 skew;
    struct Vector2 aspectScale;
    struct Vector2 clippingPlaneSkew;
    float dollyZoom;
    float dollyZoomFocalDistance;
    struct Transform *dollyZoomFocalTarget;
    struct Camera *JKMDPFHCOMK;
    struct Matrix4x4 NNPDMHACCFE;
    struct Vector2 BGBNPGMIFAL;
    float GKIIDCAHEJP;
    float JGFEFCNHAMA;
    struct Matrix4x4 BLEIOHEMDHI;
    struct Vector3 MCKDKJDBOKB;
    bool LDFPDFCNAMI;
    float GDOKJDLKHDD;
    float KBHDJIPPODN;
    float IDAFJEJKOCM;
    float BKOJOHAKFKO;
    float JKNJEPDPKAD;
    float MFFPHGGKHIJ;
    bool JCHMBOEKMDG;
};

struct CameraPerspectiveEditor {
    struct CameraPerspectiveEditor__Class *klass;
    MonitorData *monitor;
    struct CameraPerspectiveEditor__Fields fields;
};

struct NIIFJAMEHDD__Fields {
    struct MapObject__Fields _;
    struct List_1_NOBHMIPLKAP_ *DOENFMFONLM;
    float NMCEDOFIKDL;
    bool FCAFCEMCHLF;
    bool LLKEJMLKCCA;
};

struct NIIFJAMEHDD {
    struct NIIFJAMEHDD__Class *klass;
    MonitorData *monitor;
    struct NIIFJAMEHDD__Fields fields;
};

struct Pet__Fields {
    struct NIIFJAMEHDD__Fields _;
    struct KFAICNFFPBF *GFKKAPGKPDP;
    int32_t PHNLNOOLAIO;
    bool OBKOMAKIAAB;
    struct ObjectProperties *FGPKMNEABHD;
    struct ObjectProperties *object_props;
    struct ObjectProperties *NBEJOKEADNJ;
    bool INBKGJMLAKI;
    struct Player *KCKGPAMMOOD;
    bool MCNLCNGGFAP;
    bool FOIHFCCDDBD;
    struct List_1_NOBHMIPLKAP_ *NDMLNEAKBOI;
};

struct Pet {
    struct Pet__Class *klass;
    MonitorData *monitor;
    struct Pet__Fields fields;
};

struct FogController__VTable {
    VirtualInvokeData Equals;
    VirtualInvokeData Finalize;
    VirtualInvokeData GetHashCode;
    VirtualInvokeData ToString;
};

struct FogController__StaticFields {
    float LHPKACGFBPO;
    int32_t view_distance;
    int32_t KMIFAGJEIKE;
    int32_t LCNOIMECNPI;
};

struct FogController__Class {
    Il2CppClass_0 _0;
    Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
    struct FogController__StaticFields *static_fields;
    const Il2CppRGCTXData *rgctx_data;
    Il2CppClass_1 _1;
    struct FogController__VTable vtable;
};

struct MapViewService__VTable {
    VirtualInvokeData Equals;
    VirtualInvokeData Finalize;
    VirtualInvokeData GetHashCode;
    VirtualInvokeData ToString;
};

struct MapViewService__StaticFields {
    struct String *DGLELDANGBB;
    struct List_1_System_String_ *OEBEDLBDAMA;
    struct List_1_System_String_ *ENPBKGPCFMN;
    struct List_1_System_String_ *CKCELAEFOFE;
    bool FIDKPOAMOAO;
    bool MDJOIJMEJBJ;
    struct FogController *DILPMFEEJCP;
    float LFDCHMKDHKP;
};

struct MapViewService__Class {
    Il2CppClass_0 _0;
    Il2CppRuntimeInterfaceOffsetPair *interfaceOffsets;
    struct MapViewService__StaticFields *static_fields;
    const Il2CppRGCTXData *rgctx_data;
    Il2CppClass_1 _1;
    struct MapViewService__VTable vtable;
};

struct MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager___Fields {
    struct MonoBehaviour__Fields _;
    bool DHEPPKMKIGP;
};

struct MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager_ {
    struct MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager___Class *klass;
    MonitorData *monitor;
    struct MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager___Fields fields;
};

struct ApplicationManager__Fields {
    struct MonoSingleton_1_DecaGames_RotMG_Managers_ApplicationManager___Fields _;
    struct HCLAMODFNBI *_EOJBAHKEDEG_k__BackingField;
    struct EntityManager _GDMCNAFMKEI_k__BackingField;
    struct TaskManager *_KOLBBFNBOAG_k__BackingField;
    struct SocketManager_1 *_GDHHIGCAIJI_k__BackingField;
    struct AppEngineManager *_EFMBMDPPOJK_k__BackingField;
    struct AppEngineClient *_HNCCLNHOGMM_k__BackingField;
    struct PopupManager *_DLHGABBKNMP_k__BackingField;
    struct GameController *_LNNJMOPDJED_k__BackingField;
    struct ErrorHandlerManager *_FHMMGAHOFBJ_k__BackingField;
    struct CameraManager *_DAMHCKMAHGM_k__BackingField;
    struct FadeManager *_IFJJCLNBDBA_k__BackingField;
    struct CharactersMetricsTracker *_IOBAJOPHKEC_k__BackingField;
    struct InputManager *_AJCCBODONLM_k__BackingField;
    struct VisualSettings *_GHNJCMENJEL_k__BackingField;
    struct SoundSettings *_HELDMCFNHBA_k__BackingField;
    struct SettingsManager *_NEFPFALLFBD_k__BackingField;
    struct HNCCPCHKKHG *_BPKGNAPMIDG_k__BackingField;
    struct MapViewService *_HOKMJBEGNCK_k__BackingField;
    struct FKNJGNBCGON *_GKKCCMLBOEE_k__BackingField;
    struct TooltipManager *_ANKPJELCCHN_k__BackingField;
    struct ShopManager *_CKCIJGGEIKM_k__BackingField;
    struct DelayMethodManager *_CACGOMBBAJP_k__BackingField;
    struct DebugConsole *_NAEEHNDHJBH_k__BackingField;
    struct SoundManager *_PPJFKECCPMO_k__BackingField;
    struct NHEAKJPHCGC *_NMFDGAILNEF_k__BackingField;
    struct KFNNGACEKHK *_DILGODCALJF_k__BackingField;
    struct LoadImageManager *_CJEHEFECILI_k__BackingField;
    struct NDOAILOBIKC *_BKKIDMNPOJK_k__BackingField;
    struct KKMBKIAKDCC *_AGAKMGNCHDA_k__BackingField;
    struct DKOAEHAOGPN *_MMMOGCFIEPP_k__BackingField;
    struct KIJEBPDLFID *_BCDPFICEIJM_k__BackingField;
    struct NCEKHOMHKOG *_LAHNDMLIIIM_k__BackingField;
    struct NOKENPCHCDE *_ADOFIDIACLF_k__BackingField;
    struct MICPFEDBHDI *_GEGNFLNAION_k__BackingField;
    struct TutorialManager *_GFOCJPOFMJK_k__BackingField;
    struct AHLHJGLGCDJ *_DJMICDKMBOF_k__BackingField;
    struct IdleWatcher *_PKIMDALNKPF_k__BackingField;
    struct NLKABJCKLGG *_JGEOINEMOFM_k__BackingField;
    struct EHELFMCHOHD *_AALBGNKDAPI_k__BackingField;
    struct IFOLJGOEBNJ *_PDHCNJFJDAK_k__BackingField;
    struct MFJFDOPGBHL *_KNBKNBCMLJL_k__BackingField;
    struct PLEDFIMAEJB *_ECGGFLHCEJN_k__BackingField;
    struct RemoteConfigManager *_PFELAOLKNNI_k__BackingField;
    struct PMGCIFDMADL *_FDNNCPADFHN_k__BackingField;
    struct DDAACJDHJFD *_LAPNKBADMCD_k__BackingField;
    struct PDEEEIOPNFA *_HNJIOJEGKAF_k__BackingField;
    struct FPSCounter *FpsCounter;
    struct GameObject *fpsCounterGO;
    struct DevConsoleManager *_EDMIKJGJAKP_k__BackingField;
    struct GameObject *devConsoleManagerGO;
    struct String *mapJson;
    struct Camera *bootstrapCamera;
    bool _BHLBIJBELAH_k__BackingField;
    bool IsIntegratedGraphicCard;
    bool UseLocalAssets;
    bool PDDCLOPLJHH;
    int32_t HLFELIKNFJO;
};

struct ApplicationManager {
    struct ApplicationManager__Class *klass;
    MonitorData *monitor;
    struct ApplicationManager__Fields fields;
};

struct UnityThread__Fields {
    struct MonoBehaviour__Fields _;
};

struct UnityThread {
    struct UnityThread__Class *klass;
    MonitorData *monitor;
    struct UnityThread__Fields fields;
};

} // end namespace app