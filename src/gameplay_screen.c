
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;
static Camera camera = { 0 };
//static Vector3 cubePosition = { 0 };
static Vector3 mapPosition = { 0 };
static Ray player = { 0 };
//static RayCollision playerCollision = { 0 };

static int map[8][8] = {
    1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,1,1,1,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,1,1,1,1,1
};

Vector3 realToMapPosition(Vector3 playerPos){
    
    mapPosition.x = playerPos.x / 20;
    mapPosition.y = playerPos.y / 20;
    mapPosition.z = 1.0f;

    return mapPosition;
}

void DrawMap()
{
    Vector3 wallpositions = {0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(map[i][j] == 1)
            {
                wallpositions.x = 20.0f * i;
                wallpositions.z = 20.0f * j;
                wallpositions.y = 10.0f;
                DrawCubeV(wallpositions, (Vector3){20.0f, 20, 20}, GRAY);
            }
            else
            {
                continue;
            }
        }
    }
}

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{

    // Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 2;

    camera.position = (Vector3){ 25.0f, 10.0f, 32.0f };
    camera.target = (Vector3){0.0f, 10.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.f;
    camera.projection = CAMERA_PERSPECTIVE;
    

    player.position = camera.position;
    player.direction = camera.target;

    DisableCursor();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 0;
    }

    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
  
    mapPosition = realToMapPosition(player.position);

    //printf("map position x: %f, y: %f\n", mapPosition.x, mapPosition.y);
    //DrawText(, , );
    //printf("pos x: %f, pos y: %f, pos z: %f\n", player.position.x, player.position.y, player.position.z);


    player.position = camera.position;
    player.direction = camera.target;

    //printf("player position x: %f, y: %f\n", playerPosition.x, playerPosition.y);
    //camera.target = oldCamDirection;
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
   

    // TODO: Draw GAMEPLAY screen here!
    //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };


    BeginMode3D(camera);
        DrawMap();
        DrawGrid(100, 10);
        // DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        // DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
    EndMode3D();

    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText(TextFormat("ray x: %f, ray y: %f, ray z: %f\n", player.direction.x, player.direction.y, player.direction.z), 100, 100, font.baseSize * 2.0f, BLACK);
    DrawText(TextFormat("mouse posx: %f, posy: %f", GetMousePosition().x, GetMousePosition().y), 1400, 300, font.baseSize * 3.0f, BLACK);
}

// Gameplay Screen Unload logic
void ClearGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    EnableCursor();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    
    return finishScreen;
}