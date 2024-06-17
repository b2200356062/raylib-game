#ifndef SCREENS_H
#define SCREENS_H

#include "stdio.h"
#include "raylib.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define WINDOWTITLE "window"

typedef enum GameScreen{
    
    UNKNOWN = -1, 

    TITLE_SCREEN = 0,

    OPTIONS_SCREEN = 1,

    GAMEPLAY_SCREEN = 2,

    PAUSE_SCREEN = 3,

    ENDING_SCREEN = 4,

}GameScreen;

extern bool gameRunning;
extern GameScreen currentScreen;
extern Font font;
extern Music music;

int InitGameWindow(int width, int height, const char* title);

void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void ClearTitleScreen(void);
int FinishTitleScreen(void);


void InitOptionsScreen(void);
void UpdatOptionsScreen(void);
void DrawOptionsScreen(void);
void ClearOptionsScreen(void);
int FinishOptionsScreen(void);


void InitGameplayScreen(void);
void UpdateGameplayScreen(void);
void DrawGameplayScreen(void);
void ClearGameplayScreen(void);
int FinishGameplayScreen(void);


int PauseScreen(void);



#endif