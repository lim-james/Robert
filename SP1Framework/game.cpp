// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <thread>


std::string splashScreen[7][15] =
{
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"- - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"/ - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"- - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / / / / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / - - - - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - / - - - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - - / - - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -",
		"/ - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - / / / / / - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - /",
		"- - - / - - - / - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / / / / - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / - - - - - / - - - / - - / / / / - - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - / - - - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - - / - - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - -",
		"/ - - / - - - / - - / - - - / - - / - - - / - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / / / / / - - / / / / / - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - /",
		"- - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / / / / - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - -",
		"- - - / / - - - - - / - - - / - - / / / / - - - / / / / / - - - - - - - - - - - - - - - - -",
		"- - - / - / - - - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - -",
		"- - - / - - / - - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - -",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - / / / / / - - / / / / / - - / / / / / - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - - - - - - - - /",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - - - - - - /",
		"- - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - - - - - - -",
		"- - - / / / / / - - / - - - / - - / - - - / - - / - - - - - - / / / / / - - - - - - - - - -",
		"- - - / / - - - - - / - - - / - - / / / / - - - / / / / / - - / / - - - - - - - - - - - - -",
		"- - - / - / - - - - / - - - / - - / - - - / - - / - - - - - - / - / - - - - - - - - - - - -",
		"- - - / - - / - - - / - - - / - - / - - - / - - / - - - - - - / - - / - - - - - - - - - - -",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - - - - - - /",
		"/ - - / - - - / - - / / / / / - - / / / / / - - / / / / / - - / - - - / - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - /",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - / - - - - /",
		"- - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - / - - - - -",
		"- - - / / / / / - - / - - - / - - / - - - / - - / - - - - - - / / / / / - - - - / - - - - -",
		"- - - / / - - - - - / - - - / - - / / / / - - - / / / / / - - / / - - - - - - - / - - - - -",
		"- - - / - / - - - - / - - - / - - / - - - / - - / - - - - - - / - / - - - - - - / - - - - -",
		"- - - / - - / - - - / - - - / - - / - - - / - - / - - - - - - / - - / - - - - - / - - - - -",
		"/ - - / - - - / - - / - - - / - - / - - - / - - / - - - - - - / - - - / - - - - / - - - - /",
		"/ - - / - - - / - - / / / / / - - / / / / / - - / / / / / - - / - - - / - - - - / - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
};

std::string loseScreen[7][15] =
{
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - - - - - - - - / - - - - - - / / / / / - - / / / / / - - / / / / / - - /",
		"/ - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - / - - - / - - / - - - - - - /",
		"- - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - / - - - - - - / - - - - - - -",
		"- - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - / - - - - - - / - - - - - - -",
		"- - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - / / / / / - - / / / / / - - -",
		"- - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - - - - - / - - / - - - - - - -",
		"- - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - - - - - / - - / - - - - - - -",
		"/ - - / - - - / - - - - - - - - - / - - - - - - / - - - / - - / - - - / - - / - - - - - - /",
		"/ - - / / / / / - - - - - - - - - / / / / / - - / / / / / - - / / / / / - - / / / / / - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
};

std::string winScreen[7][15] =
{
	{
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - / - - - / - - - - - - - - - / - / - / - - / / / / / - - / / / / / - - - - / - - - - /",
		"/ - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - /",
		"- - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - -",
		"- - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - -",
		"- - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - -",
		"- - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - -",
		"- - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - / - - - - -",
		"/ - - / - - - / - - - - - - - - - / - / - / - - - - / - - - - / - - - / - - - - - - - - - /",
		"/ - - / / / / / - - - - - - - - - / / / / / - - / / / / / - - / - - - / - - - - / - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - /",
		"/ / / / / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / / / / /",
	},
};
//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point outputfi
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    // sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 25, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
	if (GetConsoleWindow() != GetForegroundWindow()) return;
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
		case S_LOADINGSCREEN1: loadingScreenWait1();
			break;
		case S_LOADINGSCREEN2: loadingScreenWait2();
			break;
		case S_LOADINGSCREEN3: loadingScreenWait3();
			break;
		case S_LOADINGSCREEN4: loadingScreenWait4();
			break;
		case S_LOADINGSCREEN5: loadingScreenWait5();
			break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_LOSESCREEN: loseScreenWait();
			break;
		case S_WINSCREEN: winScreenWait();
			break;
    }
}

