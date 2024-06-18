#include "screens.h"

static Vector2 mousePosition = {0,0};
static int finishScreen = 1;
static int framesCounter = 0;
Rectangle backButton;
Vector2 backTextPos;

void InitOptionsScreen(void)
{
    finishScreen = 1;
    framesCounter = 0;

    backButton.x = 1000;
    backButton.y = 600;
    backButton.width = 80;
    backButton.height = 50;

    backTextPos.x = 1010;
    backTextPos.y = 610;
}

void UpdateOptionsScreen(void)
{
    mousePosition = GetMousePosition();

    if(CheckCollisionPointRec(mousePosition, backButton)){
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            finishScreen = 0;
        }
    }
    else
    {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    
}

void DrawOptionsScreen(void)
{
    DrawText("OPTIONS SCREEN", 450, 100, font.baseSize * 4.0f, BLACK);
    DrawRectangleLinesEx(backButton, 1.0f ,BLACK);
    DrawTextEx(font, "Back", backTextPos, font.baseSize * 2.0f, 4, BLACK);
}

void ClearOptionsScreen(void)
{
    
}

int FinishOptionsScreen(void)
{
    return finishScreen;
}