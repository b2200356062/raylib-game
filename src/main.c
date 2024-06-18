
#include "screens.h"

// Shared variables
Font font = {0};
Music music = {0};
Sound fx = {0};
GameScreen currentScreen = TITLE_SCREEN;
bool gameRunning = true;

// local varibles
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

// local functions
static void UpdateDrawFrame(void);  // Update and draw one frame
static void ChangeToScreen(GameScreen screen); // change to screen
static void TransitionToScreen(GameScreen screen); // request transition
static void UpdateTransition(void); // update transition effect
static void DrawTransition(void); // draw transition effect 

int main()
{
    // Initialization
    InitGameWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOWTITLE);

    // init audio

    font = LoadFont("resources/mecha.png");
    music = LoadMusicStream("resources/ambient.ogg");
    fx = LoadSound("resources/coin.wav");

    // set volume
    PlayMusicStream(music);
    SetMusicVolume(music, 100.0f);

    currentScreen = TITLE_SCREEN;

    InitTitleScreen();

    SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    
    // Main game loop
    while (!WindowShouldClose() && gameRunning == true)    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    switch (currentScreen)
    {
    case TITLE_SCREEN:
        ClearTitleScreen();
        break;
    case GAMEPLAY_SCREEN:
        ClearGameplayScreen();
        break;
    case OPTIONS_SCREEN:
        ClearOptionsScreen();
    default: 
        break;
    }

    // De-Initialization
    UnloadFont(font);
    UnloadMusicStream(music);

    // Close window and OpenGL context
    CloseWindow();                  

    return 0;
}


static void ChangeToScreen(GameScreen screen){

    switch (currentScreen)
    {
    case TITLE_SCREEN:
        ClearTitleScreen();
        break;
    case GAMEPLAY_SCREEN:
        ClearGameplayScreen();
    case OPTIONS_SCREEN:
        ClearOptionsScreen();
    default:
        break;
    }

    switch(screen)
    {
        case TITLE_SCREEN:
            InitTitleScreen();
            break;
        case GAMEPLAY_SCREEN:
            InitGameplayScreen();
            break;
        case OPTIONS_SCREEN:
            InitOptionsScreen();
        default:
            break;
    }

    currentScreen = screen;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case TITLE_SCREEN: ClearTitleScreen(); break;
                case OPTIONS_SCREEN: ClearOptionsScreen(); break;
                case GAMEPLAY_SCREEN: ClearGameplayScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                //case LOGO: InitLogoScreen(); break;
                case TITLE_SCREEN: InitTitleScreen(); break;
                case GAMEPLAY_SCREEN: InitGameplayScreen(); break;
                case OPTIONS_SCREEN: InitOptionsScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}


// Update and draw game frame
static void UpdateDrawFrame(void)
{
    // UPDATE MUSİC
    if(!onTransition){
        switch (currentScreen)
        {
        case TITLE_SCREEN:
            UpdateTitleScreen();

            if(FinishTitleScreen() == 2)
            {
                TransitionToScreen(GAMEPLAY_SCREEN);
            }
            else if(FinishTitleScreen() == 1)
            {
                TransitionToScreen(OPTIONS_SCREEN);
            }
            break;
        case OPTIONS_SCREEN:
            UpdateOptionsScreen();

            if (FinishOptionsScreen() == 0)
            {
                TransitionToScreen(TITLE_SCREEN);
            }
            break;
        case GAMEPLAY_SCREEN:
            UpdateGameplayScreen();

            if(FinishGameplayScreen() == 0)
            {
                TransitionToScreen(TITLE_SCREEN);
            }
            else if(FinishGameplayScreen() == 3)
            {
                TransitionToScreen(PAUSE_SCREEN);
            }

        // CASE ENDING
        default:
            break;
        }
    }
    else
    {
        UpdateTransition();
    }

    // Update


    // Draw
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case TITLE_SCREEN:
            DrawTitleScreen();
            break;
        case GAMEPLAY_SCREEN:
            DrawGameplayScreen();
            break;
        case OPTIONS_SCREEN:
            DrawOptionsScreen();
            break;
        default:
            break;
        }
        
        if(onTransition)
        {
            DrawTransition();
        }

        DrawFPS(SCREEN_WIDTH - 100, 20);

    EndDrawing();
}

static void TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}