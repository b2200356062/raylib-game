
#include "screens.h"

static int framesCounter = 0;
static int finishScreen = 0;
static Vector2 mousePosition = {0,0};
static Rectangle startButton, optionsButton, exitButton;
static Vector2 startTextPos, optionsTextPos, exitTextPos;

int InitGameWindow(int width, int height, const char *title)
{
    InitWindow(width, height, "pencere");

    if(!IsWindowReady()){
        perror("window couldn't initialized!\n");
        return 1;
    }

    //ToggleFullscreen();

    return 0;
}

void InitTitleScreen()
{
    framesCounter = 0;
    finishScreen = 0;

    startButton.x = SCREEN_WIDTH / 2 - 50;
    startButton.y= SCREEN_HEIGHT / 2 - 100;
    startButton.width = 150;
    startButton.height = 50;

    optionsButton.x = SCREEN_WIDTH / 2 - 50;
    optionsButton.y = SCREEN_HEIGHT / 2 - 30;
    optionsButton.width = 150;
    optionsButton.height = 50;

    exitButton.x = SCREEN_WIDTH / 2 - 50;
    exitButton.y = SCREEN_HEIGHT / 2 + 40;
    exitButton.width =  150;
    exitButton.height = 50;

    startTextPos.x = SCREEN_WIDTH / 2 - 10;
    startTextPos.y = SCREEN_HEIGHT / 2 - 100;

    optionsTextPos.x = SCREEN_WIDTH / 2 - 30, 
    optionsTextPos.y = SCREEN_HEIGHT / 2 - 30;

    exitTextPos.x = SCREEN_WIDTH / 2 - 10;
    exitTextPos.y = SCREEN_HEIGHT / 2 + 40;
}


void UpdateTitleScreen(void)
{
    mousePosition = GetMousePosition();

    if(IsKeyPressed(KEY_ENTER))
    {
        finishScreen = 2;
    }

    // gameplay
    if(CheckCollisionPointRec(mousePosition, startButton))
    {
        SetMouseCursor(4);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // play click sound
            finishScreen = 2;
           
        }
    }
    // options
    else if(CheckCollisionPointRec(mousePosition, optionsButton))
    {
        SetMouseCursor(4);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // play click sound
            finishScreen = 1;
            
        }
    }
    // quit
    else if(CheckCollisionPointRec(mousePosition, exitButton))
    {
        SetMouseCursor(4);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            finishScreen = 4;
            gameRunning = false;
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
    DrawRectangleLinesEx(startButton, 1.0f, BLACK);
    DrawRectangleLinesEx(optionsButton, 1.0f, BLACK);
    DrawRectangleLinesEx(exitButton, 1.0f, BLACK);

    DrawTextEx(font, "Start", startTextPos, font.baseSize*3.0f, 4, BLACK);
    DrawTextEx(font, "Options", optionsTextPos, font.baseSize*3.0f, 4, BLACK);
    DrawTextEx(font, "Quit", exitTextPos, font.baseSize*3.0f, 4, BLACK);
    
    DrawText("MAIN MENU", 650, 100, font.baseSize*4.0f, BLACK);
}

void ClearTitleScreen(void)
{

}

int FinishTitleScreen(void)
{
    return finishScreen;
}
