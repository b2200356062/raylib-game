
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;
static Camera camera = {0};
Vector3 cubePosition = { 0 };


// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 2;
    camera.position = (Vector3){ 10.0f, 2.0f, 8.0f };
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.f;
    camera.projection = CAMERA_PERSPECTIVE;
    HideCursor();
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 0;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{

    UpdateCamera(&camera, CAMERA_FIRST_PERSON);

    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);

    BeginMode3D(camera);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);

    EndMode3D();
}

// Gameplay Screen Unload logic
void ClearGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    ShowCursor();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    
    return finishScreen;
}