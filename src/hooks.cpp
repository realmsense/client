#include "pch.h"
#include "globals.h"
#include "minhook/include/MinHook.h"

typedef void* (__cdecl* _UnityThread_Update)(uintptr_t __this);
_UnityThread_Update Original_UnityThread_Update = nullptr;
void* Detour_UnityThread_Update(uintptr_t __this)
{
    if (g_bNoclip) {
        return nullptr;
    }
    return Original_UnityThread_Update(__this);
}

typedef void* (__cdecl* _GetPlayer)(Entity __this);
_GetPlayer Original_GetPlayer = nullptr;
void* Detour_GetPlayer(Entity player)
{
    if (&player != g_pPlayer)
    {
        // changed map, clear stuff
        g_aEnemyList.clear();
    }

    g_pPlayer = &player;

    //std::cout << std::hex << *(uintptr_t*)&player << std::endl;
    return Original_GetPlayer(player);
}

typedef void* (__cdecl* _GetEntity)(Entity entity);
_GetEntity Original_GetEntity = nullptr;
void* Detour_GetEntity(Entity entity)
{
    // ignore if this is our player
    if (&entity == g_pPlayer)
    {
        return Detour_GetEntity(entity);
    }

    // TODO: we should probably be using one std::map?
    // to store one large entity list but the enum EntityType

    // Weird naming by DECA, but "Character" is really an enemy
    if (entity.entityType == EntityType::Character)
    {
        g_aEnemyList.insert(&entity);
    }

    return Original_GetEntity(entity);
}

typedef void* (__cdecl* _TileSetColor)(uintptr_t __this, Color value);
_TileSetColor Original_Tile_SetColor = nullptr;
void* Detour_Tile_SetColor(uintptr_t __this, Color value)
{
    // don't change the tile color if it is being darkened
    if (g_bDisableFog
        && (value.r != 1 || value.g != 1 || value.b != 1 || value.a != 1)
        ) {
        return nullptr;
    }

    return Original_Tile_SetColor(__this, value);
}

typedef void* (__cdecl* _CameraManagerUpdate)(uintptr_t cameraManager);
_CameraManagerUpdate Original_CameraManager_Update = nullptr;
void* Detour_CameraManager_Update(uintptr_t cameraManager)
{
    g_pCameraManager = cameraManager;

    uintptr_t cameraPerspectiveEditor = *(uintptr_t*)(g_pCameraManager + 0x48); // OOJJDIANIBF
    g_bDisablePerspectiveEditor = Behaviour_get_enabled(cameraPerspectiveEditor);

    return Original_CameraManager_Update(cameraManager);
}

typedef void* (__cdecl* _Add_Dynamic_Object)(uintptr_t __this, float x, float y, Color color, uintptr_t entity);
_Add_Dynamic_Object Original_Add_Dynamic_Object = nullptr;
void* Detour_Add_Dynamic_Object(uintptr_t __this, float x, float y, Color color, uintptr_t entity)
{
    if (entity)
    {
        std::cout << x << "," << y << std::endl;
        std::cout << color.r << "," << color.g << "," << color.b << std::endl;
        std::cout << std::hex << entity << std::endl;
        std::cout << std::endl;
    }

    return Original_Add_Dynamic_Object(__this, x, y, color, entity);
}

