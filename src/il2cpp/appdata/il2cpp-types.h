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

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct Color32 {
    int32_t rgba;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Transform__Fields {
    struct Component__Fields _;
};

struct Transform {
    struct Transform__Class *klass;
    MonitorData *monitor;
    struct Transform__Fields fields;
};

struct GameObject__Fields {
    struct Object__Fields _;
};

struct GameObject {
    struct GameObject__Class *klass;
    MonitorData *monitor;
    struct GameObject__Fields fields;
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

enum class KeyCode : int32_t {
    None = 0x00000000,
    Backspace = 0x00000008,
    Delete = 0x0000007f,
    Tab = 0x00000009,
    Clear = 0x0000000c,
    Return = 0x0000000d,
    Pause = 0x00000013,
    Escape = 0x0000001b,
    Space = 0x00000020,
    Keypad0 = 0x00000100,
    Keypad1 = 0x00000101,
    Keypad2 = 0x00000102,
    Keypad3 = 0x00000103,
    Keypad4 = 0x00000104,
    Keypad5 = 0x00000105,
    Keypad6 = 0x00000106,
    Keypad7 = 0x00000107,
    Keypad8 = 0x00000108,
    Keypad9 = 0x00000109,
    KeypadPeriod = 0x0000010a,
    KeypadDivide = 0x0000010b,
    KeypadMultiply = 0x0000010c,
    KeypadMinus = 0x0000010d,
    KeypadPlus = 0x0000010e,
    KeypadEnter = 0x0000010f,
    KeypadEquals = 0x00000110,
    UpArrow = 0x00000111,
    DownArrow = 0x00000112,
    RightArrow = 0x00000113,
    LeftArrow = 0x00000114,
    Insert = 0x00000115,
    Home = 0x00000116,
    End = 0x00000117,
    PageUp = 0x00000118,
    PageDown = 0x00000119,
    F1 = 0x0000011a,
    F2 = 0x0000011b,
    F3 = 0x0000011c,
    F4 = 0x0000011d,
    F5 = 0x0000011e,
    F6 = 0x0000011f,
    F7 = 0x00000120,
    F8 = 0x00000121,
    F9 = 0x00000122,
    F10 = 0x00000123,
    F11 = 0x00000124,
    F12 = 0x00000125,
    F13 = 0x00000126,
    F14 = 0x00000127,
    F15 = 0x00000128,
    Alpha0 = 0x00000030,
    Alpha1 = 0x00000031,
    Alpha2 = 0x00000032,
    Alpha3 = 0x00000033,
    Alpha4 = 0x00000034,
    Alpha5 = 0x00000035,
    Alpha6 = 0x00000036,
    Alpha7 = 0x00000037,
    Alpha8 = 0x00000038,
    Alpha9 = 0x00000039,
    Exclaim = 0x00000021,
    DoubleQuote = 0x00000022,
    Hash = 0x00000023,
    Dollar = 0x00000024,
    Percent = 0x00000025,
    Ampersand = 0x00000026,
    Quote = 0x00000027,
    LeftParen = 0x00000028,
    RightParen = 0x00000029,
    Asterisk = 0x0000002a,
    Plus = 0x0000002b,
    Comma = 0x0000002c,
    Minus = 0x0000002d,
    Period = 0x0000002e,
    Slash = 0x0000002f,
    Colon = 0x0000003a,
    Semicolon = 0x0000003b,
    Less = 0x0000003c,
    Equals = 0x0000003d,
    Greater = 0x0000003e,
    Question = 0x0000003f,
    At = 0x00000040,
    LeftBracket = 0x0000005b,
    Backslash = 0x0000005c,
    RightBracket = 0x0000005d,
    Caret = 0x0000005e,
    Underscore = 0x0000005f,
    BackQuote = 0x00000060,
    A = 0x00000061,
    B = 0x00000062,
    C = 0x00000063,
    D = 0x00000064,
    E = 0x00000065,
    F = 0x00000066,
    G = 0x00000067,
    H = 0x00000068,
    I = 0x00000069,
    J = 0x0000006a,
    K = 0x0000006b,
    L = 0x0000006c,
    M = 0x0000006d,
    N = 0x0000006e,
    O = 0x0000006f,
    P = 0x00000070,
    Q = 0x00000071,
    R = 0x00000072,
    S = 0x00000073,
    T = 0x00000074,
    U = 0x00000075,
    V = 0x00000076,
    W = 0x00000077,
    X = 0x00000078,
    Y = 0x00000079,
    Z = 0x0000007a,
    LeftCurlyBracket = 0x0000007b,
    Pipe = 0x0000007c,
    RightCurlyBracket = 0x0000007d,
    Tilde = 0x0000007e,
    Numlock = 0x0000012c,
    CapsLock = 0x0000012d,
    ScrollLock = 0x0000012e,
    RightShift = 0x0000012f,
    LeftShift = 0x00000130,
    RightControl = 0x00000131,
    LeftControl = 0x00000132,
    RightAlt = 0x00000133,
    LeftAlt = 0x00000134,
    LeftCommand = 0x00000136,
    LeftApple = 0x00000136,
    LeftWindows = 0x00000137,
    RightCommand = 0x00000135,
    RightApple = 0x00000135,
    RightWindows = 0x00000138,
    AltGr = 0x00000139,
    Help = 0x0000013b,
    Print = 0x0000013c,
    SysReq = 0x0000013d,
    Break = 0x0000013e,
    Menu = 0x0000013f,
    Mouse0 = 0x00000143,
    Mouse1 = 0x00000144,
    Mouse2 = 0x00000145,
    Mouse3 = 0x00000146,
    Mouse4 = 0x00000147,
    Mouse5 = 0x00000148,
    Mouse6 = 0x00000149,
    JoystickButton0 = 0x0000014a,
    JoystickButton1 = 0x0000014b,
    JoystickButton2 = 0x0000014c,
    JoystickButton3 = 0x0000014d,
    JoystickButton4 = 0x0000014e,
    JoystickButton5 = 0x0000014f,
    JoystickButton6 = 0x00000150,
    JoystickButton7 = 0x00000151,
    JoystickButton8 = 0x00000152,
    JoystickButton9 = 0x00000153,
    JoystickButton10 = 0x00000154,
    JoystickButton11 = 0x00000155,
    JoystickButton12 = 0x00000156,
    JoystickButton13 = 0x00000157,
    JoystickButton14 = 0x00000158,
    JoystickButton15 = 0x00000159,
    JoystickButton16 = 0x0000015a,
    JoystickButton17 = 0x0000015b,
    JoystickButton18 = 0x0000015c,
    JoystickButton19 = 0x0000015d,
    Joystick1Button0 = 0x0000015e,
    Joystick1Button1 = 0x0000015f,
    Joystick1Button2 = 0x00000160,
    Joystick1Button3 = 0x00000161,
    Joystick1Button4 = 0x00000162,
    Joystick1Button5 = 0x00000163,
    Joystick1Button6 = 0x00000164,
    Joystick1Button7 = 0x00000165,
    Joystick1Button8 = 0x00000166,
    Joystick1Button9 = 0x00000167,
    Joystick1Button10 = 0x00000168,
    Joystick1Button11 = 0x00000169,
    Joystick1Button12 = 0x0000016a,
    Joystick1Button13 = 0x0000016b,
    Joystick1Button14 = 0x0000016c,
    Joystick1Button15 = 0x0000016d,
    Joystick1Button16 = 0x0000016e,
    Joystick1Button17 = 0x0000016f,
    Joystick1Button18 = 0x00000170,
    Joystick1Button19 = 0x00000171,
    Joystick2Button0 = 0x00000172,
    Joystick2Button1 = 0x00000173,
    Joystick2Button2 = 0x00000174,
    Joystick2Button3 = 0x00000175,
    Joystick2Button4 = 0x00000176,
    Joystick2Button5 = 0x00000177,
    Joystick2Button6 = 0x00000178,
    Joystick2Button7 = 0x00000179,
    Joystick2Button8 = 0x0000017a,
    Joystick2Button9 = 0x0000017b,
    Joystick2Button10 = 0x0000017c,
    Joystick2Button11 = 0x0000017d,
    Joystick2Button12 = 0x0000017e,
    Joystick2Button13 = 0x0000017f,
    Joystick2Button14 = 0x00000180,
    Joystick2Button15 = 0x00000181,
    Joystick2Button16 = 0x00000182,
    Joystick2Button17 = 0x00000183,
    Joystick2Button18 = 0x00000184,
    Joystick2Button19 = 0x00000185,
    Joystick3Button0 = 0x00000186,
    Joystick3Button1 = 0x00000187,
    Joystick3Button2 = 0x00000188,
    Joystick3Button3 = 0x00000189,
    Joystick3Button4 = 0x0000018a,
    Joystick3Button5 = 0x0000018b,
    Joystick3Button6 = 0x0000018c,
    Joystick3Button7 = 0x0000018d,
    Joystick3Button8 = 0x0000018e,
    Joystick3Button9 = 0x0000018f,
    Joystick3Button10 = 0x00000190,
    Joystick3Button11 = 0x00000191,
    Joystick3Button12 = 0x00000192,
    Joystick3Button13 = 0x00000193,
    Joystick3Button14 = 0x00000194,
    Joystick3Button15 = 0x00000195,
    Joystick3Button16 = 0x00000196,
    Joystick3Button17 = 0x00000197,
    Joystick3Button18 = 0x00000198,
    Joystick3Button19 = 0x00000199,
    Joystick4Button0 = 0x0000019a,
    Joystick4Button1 = 0x0000019b,
    Joystick4Button2 = 0x0000019c,
    Joystick4Button3 = 0x0000019d,
    Joystick4Button4 = 0x0000019e,
    Joystick4Button5 = 0x0000019f,
    Joystick4Button6 = 0x000001a0,
    Joystick4Button7 = 0x000001a1,
    Joystick4Button8 = 0x000001a2,
    Joystick4Button9 = 0x000001a3,
    Joystick4Button10 = 0x000001a4,
    Joystick4Button11 = 0x000001a5,
    Joystick4Button12 = 0x000001a6,
    Joystick4Button13 = 0x000001a7,
    Joystick4Button14 = 0x000001a8,
    Joystick4Button15 = 0x000001a9,
    Joystick4Button16 = 0x000001aa,
    Joystick4Button17 = 0x000001ab,
    Joystick4Button18 = 0x000001ac,
    Joystick4Button19 = 0x000001ad,
    Joystick5Button0 = 0x000001ae,
    Joystick5Button1 = 0x000001af,
    Joystick5Button2 = 0x000001b0,
    Joystick5Button3 = 0x000001b1,
    Joystick5Button4 = 0x000001b2,
    Joystick5Button5 = 0x000001b3,
    Joystick5Button6 = 0x000001b4,
    Joystick5Button7 = 0x000001b5,
    Joystick5Button8 = 0x000001b6,
    Joystick5Button9 = 0x000001b7,
    Joystick5Button10 = 0x000001b8,
    Joystick5Button11 = 0x000001b9,
    Joystick5Button12 = 0x000001ba,
    Joystick5Button13 = 0x000001bb,
    Joystick5Button14 = 0x000001bc,
    Joystick5Button15 = 0x000001bd,
    Joystick5Button16 = 0x000001be,
    Joystick5Button17 = 0x000001bf,
    Joystick5Button18 = 0x000001c0,
    Joystick5Button19 = 0x000001c1,
    Joystick6Button0 = 0x000001c2,
    Joystick6Button1 = 0x000001c3,
    Joystick6Button2 = 0x000001c4,
    Joystick6Button3 = 0x000001c5,
    Joystick6Button4 = 0x000001c6,
    Joystick6Button5 = 0x000001c7,
    Joystick6Button6 = 0x000001c8,
    Joystick6Button7 = 0x000001c9,
    Joystick6Button8 = 0x000001ca,
    Joystick6Button9 = 0x000001cb,
    Joystick6Button10 = 0x000001cc,
    Joystick6Button11 = 0x000001cd,
    Joystick6Button12 = 0x000001ce,
    Joystick6Button13 = 0x000001cf,
    Joystick6Button14 = 0x000001d0,
    Joystick6Button15 = 0x000001d1,
    Joystick6Button16 = 0x000001d2,
    Joystick6Button17 = 0x000001d3,
    Joystick6Button18 = 0x000001d4,
    Joystick6Button19 = 0x000001d5,
    Joystick7Button0 = 0x000001d6,
    Joystick7Button1 = 0x000001d7,
    Joystick7Button2 = 0x000001d8,
    Joystick7Button3 = 0x000001d9,
    Joystick7Button4 = 0x000001da,
    Joystick7Button5 = 0x000001db,
    Joystick7Button6 = 0x000001dc,
    Joystick7Button7 = 0x000001dd,
    Joystick7Button8 = 0x000001de,
    Joystick7Button9 = 0x000001df,
    Joystick7Button10 = 0x000001e0,
    Joystick7Button11 = 0x000001e1,
    Joystick7Button12 = 0x000001e2,
    Joystick7Button13 = 0x000001e3,
    Joystick7Button14 = 0x000001e4,
    Joystick7Button15 = 0x000001e5,
    Joystick7Button16 = 0x000001e6,
    Joystick7Button17 = 0x000001e7,
    Joystick7Button18 = 0x000001e8,
    Joystick7Button19 = 0x000001e9,
    Joystick8Button0 = 0x000001ea,
    Joystick8Button1 = 0x000001eb,
    Joystick8Button2 = 0x000001ec,
    Joystick8Button3 = 0x000001ed,
    Joystick8Button4 = 0x000001ee,
    Joystick8Button5 = 0x000001ef,
    Joystick8Button6 = 0x000001f0,
    Joystick8Button7 = 0x000001f1,
    Joystick8Button8 = 0x000001f2,
    Joystick8Button9 = 0x000001f3,
    Joystick8Button10 = 0x000001f4,
    Joystick8Button11 = 0x000001f5,
    Joystick8Button12 = 0x000001f6,
    Joystick8Button13 = 0x000001f7,
    Joystick8Button14 = 0x000001f8,
    Joystick8Button15 = 0x000001f9,
    Joystick8Button16 = 0x000001fa,
    Joystick8Button17 = 0x000001fb,
    Joystick8Button18 = 0x000001fc,
    Joystick8Button19 = 0x000001fd,
};

struct RaycastHit2D {
    struct Vector2 m_Centroid;
    struct Vector2 m_Point;
    struct Vector2 m_Normal;
    float m_Distance;
    float m_Fraction;
    int32_t m_Collider;
};

struct EntityManager {
    struct EntityDataAccess *m_EntityDataAccess;
};

struct UIBehaviour__Fields {
    struct MonoBehaviour__Fields _;
};

struct UIBehaviour {
    struct UIBehaviour__Class *klass;
    MonitorData *monitor;
    struct UIBehaviour__Fields fields;
};

struct Graphic__Fields {
    struct UIBehaviour__Fields _;
    struct Material *m_Material;
    struct Color m_Color;
    bool m_SkipLayoutUpdate;
    bool m_SkipMaterialUpdate;
    bool m_RaycastTarget;
    struct RectTransform *m_RectTransform;
    struct CanvasRenderer *m_CanvasRenderer;
    struct Canvas *m_Canvas;
    bool m_VertsDirty;
    bool m_MaterialDirty;
    struct UnityAction *m_OnDirtyLayoutCallback;
    struct UnityAction *m_OnDirtyVertsCallback;
    struct UnityAction *m_OnDirtyMaterialCallback;
    struct Mesh *m_CachedMesh;
    struct Vector2__Array *m_CachedUvs;
    struct TweenRunner_1_ColorTween_ *m_ColorTweenRunner;
    bool _useLegacyMeshGeneration_k__BackingField;
};

struct Graphic {
    struct Graphic__Class *klass;
    MonitorData *monitor;
    struct Graphic__Fields fields;
};

struct MaskableGraphic__Fields {
    struct Graphic__Fields _;
    bool m_ShouldRecalculateStencil;
    struct Material *m_MaskMaterial;
    struct RectMask2D *m_ParentMask;
    bool m_Maskable;
    bool m_IsMaskingGraphic;
    bool m_IncludeForMasking;
    struct MaskableGraphic_CullStateChangedEvent *m_OnCullStateChanged;
    bool m_ShouldRecalculate;
    int32_t m_StencilValue;
    struct Vector3__Array *m_Corners;
};

struct MaskableGraphic {
    struct MaskableGraphic__Class *klass;
    MonitorData *monitor;
    struct MaskableGraphic__Fields fields;
};

enum class ColorMode : int32_t {
    Single = 0x00000000,
    HorizontalGradient = 0x00000001,
    VerticalGradient = 0x00000002,
    FourCornersGradient = 0x00000003,
};

struct MaterialReference {
    int32_t index;
    struct TMP_FontAsset *fontAsset;
    struct TMP_SpriteAsset *spriteAsset;
    struct Material *material;
    bool isDefaultMaterial;
    bool isFallbackMaterial;
    struct Material *fallbackMaterial;
    float padding;
    int32_t referenceCount;
};

struct TMP_Offset {
    float m_Left;
    float m_Right;
    float m_Top;
    float m_Bottom;
};

struct HighlightState {
    struct Color32 color;
    struct TMP_Offset padding;
};

enum class TextAlignmentOptions : int32_t {
    TopLeft = 0x00000101,
    Top = 0x00000102,
    TopRight = 0x00000104,
    TopJustified = 0x00000108,
    TopFlush = 0x00000110,
    TopGeoAligned = 0x00000120,
    Left = 0x00000201,
    Center = 0x00000202,
    Right = 0x00000204,
    Justified = 0x00000208,
    Flush = 0x00000210,
    CenterGeoAligned = 0x00000220,
    BottomLeft = 0x00000401,
    Bottom = 0x00000402,
    BottomRight = 0x00000404,
    BottomJustified = 0x00000408,
    BottomFlush = 0x00000410,
    BottomGeoAligned = 0x00000420,
    BaselineLeft = 0x00000801,
    Baseline = 0x00000802,
    BaselineRight = 0x00000804,
    BaselineJustified = 0x00000808,
    BaselineFlush = 0x00000810,
    BaselineGeoAligned = 0x00000820,
    MidlineLeft = 0x00001001,
    Midline = 0x00001002,
    MidlineRight = 0x00001004,
    MidlineJustified = 0x00001008,
    MidlineFlush = 0x00001010,
    MidlineGeoAligned = 0x00001020,
    CaplineLeft = 0x00002001,
    Capline = 0x00002002,
    CaplineRight = 0x00002004,
    CaplineJustified = 0x00002008,
    CaplineFlush = 0x00002010,
    CaplineGeoAligned = 0x00002020,
    Converted = 0x0000ffff,
};

struct TMP_TextProcessingStack_1_MaterialReference_ {
    struct MaterialReference__Array *itemStack;
    int32_t index;
    struct MaterialReference m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

struct VertexGradient {
    struct Color topLeft;
    struct Color topRight;
    struct Color bottomLeft;
    struct Color bottomRight;
};

struct TMP_TextProcessingStack_1_System_Single_ {
    struct Single__Array *itemStack;
    int32_t index;
    float m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

enum class FontWeight : int32_t {
    Thin = 0x00000064,
    ExtraLight = 0x000000c8,
    Light = 0x0000012c,
    Regular = 0x00000190,
    Medium = 0x000001f4,
    SemiBold = 0x00000258,
    Bold = 0x000002bc,
    Heavy = 0x00000320,
    Black = 0x00000384,
};

struct TMP_TextProcessingStack_1_FontWeight_ {
    struct FontWeight__Array *itemStack;
    int32_t index;
    #if defined(_CPLUSPLUS_)
    FontWeight m_DefaultItem;
    #else
    int32_t m_DefaultItem;
    #endif
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

enum class FontStyles : int32_t {
    Normal = 0x00000000,
    Bold = 0x00000001,
    Italic = 0x00000002,
    Underline = 0x00000004,
    LowerCase = 0x00000008,
    UpperCase = 0x00000010,
    SmallCaps = 0x00000020,
    Strikethrough = 0x00000040,
    Superscript = 0x00000080,
    Subscript = 0x00000100,
    Highlight = 0x00000200,
};

struct TMP_FontStyleStack {
    uint8_t bold;
    uint8_t italic;
    uint8_t underline;
    uint8_t strikethrough;
    uint8_t highlight;
    uint8_t superscript;
    uint8_t subscript;
    uint8_t uppercase;
    uint8_t lowercase;
    uint8_t smallcaps;
};

enum class HorizontalAlignmentOptions : int32_t {
    Left = 0x00000001,
    Center = 0x00000002,
    Right = 0x00000004,
    Justified = 0x00000008,
    Flush = 0x00000010,
    Geometry = 0x00000020,
};

enum class VerticalAlignmentOptions : int32_t {
    Top = 0x00000100,
    Middle = 0x00000200,
    Bottom = 0x00000400,
    Baseline = 0x00000800,
    Geometry = 0x00001000,
    Capline = 0x00002000,
};

struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_ {
    struct HorizontalAlignmentOptions__Array *itemStack;
    int32_t index;
    #if defined(_CPLUSPLUS_)
    HorizontalAlignmentOptions m_DefaultItem;
    #else
    int32_t m_DefaultItem;
    #endif
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

enum class TextOverflowModes : int32_t {
    Overflow = 0x00000000,
    Ellipsis = 0x00000001,
    Masking = 0x00000002,
    Truncate = 0x00000003,
    ScrollRect = 0x00000004,
    Page = 0x00000005,
    Linked = 0x00000006,
};

enum class TextureMappingOptions : int32_t {
    Character = 0x00000000,
    Line = 0x00000001,
    Paragraph = 0x00000002,
    MatchAspect = 0x00000003,
};

enum class TextRenderFlags : int32_t {
    DontRender = 0x00000000,
    Render = 0x000000ff,
};

enum class VertexSortingOrder : int32_t {
    Normal = 0x00000000,
    Reverse = 0x00000001,
};

enum class TMP_Text_TextInputSources : int32_t {
    Text = 0x00000000,
    SetText = 0x00000001,
    SetCharArray = 0x00000002,
    String = 0x00000003,
};

struct Extents {
    struct Vector2 min;
    struct Vector2 max;
};

struct TMP_LineInfo {
    int32_t controlCharacterCount;
    int32_t characterCount;
    int32_t visibleCharacterCount;
    int32_t spaceCount;
    int32_t wordCount;
    int32_t firstCharacterIndex;
    int32_t firstVisibleCharacterIndex;
    int32_t lastCharacterIndex;
    int32_t lastVisibleCharacterIndex;
    float length;
    float lineHeight;
    float ascender;
    float baseline;
    float descender;
    float maxAdvance;
    float width;
    float marginLeft;
    float marginRight;
    #if defined(_CPLUSPLUS_)
    HorizontalAlignmentOptions alignment;
    #else
    int32_t alignment;
    #endif
    struct Extents lineExtents;
};

struct TMP_TextProcessingStack_1_System_Int32_ {
    struct Int32__Array *itemStack;
    int32_t index;
    int32_t m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

struct TMP_TextProcessingStack_1_UnityEngine_Color32_ {
    struct Color32__Array *itemStack;
    int32_t index;
    struct Color32 m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

struct TMP_TextProcessingStack_1_HighlightState_ {
    struct HighlightState__Array *itemStack;
    int32_t index;
    struct HighlightState m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

struct TMP_TextProcessingStack_1_TMP_ColorGradient_ {
    struct TMP_ColorGradient__Array *itemStack;
    int32_t index;
    struct TMP_ColorGradient *m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

struct WordWrapState {
    int32_t previous_WordBreak;
    int32_t total_CharacterCount;
    int32_t visible_CharacterCount;
    int32_t visible_SpriteCount;
    int32_t visible_LinkCount;
    int32_t firstCharacterIndex;
    int32_t firstVisibleCharacterIndex;
    int32_t lastCharacterIndex;
    int32_t lastVisibleCharIndex;
    int32_t lineNumber;
    float maxCapHeight;
    float maxAscender;
    float maxDescender;
    float startOfLineAscender;
    float maxLineAscender;
    float maxLineDescender;
    float pageAscender;
    #if defined(_CPLUSPLUS_)
    HorizontalAlignmentOptions horizontalAlignment;
    #else
    int32_t horizontalAlignment;
    #endif
    float marginLeft;
    float marginRight;
    float xAdvance;
    float preferredWidth;
    float preferredHeight;
    float previousLineScale;
    int32_t wordCount;
    #if defined(_CPLUSPLUS_)
    FontStyles fontStyle;
    #else
    int32_t fontStyle;
    #endif
    int32_t italicAngle;
    float fontScale;
    float fontScaleMultiplier;
    float currentFontSize;
    float baselineOffset;
    float lineOffset;
    bool isDrivenLineSpacing;
    float glyphHorizontalAdvanceAdjustment;
    float cSpace;
    float mSpace;
    struct TMP_TextInfo *textInfo;
    struct TMP_LineInfo lineInfo;
    struct Color32 vertexColor;
    struct Color32 underlineColor;
    struct Color32 strikethroughColor;
    struct Color32 highlightColor;
    struct TMP_FontStyleStack basicStyleStack;
    struct TMP_TextProcessingStack_1_System_Int32_ italicAngleStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ colorStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ underlineColorStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ strikethroughColorStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ highlightColorStack;
    struct TMP_TextProcessingStack_1_HighlightState_ highlightStateStack;
    struct TMP_TextProcessingStack_1_TMP_ColorGradient_ colorGradientStack;
    struct TMP_TextProcessingStack_1_System_Single_ sizeStack;
    struct TMP_TextProcessingStack_1_System_Single_ indentStack;
    struct TMP_TextProcessingStack_1_FontWeight_ fontWeightStack;
    struct TMP_TextProcessingStack_1_System_Int32_ styleStack;
    struct TMP_TextProcessingStack_1_System_Single_ baselineStack;
    struct TMP_TextProcessingStack_1_System_Int32_ actionStack;
    struct TMP_TextProcessingStack_1_MaterialReference_ materialReferenceStack;
    struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_ lineJustificationStack;
    int32_t spriteAnimationID;
    struct TMP_FontAsset *currentFontAsset;
    struct TMP_SpriteAsset *currentSpriteAsset;
    struct Material *currentMaterial;
    int32_t currentMaterialIndex;
    struct Extents meshExtents;
    bool tagNoParsing;
    bool isNonBreakingSpace;
};

struct TMP_TextProcessingStack_1_WordWrapState_ {
    struct WordWrapState__Array *itemStack;
    int32_t index;
    struct WordWrapState m_DefaultItem;
    int32_t m_Capacity;
    int32_t m_RolloverSize;
    int32_t m_Count;
};

enum class TMP_TextElementType : int32_t {
    Character = 0x00000000,
    Sprite = 0x00000001,
};

struct TMP_Text_SpecialCharacter {
    struct TMP_Character *character;
    struct TMP_FontAsset *fontAsset;
    struct Material *material;
    int32_t materialIndex;
};

struct TMP_Text__Fields {
    struct MaskableGraphic__Fields _;
    struct String *m_text;
    struct ITextPreprocessor *m_TextPreprocessor;
    bool m_isRightToLeft;
    struct TMP_FontAsset *m_fontAsset;
    struct TMP_FontAsset *m_currentFontAsset;
    bool m_isSDFShader;
    struct Material *m_sharedMaterial;
    struct Material *m_currentMaterial;
    struct MaterialReference__Array *m_materialReferences;
    struct Dictionary_2_System_Int32_System_Int32_ *m_materialReferenceIndexLookup;
    struct TMP_TextProcessingStack_1_MaterialReference_ m_materialReferenceStack;
    int32_t m_currentMaterialIndex;
    struct Material__Array *m_fontSharedMaterials;
    struct Material *m_fontMaterial;
    struct Material__Array *m_fontMaterials;
    bool m_isMaterialDirty;
    struct Color32 m_fontColor32;
    struct Color m_fontColor;
    struct Color32 m_underlineColor;
    struct Color32 m_strikethroughColor;
    bool m_enableVertexGradient;
    #if defined(_CPLUSPLUS_)
    ColorMode m_colorMode;
    #else
    int32_t m_colorMode;
    #endif
    struct VertexGradient m_fontColorGradient;
    struct TMP_ColorGradient *m_fontColorGradientPreset;
    struct TMP_SpriteAsset *m_spriteAsset;
    bool m_tintAllSprites;
    bool m_tintSprite;
    struct Color32 m_spriteColor;
    struct TMP_StyleSheet *m_StyleSheet;
    struct TMP_Style *m_TextStyle;
    int32_t m_TextStyleHashCode;
    bool m_overrideHtmlColors;
    struct Color32 m_faceColor;
    struct Color32 m_outlineColor;
    float m_outlineWidth;
    float m_fontSize;
    float m_currentFontSize;
    float m_fontSizeBase;
    struct TMP_TextProcessingStack_1_System_Single_ m_sizeStack;
    #if defined(_CPLUSPLUS_)
    FontWeight m_fontWeight;
    #else
    int32_t m_fontWeight;
    #endif
    #if defined(_CPLUSPLUS_)
    FontWeight m_FontWeightInternal;
    #else
    int32_t m_FontWeightInternal;
    #endif
    struct TMP_TextProcessingStack_1_FontWeight_ m_FontWeightStack;
    bool m_enableAutoSizing;
    float m_maxFontSize;
    float m_minFontSize;
    int32_t m_AutoSizeIterationCount;
    int32_t m_AutoSizeMaxIterationCount;
    bool m_IsAutoSizePointSizeSet;
    float m_fontSizeMin;
    float m_fontSizeMax;
    #if defined(_CPLUSPLUS_)
    FontStyles m_fontStyle;
    #else
    int32_t m_fontStyle;
    #endif
    #if defined(_CPLUSPLUS_)
    FontStyles m_FontStyleInternal;
    #else
    int32_t m_FontStyleInternal;
    #endif
    struct TMP_FontStyleStack m_fontStyleStack;
    bool m_isUsingBold;
    #if defined(_CPLUSPLUS_)
    HorizontalAlignmentOptions m_HorizontalAlignment;
    #else
    int32_t m_HorizontalAlignment;
    #endif
    #if defined(_CPLUSPLUS_)
    VerticalAlignmentOptions m_VerticalAlignment;
    #else
    int32_t m_VerticalAlignment;
    #endif
    #if defined(_CPLUSPLUS_)
    TextAlignmentOptions m_textAlignment;
    #else
    int32_t m_textAlignment;
    #endif
    #if defined(_CPLUSPLUS_)
    HorizontalAlignmentOptions m_lineJustification;
    #else
    int32_t m_lineJustification;
    #endif
    struct TMP_TextProcessingStack_1_HorizontalAlignmentOptions_ m_lineJustificationStack;
    struct Vector3__Array *m_textContainerLocalCorners;
    float m_characterSpacing;
    float m_cSpacing;
    float m_monoSpacing;
    float m_wordSpacing;
    float m_lineSpacing;
    float m_lineSpacingDelta;
    float m_lineHeight;
    bool m_IsDrivenLineSpacing;
    float m_lineSpacingMax;
    float m_paragraphSpacing;
    float m_charWidthMaxAdj;
    float m_charWidthAdjDelta;
    bool m_enableWordWrapping;
    bool m_isCharacterWrappingEnabled;
    bool m_isNonBreakingSpace;
    bool m_isIgnoringAlignment;
    float m_wordWrappingRatios;
    #if defined(_CPLUSPLUS_)
    TextOverflowModes m_overflowMode;
    #else
    int32_t m_overflowMode;
    #endif
    int32_t m_firstOverflowCharacterIndex;
    struct TMP_Text *m_linkedTextComponent;
    struct TMP_Text *parentLinkedComponent;
    bool m_isTextTruncated;
    bool m_enableKerning;
    float m_GlyphHorizontalAdvanceAdjustment;
    bool m_enableExtraPadding;
    bool checkPaddingRequired;
    bool m_isRichText;
    bool m_parseCtrlCharacters;
    bool m_isOverlay;
    bool m_isOrthographic;
    bool m_isCullingEnabled;
    bool m_isMaskingEnabled;
    bool isMaskUpdateRequired;
    bool m_ignoreCulling;
    #if defined(_CPLUSPLUS_)
    TextureMappingOptions m_horizontalMapping;
    #else
    int32_t m_horizontalMapping;
    #endif
    #if defined(_CPLUSPLUS_)
    TextureMappingOptions m_verticalMapping;
    #else
    int32_t m_verticalMapping;
    #endif
    float m_uvLineOffset;
    #if defined(_CPLUSPLUS_)
    TextRenderFlags m_renderMode;
    #else
    int32_t m_renderMode;
    #endif
    #if defined(_CPLUSPLUS_)
    VertexSortingOrder m_geometrySortingOrder;
    #else
    int32_t m_geometrySortingOrder;
    #endif
    bool m_IsTextObjectScaleStatic;
    bool m_VertexBufferAutoSizeReduction;
    int32_t m_firstVisibleCharacter;
    int32_t m_maxVisibleCharacters;
    int32_t m_maxVisibleWords;
    int32_t m_maxVisibleLines;
    bool m_useMaxVisibleDescender;
    int32_t m_pageToDisplay;
    bool m_isNewPage;
    struct Vector4 m_margin;
    float m_marginLeft;
    float m_marginRight;
    float m_marginWidth;
    float m_marginHeight;
    float m_width;
    struct TMP_TextInfo *m_textInfo;
    bool m_havePropertiesChanged;
    bool m_isUsingLegacyAnimationComponent;
    struct Transform *m_transform;
    struct RectTransform *m_rectTransform;
    struct Vector2 m_PreviousRectTransformSize;
    struct Vector2 m_PreviousPivotPosition;
    bool _autoSizeTextContainer_k__BackingField;
    bool m_autoSizeTextContainer;
    struct Mesh *m_mesh;
    bool m_isVolumetricText;
    struct Action_1_TMPro_TMP_TextInfo_ *OnPreRenderText;
    struct TMP_SpriteAnimator *m_spriteAnimator;
    float m_flexibleHeight;
    float m_flexibleWidth;
    float m_minWidth;
    float m_minHeight;
    float m_maxWidth;
    float m_maxHeight;
    struct LayoutElement *m_LayoutElement;
    float m_preferredWidth;
    float m_renderedWidth;
    bool m_isPreferredWidthDirty;
    float m_preferredHeight;
    float m_renderedHeight;
    bool m_isPreferredHeightDirty;
    bool m_isCalculatingPreferredValues;
    int32_t m_layoutPriority;
    bool m_isLayoutDirty;
    bool m_isAwake;
    bool m_isWaitingOnResourceLoad;
    bool m_isInputParsingRequired;
    #if defined(_CPLUSPLUS_)
    TMP_Text_TextInputSources m_inputSource;
    #else
    int32_t m_inputSource;
    #endif
    float m_fontScale;
    float m_fontScaleMultiplier;
    struct Char__Array *m_htmlTag;
    struct RichTextTagAttribute__Array *m_xmlAttribute;
    struct Single__Array *m_attributeParameterValues;
    float tag_LineIndent;
    float tag_Indent;
    struct TMP_TextProcessingStack_1_System_Single_ m_indentStack;
    bool tag_NoParsing;
    bool m_isParsingText;
    struct Matrix4x4 m_FXMatrix;
    bool m_isFXMatrixSet;
    struct TMP_Text_UnicodeChar__Array *m_InternalParsingBuffer;
    int32_t m_InternalParsingBufferSize;
    struct TMP_CharacterInfo__Array *m_internalCharacterInfo;
    struct Char__Array *m_input_CharArray;
    int32_t m_charArray_Length;
    int32_t m_totalCharacterCount;
    struct WordWrapState m_SavedWordWrapState;
    struct WordWrapState m_SavedLineState;
    struct WordWrapState m_SavedEllipsisState;
    struct WordWrapState m_SavedLastValidState;
    struct WordWrapState m_SavedSoftLineBreakState;
    struct TMP_TextProcessingStack_1_WordWrapState_ m_EllipsisInsertionCandidateStack;
    int32_t m_characterCount;
    int32_t m_firstCharacterOfLine;
    int32_t m_firstVisibleCharacterOfLine;
    int32_t m_lastCharacterOfLine;
    int32_t m_lastVisibleCharacterOfLine;
    int32_t m_lineNumber;
    int32_t m_lineVisibleCharacterCount;
    int32_t m_pageNumber;
    float m_PageAscender;
    float m_maxTextAscender;
    float m_maxCapHeight;
    float m_ElementAscender;
    float m_ElementDescender;
    float m_maxLineAscender;
    float m_maxLineDescender;
    float m_startOfLineAscender;
    float m_startOfLineDescender;
    float m_lineOffset;
    struct Extents m_meshExtents;
    struct Color32 m_htmlColor;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_colorStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_underlineColorStack;
    struct TMP_TextProcessingStack_1_UnityEngine_Color32_ m_strikethroughColorStack;
    struct TMP_TextProcessingStack_1_HighlightState_ m_HighlightStateStack;
    struct TMP_ColorGradient *m_colorGradientPreset;
    struct TMP_TextProcessingStack_1_TMP_ColorGradient_ m_colorGradientStack;
    bool m_colorGradientPresetIsTinted;
    float m_tabSpacing;
    float m_spacing;
    struct TMP_TextProcessingStack_1_System_Int32___Array *m_TextStyleStacks;
    int32_t m_TextStyleStackDepth;
    struct TMP_TextProcessingStack_1_System_Int32_ m_ItalicAngleStack;
    int32_t m_ItalicAngle;
    struct TMP_TextProcessingStack_1_System_Int32_ m_actionStack;
    float m_padding;
    float m_baselineOffset;
    struct TMP_TextProcessingStack_1_System_Single_ m_baselineOffsetStack;
    float m_xAdvance;
    #if defined(_CPLUSPLUS_)
    TMP_TextElementType m_textElementType;
    #else
    int32_t m_textElementType;
    #endif
    struct TMP_TextElement *m_cached_TextElement;
    struct TMP_Text_SpecialCharacter m_Ellipsis;
    struct TMP_Text_SpecialCharacter m_Underline;
    struct TMP_SpriteAsset *m_defaultSpriteAsset;
    struct TMP_SpriteAsset *m_currentSpriteAsset;
    int32_t m_spriteCount;
    int32_t m_spriteIndex;
    int32_t m_spriteAnimationID;
    bool m_ignoreActiveState;
    struct Decimal__Array *k_Power;
};

struct TMP_Text {
    struct TMP_Text__Class *klass;
    MonitorData *monitor;
    struct TMP_Text__Fields fields;
};

struct TextMeshProUGUI__Fields {
    struct TMP_Text__Fields _;
    bool m_hasFontAssetChanged;
    struct TMP_SubMeshUI__Array *m_subTextObjects;
    float m_previousLossyScaleY;
    struct Vector3__Array *m_RectTransformCorners;
    struct CanvasRenderer *m_canvasRenderer;
    struct Canvas *m_canvas;
    bool m_isFirstAllocation;
    int32_t m_max_characters;
    struct Material *m_baseMaterial;
    bool m_isScrollRegionSet;
    struct Vector4 m_maskOffset;
    struct Matrix4x4 m_EnvMapMatrix;
    bool m_isRegisteredForEvents;
    bool m_isRebuildingLayout;
    struct Coroutine *m_DelayedGraphicRebuild;
    struct Coroutine *m_DelayedMaterialRebuild;
    struct Rect m_ClipRect;
    bool m_ValidRect;
    struct Action_1_TMPro_TMP_TextInfo_ *OnPreRenderText;
};

struct TextMeshProUGUI {
    struct TextMeshProUGUI__Class *klass;
    MonitorData *monitor;
    struct TextMeshProUGUI__Fields fields;
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
    bool invulnerable;
    int32_t HNBJJFDLAKN;
    int32_t MMFKLFOFMEK;
    int32_t HFLFELILPIK;
    int32_t MGOMLEAAGEM;
    bool HCPADPBCLAE;
    int32_t ENPPCKKNLKM;
    int32_t max_hp;
    int32_t hp;
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
    struct String *guild_name;
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
    struct String *account_name;
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
    struct String *access_token;
    struct String *_CLAPFHFJMJK_k__BackingField;
    struct String *_FFIJPPMKHJC_k__BackingField;
    struct String *account_guid;
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

struct SettingsManager__Fields {
    struct MonoBehaviour__Fields _;
    bool JOFMCOFEDJP;
    struct OptionModel *PFGDIIAPHPE;
    struct OptionsList *IBNBAAHNHJD;
    struct OptionsList *CODLLBLMNME;
    struct List_1_DecaGames_RotMG_Managers_Options_OptionModel_ *OCJIOJEEDOJ;
    struct Dictionary_2_GCAPHHCPLGG_DecaGames_RotMG_Managers_Options_OptionModel_ *BPDNPDLKCEB;
    struct Settings *DKCDBOLECHM;
    struct Action *FPKFANEHKBA;
    struct CameraManager *KEIBIEADOBC;
};

struct SettingsManager {
    struct SettingsManager__Class *klass;
    MonitorData *monitor;
    struct SettingsManager__Fields fields;
};

enum class SettingsKeyCode : int32_t {
    Up = 0x00000000,
    Down = 0x00000001,
    Left = 0x00000002,
    Right = 0x00000003,
    RotateLeft = 0x00000004,
    RotateRight = 0x00000005,
    CenterPlayer = 0x00000006,
    ResetCameraAngle = 0x00000007,
    AutoFire = 0x00000008,
    UseWeaponAttack = 0x00000009,
    UseSpecialAbility = 0x0000000a,
    InteractBuy = 0x0000000b,
    EscapeToNexus = 0x0000000c,
    ShowMenu = 0x0000000d,
    SwitchTabs = 0x0000000e,
    ToggleHpBars = 0x0000000f,
    ToggleRealmQuests = 0x00000010,
    UseQuickslot1 = 0x00000011,
    UseQuickslot2 = 0x00000012,
    UseQuickslot3 = 0x00000013,
    UseInventorySlot1 = 0x00000014,
    UseInventorySlot2 = 0x00000015,
    UseInventorySlot3 = 0x00000016,
    UseInventorySlot4 = 0x00000017,
    UseInventorySlot5 = 0x00000018,
    UseInventorySlot6 = 0x00000019,
    UseInventorySlot7 = 0x0000001a,
    UseInventorySlot8 = 0x0000001b,
    UseBackpackSlot1 = 0x0000001c,
    UseBackpackSlot2 = 0x0000001d,
    UseBackpackSlot3 = 0x0000001e,
    UseBackpackSlot4 = 0x0000001f,
    UseBackpackSlot5 = 0x00000020,
    UseBackpackSlot6 = 0x00000021,
    UseBackpackSlot7 = 0x00000022,
    UseBackpackSlot8 = 0x00000023,
    MiniMapZoomIn = 0x00000024,
    MiniMapZoomOut = 0x00000025,
    CameraZoomIn = 0x00000026,
    CameraZoomOut = 0x00000027,
    UserInterfaceList = 0x00000028,
    PotionPurchases = 0x00000029,
    AllowCameraRotation = 0x0000002a,
    AllowMiniMapRotation = 0x0000002b,
    DoubleClickForGold = 0x0000002c,
    SwitchItemToFromBackpack = 0x0000002d,
    CameraFollowCursorMode = 0x0000002e,
    DefaultCameraAngle = 0x0000002f,
    ForceHighQualityChatText = 0x00000030,
    CenterOnPlayer = 0x00000031,
    ShowQuestsPortraits = 0x00000032,
    ShowTips = 0x00000033,
    DrawShadows = 0x00000034,
    DrawTextBubbles = 0x00000035,
    ShowTradeRequestPanel = 0x00000036,
    ShowGuildInvitePanel = 0x00000037,
    ShowTierLevel = 0x00000038,
    ExpandRealmQuests = 0x00000039,
    StarRequirement = 0x0000003a,
    FilterOffensiveLanguage = 0x0000003b,
    HideChatWindow = 0x0000003c,
    PlayerChat = 0x0000003d,
    WhisperChat = 0x0000003e,
    GuildChat = 0x0000003f,
    TradeRequests = 0x00000040,
    TradeRequestsFromFriendsOnly = 0x00000041,
    FriendsWhisperOnly = 0x00000042,
    ShowOptions = 0x00000043,
    WindowMode = 0x00000044,
    Resolutions = 0x00000045,
    Vsync = 0x00000046,
    RefreshRate = 0x00000047,
    ColorBlind = 0x00000048,
    ParticleEffect = 0x00000049,
    DisableParticleMaster = 0x0000004a,
    DisableEnemyParticles = 0x0000004b,
    DisablePlayersHitParticles = 0x0000004c,
    UserInterface = 0x0000004d,
    GUIMode = 0x0000004e,
    HpBarsMode = 0x0000004f,
    MpBarsMode = 0x00000050,
    AspectRatio = 0x00000051,
    ActivateChat = 0x00000052,
    StartChatCommand = 0x00000053,
    BeginTell = 0x00000054,
    BeginGuildChat = 0x00000055,
    ShowFriendList = 0x00000056,
    ScrollChatUp = 0x00000057,
    ScrollChatDown = 0x00000058,
    WeaponSounds = 0x00000059,
    NewMinimapColor = 0x0000005a,
    DisableAllyNotifications = 0x0000005b,
    EnableAllyDamage = 0x0000005c,
    EnableEnemyDamage = 0x0000005d,
    ShowFameGain = 0x0000005e,
    PotsToMax = 0x0000005f,
    AlwaysShowExp = 0x00000060,
    DisableAllyShoot = 0x00000061,
    CurseIndication = 0x00000062,
    HpColorsGUI = 0x00000063,
    CameraRotationSpeed = 0x00000064,
    ChatSize = 0x00000065,
    HpColorsPlayer = 0x00000066,
    InteractWithGameview = 0x00000067,
    ShowServers = 0x00000068,
    ShowLegends = 0x00000069,
    HpColorsQuest = 0x0000006a,
    ToggleQuestBars = 0x0000006b,
    ToggleConditionSize = 0x0000006c,
    TransparencyValue = 0x0000006d,
    TransparencyOnOtherPlayers = 0x0000006e,
    TransparencyOnOtherPets = 0x0000006f,
    TransparencyOnOtherProjectiles = 0x00000070,
    TransparencyRenderOnTop = 0x00000071,
    TransparencyAffectGuildMembers = 0x00000072,
    TransparencyAffectLockedPlayers = 0x00000073,
    DrawGUIShadows = 0x00000074,
    ControlSummon = 0x00000075,
    ToggleAllySummon = 0x00000076,
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

struct InputManager__Fields {
    struct MonoBehaviour__Fields _;
    bool isInteractHoldDown;
    struct MapViewService *OHLHEKBJMOO;
    struct CameraManager *KEIBIEADOBC;
    struct EquipmentManager *HCCCOFFFJJI;
    struct PopupManager *KHFEOFMPGGG;
    struct MiniMapManager *MPDIMLPFNBE;
    struct SettingsManager *BOJJBEJPDHF;
    bool CBHDGGBKGDF;
    bool CCEKJFLNIDO;
    bool ABDEALGBCPK;
    bool OFELALGANLE;
    bool CCFMBLCDBAB;
    struct Settings *DKCDBOLECHM;
    int32_t EDHIDLAPEJK;
    bool interactionKeyPressed;
    struct RaycastHit2D EMEKLCCAPFF;
    struct PlayerActionPanelHelper *KEKMGDLFCKG;
};

struct InputManager {
    struct InputManager__Class *klass;
    MonitorData *monitor;
    struct InputManager__Fields fields;
};

struct CharacterInfo__Fields {
    struct MonoBehaviour__Fields _;
    struct BaseButton *charactersButton;
    struct TextMeshProUGUI *accountName;
    struct GameObject *guildInfo;
    struct TextMeshProUGUI *guildNameLabel;
    struct Image *guildIcon;
    struct UIIconLoader *characterIconLoader;
    struct Image *starIcon;
    struct TextMeshProUGUI *starCountLabel;
    struct UIInfoTooltip *tooltipInfo;
    struct MapViewService *OHLHEKBJMOO;
    struct SocketManager_1 *HPIPJDMLKLK;
    struct GameObject *ui;
    struct UIItemShader *AAOFKKKOLBP;
};

struct CharacterInfo {
    struct CharacterInfo__Class *klass;
    MonitorData *monitor;
    struct CharacterInfo__Fields fields;
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
    struct NOKENPCHCDE *guild_info;
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