#pragma once

// il2cpp
#define OFFSET_IL2CPP_STRING_NEW                 0xc0d70        // Il2CppString * il2cpp_string_new(char * str)

// Assembly-CSharp.dll
#define OFFSET_SOCKET_MANAGER_CONNECT            0x1b68a50      // void SocketManager_1_Connect(SocketManager_1 * this, String * FAEOEJAKJCD, int32_t NDDFJGMCEAI, String * HJLKEICEIGB, String * OJPAJEEOJMC, MethodInfo * method)
#define OFFSET_CAMERAMANAGER_UPDATE              0x16230e0      // void CameraManager_Update(CameraManager * this, MethodInfo * method)
#define OFFSET_SHOW_FLOATING_TEXT                0x1a87870      // void MapObjectUIManager_ShowFloatingText_1(MapObjectUIManager * this, CLEPBEMBHAJ__Enum DBMPDNFHFNL, String * OBEFKMANGCK, Nullable_1_UnityEngine_Color32_ HNDHLEHECGE, float MPNAHCHFHMD, MethodInfo * method)
#define OFFSET_UNITYTHREAD_UPDATE                0x241ccf0      // void UnityThread_Update(UnityThread * this, MethodInfo * method)

// TODO: use FindObjectsByType
#define OFFSET_PLAYER_UPDATE                    0x17528a0    // JFNHHLNJJKP.JJCAKPHMLKD - Random method that runs every tick to get player
#define OFFSET_ENTITY_UPDATE                    0x21ca3a0    // COEDKELBKMI.(HOGFGOPEKAE or FFHEDOAINJH) - Random method to get enemy 
#define OFFSET_PET_UPDATE                       0x0    // DAFEAHGLBGL.AOOJCNNGNGI - random method that runs every tick to get pets


// mscorlib.dll
#define OFFSET_SYSTEM_GET_TYPE                   0x1355b30      // Type * Type_GetType_2(String * typeName, MethodInfo * method)

// UnityEngine.CoreModule.dll
#define OFFSET_SCREEN_GET_FULLSCREEN_MODE        0xd436a0       // FullScreenMode__Enum Screen_get_fullScreenMode(MethodInfo * method)
#define OFFSET_SCREEN_SET_FULLSCREEN_MODE        0xd43790       // void Screen_set_fullScreenMode(FullScreenMode__Enum value, MethodInfo * method)
#define OFFSET_GET_MAINCAMERA                    0xe0fc10       // Camera * Camera_get_main(MethodInfo * method)
#define OFFSET_SET_ORTHOGRAPHICSIZE              0xe10430       // void Camera_set_orthographicSize(Camera * this, float value, MethodInfo * method)
#define OFFSET_WORLD_TO_SCREEN                   0xe0f640       // Vector3 Camera_WorldToScreenPoint_1(Camera * this, Vector3 position, MethodInfo * method)
#define OFFSET_SCREEN_TO_WORLD                   0xe0f230       // Vector3 Camera_ScreenToWorldPoint_1(Camera * this, Vector3 position, MethodInfo * method)
#define OFFSET_BEHAVIOUR_GET_ENABLED             0xe0d570       // bool Behaviour_get_enabled(Behaviour * this, MethodInfo * method)
#define OFFSET_BEHAVIOUR_SET_ENABLED             0xe0d5f0       // void Behaviour_set_enabled(Behaviour * this, bool value, MethodInfo * method)
#define OFFSET_COMPONENT_GET_GAMEOBJECT          0xe11ef0       // GameObject * Component_1_get_gameObject(Component_1 * this, MethodInfo * method)
#define OFFSET_OBJECT_FIND_BY_TYPE               0xec2080       // Object_1 * Object_1_FindObjectOfType(Type * type, MethodInfo * method)
#define OFFSET_OBJECT_GET_NAME                   0xec2d20       // String * Object_1_get_name(Object_1 * this, MethodInfo * method)
#define OFFSET_OBJECT_GET_NAME                   0xec2d20       // String * Object_1_get_name(Object_1 * this, MethodInfo * method)
#define OFFSET_GAMEOBJECT_FIND                   0xe160c0       // GameObject * GameObject_Find(String * name, MethodInfo * method)
#define OFFSET_GAMEOBJECT_GET_TRANSFORM          0xe16870       // Transform * GameObject_get_transform(GameObject * this, MethodInfo * method)
#define OFFSET_GAMEOBJECT_GET_ACTIVE             0xe16750       // bool GameObject_get_activeSelf(GameObject * this, MethodInfo * method)
#define OFFSET_GAMEOBJECT_SET_ACTIVE             0xe16450       // void GameObject_SetActive(GameObject * this, bool value, MethodInfo * method)
#define OFFSET_TRANSFORM_GET_CHILD               0xd4d8f0       // Transform * Transform_GetChild(Transform * this, int32_t index, MethodInfo * method)
#define OFFSET_TRANSFORM_FIND                    0xd4d850       // Transform * Transform_Find(Transform * this, String * n, MethodInfo * method)
#define OFFSET_TRANSFORM_GET_CHILD_COUNT         0xd4e6c0       // int32_t Transform_get_childCount(Transform * this, MethodInfo * method)
#define OFFSET_TRANSFORM_GET_POSITION            0xd4ecb0       // Vector3 Transform_get_position(Transform * this, MethodInfo * method)
#define OFFSET_TRANSFORM_SET_POSITION            0xd4f500       // void Transform_set_position(Transform * this, Vector3 value, MethodInfo * method)
#define OFFSET_TRANSFORM_GET_LOCAL_SCALE         0xd4eac0       // Vector3 Transform_get_localScale(Transform * this, MethodInfo * method)
#define OFFSET_TRANSFORM_SET_LOCAL_SCALE         0xd4f3b0       // void Transform_set_localScale(Transform * this, Vector3 value, MethodInfo * method)
#define OFFSET_SPRITE_SET_COLOR                  0xd46290       // void SpriteRenderer_set_color(SpriteRenderer * this, Color value, MethodInfo * method)
#define OFFSET_SET_VSYNC                         0xec97d0       // void QualitySettings_set_vSyncCount(int32_t value, MethodInfo * method)
#define OFFSET_SET_FPS_TARGET                    0xe0b6e0       // void Application_set_targetFrameRate(int32_t value, MethodInfo * method)

// UnityEngine.InputLegacyModule.dll
#define OFFSET_GET_MOUSEPOS                      0x15df350      // Vector3 Input_get_mousePosition(MethodInfo * method)
#define OFFSET_GET_KEY_DOWN                      0x15defb0      // bool Input_GetKeyDown(KeyCode__Enum key, MethodInfo * method)
#define OFFSET_GET_KEY                           0x15deff0      // bool Input_GetKey(KeyCode__Enum key, MethodInfo * method)

// Unity.TextMeshPro.dll
#define OFFSET_TMP_TEXT_SET_TEXT                 0x2e9f30       // void TMP_Text_SetText(TMP_Text * this, String * text, bool syncTextInputBox, MethodInfo * method)
#define OFFSET_TMP_TEXT_SET_TEXT_INTERNAL        0x2f5040       // void TMP_Text_set_text(TMP_Text * this, String * value, MethodInfo * method)
#define OFFSET_TMP_TEXT_SET_COLOR                0x2f3eb0       // void TMP_Text_set_color(TMP_Text * this, Color value, MethodInfo * method)