//--------------------------------------------------------------+
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
		case S_LOADINGSCREEN1: renderLoadingScreen1();
			break;
		case S_LOADINGSCREEN2: renderLoadingScreen2();
			break;
		case S_LOADINGSCREEN3: renderLoadingScreen3();
			break;
		case S_LOADINGSCREEN4: renderLoadingScreen4();
			break;
		case S_LOADINGSCREEN5: renderLoadingScreen5();
			break;
		case S_GAME:
			renderGame(player1());
			renderGame(player2());
            break;
		case S_LOSESCREEN: renderLoseScreen();
			break;
		case S_WINSCREEN: renderWinScreen();
			break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_abKeyPressed[K_SPACE]) // wait for space to switch to game mode, else do nothing
	{
		setLevel(currentLevel);
		g_eGameState = S_LOADINGSCREEN1;
	}
}

void loadingScreenWait1()
{
	Sleep(1200);
	g_eGameState = S_LOADINGSCREEN2;
}

void loadingScreenWait2()
{
	Sleep(1200);
	g_eGameState = S_LOADINGSCREEN3;
}

void loadingScreenWait3()
{
	Sleep(1200);
	g_eGameState = S_LOADINGSCREEN4;
}
void loadingScreenWait4()
{
	Sleep(1200);
	g_eGameState = S_LOADINGSCREEN5;
}
void loadingScreenWait5()
{
	Sleep(2000);
	setLevel(currentLevel);
	g_eGameState = S_GAME;
}

void loseScreenWait()
{
	if (g_abKeyPressed[K_SPACE]) // wait for space to switch to game mode, else do nothing
	{
		setLevel(currentLevel);
		g_eGameState = S_GAME;
	}
}

void winScreenWait()
{
	if (g_abKeyPressed[K_SPACE]) // wait for space to switch to game mode, else do nothing
	{
		setLevel(currentLevel);
		g_eGameState = S_GAME;
	}
}

void gameplay()            // gameplay logic
{
	refreshEnemies();
	playerKeyEvents();  // moves the character, collision detection, physics, etc
                        // sound can be played here too.
	checkGamestate();
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
	for (int p = 0; p < 2; ++p)
	{
		unsigned int curr = players()[p]->currentStorey;
		for (unsigned int i = 0; i < numberOfEnemies(curr); ++i)
		{
			if (enemies(curr)[i]->state == chasing)
			{
				// Clears the buffer with this colour attribute
				g_Console.clearBuffer(((int)(g_dElapsedTime * 5) % 2) * red * 17);
				return;
			}
		}
	}
	
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0);
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 5;
	c.X = c.X / 2 - 45;

	int frame = 6;
	if (g_dElapsedTime * 2 < 7)
		frame = (int)(g_dElapsedTime * 2);

	for (int r = 0; r < 15; ++r)
	{
		g_Console.writeToBuffer(c, splashScreen[frame][r], white);
		c.Y++;
	}

	if (g_dElapsedTime * 2 < 7)
		return;

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "WELCOME TO ROBERT", white);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "Press <Space> to start", white);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 10;
	g_Console.writeToBuffer(c, "Press <Esc> to quit", white);
}

void renderLoadingScreen1()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 4;
	c.X = c.X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", black);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", black);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                    O", black);
	c.X = g_Console.getConsoleSize().X / 2 - 14;
	g_Console.writeToBuffer(c, "O                   ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "     LOADING    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", black);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 17;
	g_Console.writeToBuffer(c, "FIND THE KEY. UNLOCK THE SAFE.", white);

	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "    RUN.    ", white);
}

void renderLoadingScreen2()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 4;
	c.X = c.X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", black);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", black);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                    O", black);
	c.X = g_Console.getConsoleSize().X / 2 - 14;
	g_Console.writeToBuffer(c, "O                   ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "     LOADING.   ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 17;
	g_Console.writeToBuffer(c, "FIND THE KEY. UNLOCK THE SAFE.", white);

	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "    RUN.    ", white);
}

