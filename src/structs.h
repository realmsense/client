#pragma once

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };

#include "other/reclass.h"
#include "other/offsets.h"

// Function typedefs

// il2cpp
typedef String* (__cdecl* _il2cpp_string_new)(const char* str);                                              // OFFSET_IL2CPP_STRING_NEW

// Assembly-CSharp.dll
typedef void(__cdecl* _SocketManager_Connect)(uintptr_t __this, String* address, int port, String* OUTGOING_KEY, String* INCOMING_KEY); // OFFSET_SOCKET_MANAGER_CONNECT
typedef void* (__cdecl* _CameraManagerUpdate)(uintptr_t cameraManager);                                     // OFFSET_CAMERAMANAGER_UPDATE
typedef void* (__cdecl* _UnityThread_Update)(uintptr_t __this);                                             // OFFSET_UNITYTHREAD_UPDATE
typedef void* (__cdecl* _PlayerUpdate)(Entity __this);                                                      // OFFSET_PLAYER_UPDATE
typedef void* (__cdecl* _EntityUpdate)(Entity entity);                                                      // OFFSET_ENTITY_UPDATE
typedef void* (__cdecl* _PetUpdate)(Entity pet, bool AMKOONDPFBD);                                          // OFFSET_PET_UPDATE

// mscorlib.dll
typedef uintptr_t(__cdecl* _System_GetType)(String* assemblyQualifiedName);                                 // OFFSET_SYSTEM_GET_TYPE

// UnityEngine.CoreModule.dll
typedef int(__cdecl* _Screen_GetFullscreenMode)(void);                                                      // OFFSET_SCREEN_GET_FULLSCREEN_MODE
typedef void(__cdecl* _Screen_SetFullscreenMode)(int mode);                                                 // OFFSET_SCREEN_SET_FULLSCREEN_MODE
typedef uintptr_t(__cdecl* _GetMainCamera)(void);                                                           // OFFSET_GET_MAINCAMERA
typedef void* (__cdecl* _Camera_set_orthographicSize)(uintptr_t UnityEngine_Camera, float amount);          // OFFSET_SET_ORTHOGRAPHICSIZE
typedef Vector3(__cdecl* _WorldToScreen)(uintptr_t camera, Vector3 position);                               // OFFSET_WORLD_TO_SCREEN
typedef Vector3(__cdecl* _ScreenToWorld)(uintptr_t camera, Vector3 position);                               // OFFSET_SCREEN_TO_WORLD
typedef bool(__cdecl* _Behaviour_get_enabled)(uintptr_t __this);                                            // OFFSET_BEHAVIOUR_GET_ENABLED
typedef void* (__cdecl* _Behaviour_set_enabled)(uintptr_t __this, bool value);                              // OFFSET_BEHAVIOUR_SET_ENABLED
typedef uintptr_t(__cdecl* _Component_GetGameObject)(uintptr_t __this);                                     // OFFSET_COMPONENT_GET_GAMEOBJECT
typedef uintptr_t(__cdecl* _Object_FindObjectOfType)(uintptr_t type);                                       // OFFSET_OBJECT_FIND_BY_TYPE
typedef String* (__cdecl* _Object_GetName)(uintptr_t object);                                               // OFFSET_OBJECT_GET_NAME
typedef uintptr_t(__cdecl* _GameObject_Find)(String* name);                                                 // OFFSET_GAMEOBJECT_FIND
typedef uintptr_t(__cdecl* _GameObject_GetTransform)(uintptr_t gameObject);                                 // OFFSET_GAMEOBJECT_GET_TRANSFORM
typedef bool(__cdecl* _GameObject_GetActive)(uintptr_t gameObject);                                         // OFFSET_GAMEOBJECT_GET_ACTIVE
typedef void(__cdecl* _GameObject_SetActive)(uintptr_t gameObject, bool value);                             // OFFSET_GAMEOBJECT_SET_ACTIVE
typedef uintptr_t(__cdecl* _Transform_GetChild)(uintptr_t transform, int index);                            // OFFSET_TRANSFORM_GET_CHILD
typedef uintptr_t(__cdecl* _Transform_Find)(uintptr_t transform, String* name);                             // OFFSET_TRANSFORM_FIND
typedef int(__cdecl* _Transform_get_childCount)(uintptr_t transform);                                       // OFFSET_TRANSFORM_GET_CHILD_COUNT
typedef Vector3(__cdecl* _Transform_get_position)(uintptr_t transform);                                     // OFFSET_TRANSFORM_GET_POSITION
typedef void(__cdecl* _Transform_set_position)(uintptr_t transform, Vector3 scale);                         // OFFSET_TRANSFORM_SET_POSITION
typedef Vector3(__cdecl* _Transform_get_localScale)(uintptr_t transform);                                   // OFFSET_TRANSFORM_GET_LOCAL_SCALE
typedef void(__cdecl* _Transform_set_localScale)(uintptr_t transform, Vector3 scale);                       // OFFSET_TRANSFORM_SET_LOCAL_SCALE
typedef void* (__cdecl* _TileSetColor)(uintptr_t __this, Color value);                                      // OFFSET_SPRITE_SET_COLOR
typedef void(__cdecl* _SetVsync)(int value);                                                                // OFFSET_SET_VSYNC
typedef void(__cdecl* _SetFpsTarget)(int value);                                                            // OFFSET_SET_FPS_TARGET 

// UnityEngine.InputLegacyModule.dll
typedef Vector3(__cdecl* _Input_GetMousePos)(uintptr_t __this);                                             // OFFSET_GET_MOUSEPOS

// Unity.TextMeshPro.dll
typedef void(__cdecl* _TMPText_SetText)(uintptr_t __this, String* text, bool syncTextInputBox);             // OFFSET_TMP_TEXT_SET_TEXT
typedef void(__cdecl* _TMP_Text_SetText_Internal)(uintptr_t __this, String* text, bool syncTextInputBox);   // OFFSET_TMP_TEXT_SET_TEXT_INTERNAL
typedef void* (__cdecl* _TMPText_SetColor)(uintptr_t __this, Color color);                                  // OFFSET_TMP_TEXT_SET_COLOR


// Global Structs - TODO: move to own module include file
enum class ModuleEvent
{
    MainLoop,
    UnityThread_Update,
    GetMousePos,
    Tile_SetColor,
    CameraManager_Update,
    SocketManager_Connect,
    TMP_SetText,
    Pet_Update
};
enum class ModuleCategory {
    VIEW,
    MOVEMENT,
    AUTO,
    OTHER
};