typedef Vector3 (__cdecl* _Input_GetMousePos)(uintptr_t __this);
_Input_GetMousePos Original_Input_GetMousePos = nullptr;
Vector3 Detour_Input_GetMousePos(uintptr_t __this)
{
    Vector3 mousePos = Original_Input_GetMousePos(__this);

    if (!g_bAutoAim || !g_pPlayer || !g_pMainCamera)
    {
        return mousePos;
    }

    Entity* chosenEnemy = nullptr;
    for (auto& enemy : g_aEnemyList)
    {
        if (chosenEnemy == nullptr)
        {
            chosenEnemy = enemy;
            continue;
        }

        if (g_AutoAimTarget == AutoAimTarget::ClosestPos)
        {
            float chosenDistance = CalculateDistance(chosenEnemy->pos, g_pPlayer->pos);
            float currentDistance = CalculateDistance(enemy->pos, g_pPlayer->pos);
            if (currentDistance < chosenDistance)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (g_AutoAimTarget == AutoAimTarget::ClosestMouse)
        {
            Vector3 mouseWorldPos3 = ScreenToWorld(g_pMainCamera, mousePos);
            Vector2 mouseWorldPos = { mouseWorldPos3.x, mouseWorldPos3.y * -1 };
            float chosenDistance = CalculateDistance(chosenEnemy->pos, mouseWorldPos);
            float currentdistance = CalculateDistance(enemy->pos, mouseWorldPos);
            if (currentdistance < chosenDistance)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (g_AutoAimTarget == AutoAimTarget::HighestDef)
        {
            // TODO: what happens if the enemy is armor broken?
            int chosenDef = chosenEnemy->defense;
            int currentDefense = enemy->defense;
            if (currentDefense > chosenDef)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else if (g_AutoAimTarget == AutoAimTarget::HighestMaxHP)
        {
            int chosenHP = chosenEnemy->maxHP;
            int currentHP = enemy->maxHP;
            if (chosenHP > currentHP)
            {
                chosenEnemy = enemy;
                continue;
            }
        }
        else
        {
            chosenEnemy = enemy;
            break;
        }
    }
    
    if (chosenEnemy)
    {
        Vector3 enemyPos = { chosenEnemy->pos.x, (chosenEnemy->pos.y) * -1, 0.0f };
        Vector3 enemyScreenPos = WorldToScreen(g_pMainCamera, enemyPos);
        mousePos = enemyScreenPos;
    }

    return mousePos;
}

typedef void*(__cdecl* _SocketManager_SendMessage)(uintptr_t __this, uintptr_t packet);
_SocketManager_SendMessage Original_SocketManager_SendMessage = nullptr;
void* Detour_SocketManager_SendMessage(uintptr_t __this, uintptr_t packet)
{
    int packetId = *(int*)(packet + 0x18);
    if (g_bNoclip
        && packetId == 42 // move
    ) {
        return nullptr;
    }

    return Original_SocketManager_SendMessage(__this, packet);
}


typedef void* (__cdecl* _GetPlayerList)(NBJLMDOACBC __this, int EGHLCCGKEDH);
_GetPlayerList Original_GetPlayerList = nullptr;
void* Detour_GetPlayerList(NBJLMDOACBC __this, int EGHLCCGKEDH)
{
    g_pNBJLMDOACBC = &__this;
    return Original_GetPlayerList(__this, EGHLCCGKEDH);
}

bool InitHooks()
{
    MH_Initialize();

    // TODO: Use sig scan here
    void* UnityThread_Update = (void*)(g_pBaseAddress + OFFSET_UNITYTHREAD_UPDATE);
    if (MH_CreateHook(UnityThread_Update, Detour_UnityThread_Update, reinterpret_cast<LPVOID*>(&Original_UnityThread_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour UnityThread_Update", "RotMGInternal", MB_OK);
        return false;
    }

    void* GetPlayer = (void*)(g_pBaseAddress + OFFSET_GET_PLAYER);
    if (MH_CreateHook(GetPlayer, Detour_GetPlayer, reinterpret_cast<LPVOID*>(&Original_GetPlayer)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPlayer", "RotMGInternal", MB_OK);
        return false;
    }

    void* GetEntity = (void*)(g_pBaseAddress + OFFSET_GET_ENEMY);
    if (MH_CreateHook(GetEntity, Detour_GetEntity, reinterpret_cast<LPVOID*>(&Original_GetEntity)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetEntity", "RotMG Internal", MB_OK);
        return 1;
    }

    void* SpriteRenderer_SetColor = (void*)(g_pBaseAddress + OFFSET_SPRITE_SET_COLOR);
    if (MH_CreateHook(SpriteRenderer_SetColor, Detour_Tile_SetColor, reinterpret_cast<LPVOID*>(&Original_Tile_SetColor)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SpriteRenderer_SetColor", "RotMGInternal", MB_OK);
        return false;
    }

    void* CameraManager_Update = (void*)(g_pBaseAddress + OFFSET_CAMERAMANAGER_UPDATE);
    if (MH_CreateHook(CameraManager_Update, Detour_CameraManager_Update, reinterpret_cast<LPVOID*>(&Original_CameraManager_Update)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour CameraManager_Update", "RotMG Internal", MB_OK);
        return 1;
    }

    void* Input_GetMousePos = (void*)(g_pBaseAddress + OFFSET_GET_MOUSEPOS);
    if (MH_CreateHook(Input_GetMousePos, Detour_Input_GetMousePos, reinterpret_cast<LPVOID*>(&Original_Input_GetMousePos)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour Input_GetMousePos", "RotMG Internal", MB_OK);
        return 1;
    }

    void* SocketManager_SendMessage = (void*)(g_pBaseAddress + OFFSET_SOCKET_SENDMESSAGE);
    if (MH_CreateHook(SocketManager_SendMessage, Detour_SocketManager_SendMessage, reinterpret_cast<LPVOID*>(&Original_SocketManager_SendMessage)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour SocketManager_SendMessage", "RotMG Internal", MB_OK);
        return 1;
    }


    void* GetPlayerList = (void*)(g_pBaseAddress + OFFSET_GET_PLAYER_LIST);
    if (MH_CreateHook(GetPlayerList, Detour_GetPlayerList, reinterpret_cast<LPVOID*>(&Original_GetPlayerList)) != MH_OK)
    {
        MessageBoxA(NULL, "Failed to Detour GetPlayerList", "RotMG Internal", MB_OK);
        return 1;
    }

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MessageBoxA(NULL, "Faild To Activate MinHook Hooks", "RotMG Internal", MB_OK);
        return false;
    }

    return true;
}

void RemoveHooks()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