void renderLoadingScreen3()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 4;
	c.X = c.X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                    O", black);
	c.X = g_Console.getConsoleSize().X / 2 - 14;
	g_Console.writeToBuffer(c, "O                   ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "    LOADING..   ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 17;
	g_Console.writeToBuffer(c, "FIND THE KEY. UNLOCK THE SAFE.", white);

	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "    RUN.    ", white);
}

void renderLoadingScreen4()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 4;
	c.X = c.X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                    O", white);
	c.X = g_Console.getConsoleSize().X / 2 - 14;
	g_Console.writeToBuffer(c, "O                   ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 11;
	g_Console.writeToBuffer(c, "     LOADING    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                O  ", black);
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 17;
	g_Console.writeToBuffer(c, "FIND THE KEY. UNLOCK THE SAFE.", white);

	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "    RUN.    ", white);
}

void renderLoadingScreen5()
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 4;
	c.X = c.X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             O  ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "                    O", white);
	c.X = g_Console.getConsoleSize().X / 2 - 14;
	g_Console.writeToBuffer(c, "O                   ", white);
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "     STARTING..    ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "   O             O  ", white);

	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 7;
	g_Console.writeToBuffer(c, "    O    ", white);

	c.Y += 5;
	c.X = g_Console.getConsoleSize().X / 2 - 17;
	g_Console.writeToBuffer(c, "FIND THE KEY. UNLOCK THE SAFE.", white);

	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 8;
	g_Console.writeToBuffer(c, "    RUN.    ", white);
}

void renderWinScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 5;
	c.X = c.X / 2 - 45;
	for (int r = 0; r < 15; ++r)
	{
		g_Console.writeToBuffer(c, winScreen[0][r], white);
		c.Y++;
	}
	c.Y += 3;
	c.X = g_Console.getConsoleSize().X / 2 - 5;
	g_Console.writeToBuffer(c, "YOU WON!!", white);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 12;
	g_Console.writeToBuffer(c, "Press <Space> to re-start", white);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 10;
	g_Console.writeToBuffer(c, "Press <Esc> to quit", white);
}

void renderLoseScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
		c.Y /= 5;
		c.X = c.X / 2 - 45;
		for (int r = 0; r < 15; ++r)
		{
			g_Console.writeToBuffer(c, loseScreen[0][r], white);
			c.Y++;
		}
		c.Y += 3;
		c.X = g_Console.getConsoleSize().X / 2 - 5;
		g_Console.writeToBuffer(c, "YOU DIED!", white);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 12;
		g_Console.writeToBuffer(c, "Press <Space> to re-start", white);
		c.Y += 1;
		c.X = g_Console.getConsoleSize().X / 2 - 10;
		g_Console.writeToBuffer(c, "Press <Esc> to quit", white);
}

void renderGame(Player* player)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	if (currentLevel != S_LOSESCREEN)
	{
		for (int r = 0; r < g->size.Y; ++r)
			for (int c = 0; c < g->size.X; ++c)
					g->nodes[r][c].seen = g->nodes[r][c].getState() == interactiveItems[WALL] && player->currentStorey == 1;
		renderPlayerVision(player1());
		renderPlayerVision(player2());
	}
	renderMap(player);        // renders the map to the buffer first
	renderMessage(attrs()[player->facingIn(grid(storey))->getState()], player);

	if (player->openedInventory)
		renderInventory(player);

	for (unsigned int i = 0; i < numberOfEnemies(storey); ++i)
		renderEnemyVision(enemies(storey)[i], player);

    renderPlayers(player);  // renders the character into the buffer
	renderEnemies(player);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void checkGamestate()
{
	for (int p = 0; p < 2; ++p)
	{
		Player* player = players()[p];
		unsigned int storey = player->currentStorey;
		for (unsigned int i = 0; i < numberOfEnemies(storey); ++i)
		{
			Enemy *e = enemies(storey)[i];
			if (e->position.coord == player->position.coord && !player->isGod)
				g_eGameState = S_LOSESCREEN;
		}
	}
}