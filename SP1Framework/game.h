#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

#include "EnemyHelpers.h"
#include "PlayerHelpers.h"
#include "RenderMapHelpers.h"
#include "RenderPersonHelpers.h"
#include "PlayerVisionHelpers.h"
#include "EnemyVisionHelpers.h"
#include "RenderMessageHelpers.h"
#include "RenderInventoryHelpers.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

void init        ( void );      // initialize your variables, allocate memory, etc
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait(); 
void loadingScreenWait1();
void loadingScreenWait2();
void loadingScreenWait3();
void loadingScreenWait4();
void loadingScreenWait5(); // waits for time to pass in splash screen
void renderLoadingScreen1();
void renderLoadingScreen2();
void renderLoadingScreen3();
void renderLoadingScreen4();
void renderLoadingScreen5();
void loseScreenWait();
void winScreenWait();

void gameplay();            // gameplay logic

void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit

void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderLoseScreen();
void renderWinScreen();

void renderGame(Player*);   // renders the game stuff

void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void checkGamestate();

#endif // _GAME_H