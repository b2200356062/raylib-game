
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;
Vector2 mousePosition = {0,0};
static Camera camera = {0};

int InitGameWindow(int width, int height, const char *title)
{
    InitWindow(width, height, "pencere");

    if(!IsWindowReady()){
        perror("window couldn't initialized!\n");
        return 1;
    }

    ToggleFullscreen();

    return 0;
}

void InitTitleScreen()
{
    framesCounter = 0;
    finishScreen = 0;

    camera.position = (Vector3){ 10.0f, 2.0f, 8.0f };
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void UpdateTitleScreen(void)
{
    
    Rectangle startButton = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 100, 150, 50};
    DrawRectangleLinesEx(startButton, 1.0f, BLACK);

    Rectangle optionsButton = {SCREEN_WIDTH / 2 - 50 , SCREEN_HEIGHT / 2 - 30, 150, 50};
    DrawRectangleLinesEx(optionsButton, 1.0f, BLACK);

    Rectangle exitButton = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 40, 150, 50};
    DrawRectangleLinesEx(exitButton, 1.0f, BLACK);
    
    Vector2 startTextPos =  {SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 100};
    DrawTextEx(font, "Start", startTextPos, font.baseSize*3.0f, 4, BLACK);
    
    Vector2 optionsTextPos =  {SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 30};
    DrawTextEx(font, "Options", optionsTextPos, font.baseSize*3.0f, 4, BLACK);

    Vector2 exitTextPos =  {SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 30};
    DrawTextEx(font, "Quit", exitTextPos, font.baseSize*3.0f, 4, BLACK);
    
    DrawText("MAIN MENU", 650, 100, font.baseSize*4.0f, BLACK);

    mousePosition = GetMousePosition();

    // gameplay
    if(CheckCollisionPointRec(mousePosition, startButton))
    {
        SetMouseCursor(4);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // play click sound
            finishScreen = 2;
            SetMouseCursor(0);
        }
    }
    // options
    else if(CheckCollisionPointRec(mousePosition, optionsButton))
    {
        SetMouseCursor(4);
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // play click sound
            finishScreen = 1;
            SetMouseCursor(0);
        }
    }
    // quit
    else if(CheckCollisionPointRec(mousePosition, exitButton))
    {
        SetMouseCursor(4);
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            ClearTitleScreen();
            return;
        }
    }
    else
    {
        SetMouseCursor(0);
    }

}

void DrawTitleScreen(void)
{

   
}

void ClearTitleScreen(void)
{
    gameRunning = false;
}

int FinishTitleScreen(void)
{
    return finishScreen;
}
