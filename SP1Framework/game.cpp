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
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
		case S_LOSESCREEN: loseScreenWait();
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
		case S_GAME:
			renderGame(player1());
			renderGame(player2());
            break;
		case S_LOSESCREEN: renderLoseScreen();
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
		g_eGameState = S_GAME;
	}
}

void loseScreenWait()
{
	if (g_abKeyPressed[K_SPACE]) // wait for space to switch to game mode, else do nothing
	{
		setLevel(currentLevel);
		g_eGameState = S_GAME;
	}
}

void gameplay()            // gameplay logic
{
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
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(black * 17);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "WELCOME TO ROBERT", 0x12);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 11;
    g_Console.writeToBuffer(c, "Press <Space> to start", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 10;
    g_Console.writeToBuffer(c, "Press <Esc> to quit", 0x09);
}

void renderLoseScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 5;
	g_Console.writeToBuffer(c, "YOU LOST", 0x12);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 13;
	g_Console.writeToBuffer(c, "Press <Space> to re-start", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 10;
	g_Console.writeToBuffer(c, "Press <Esc> to quit", 0x09);
}

void renderGame(Player* player)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	if (currentLevel != S_LOSESCREEN)
	{
		for (int r = 0; r < g->size.Y; ++r)
			for (int c = 0; c < g->size.X; ++c)
				g->nodes[r][c].seen = g->nodes[r][c].getState() == interactiveItems[WALL];
		renderPlayerVision(player1());
		renderPlayerVision(player2());
	}
	renderMap(player);        // renders the map to the buffer first
	renderMessage(attrs()[player->facingIn(grid(storey))->getState()], player);

	if (player->openedInventory)
		renderInventory(player);

	for (int i = 0; i < numberOfEnemies(storey); ++i)
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
		for (int i = 0; i < numberOfEnemies(storey); ++i)
		{
			Enemy *e = enemies(storey)[i];
			if (e->position.coord == player->position.coord && !player->isGod)
				g_eGameState = S_LOSESCREEN;
		}
	}
}