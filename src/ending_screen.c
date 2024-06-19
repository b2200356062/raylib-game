#include "screens.h"

static int framesCount = 0;
static int finishScreen = 0;
static Vector2 mousePosition = {0,0};

void InitEndingScreen(void)
{
    framesCount = 0;

}

void UpdateEndingScreen(void)
{
    mousePosition = GetMousePosition();

}

void DrawEndingScreen(void)
{
    

}

void ClearEndingScreen(void)
{

}

int FinishEndingScreen(void)
{
    return finishScreen;
}
