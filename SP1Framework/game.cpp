// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int prevTime = 0;

// Console object
Console g_Console(256, 64, "SP1 Framework");

Level *level = new Level("AUNTY'S_HOUSE_LEVEL.txt");

Player** players() { return level->players; }
Player* player1() { return level->players[0]; }
Player* player2() { return level->players[1]; }
Grid* grid() { return level->storeys[level->currentStorey]; }
unsigned int numberOfEnemies() { return level->numberOfEnemies[level->currentStorey]; }
Enemy** enemies() { return level->enemies[level->currentStorey]; }
std::map<char, std::string> attrs() { return level->attrs; };

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    // sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");
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
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_W] = isKeyPressed(0x57);
	g_abKeyPressed[K_A] = isKeyPressed(0x41);
	g_abKeyPressed[K_S] = isKeyPressed(0x53);
	g_abKeyPressed[K_D] = isKeyPressed(0x44);
	g_abKeyPressed[K_RETURN] = isKeyPressed(VK_RETURN);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
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
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}

//--------------------------------------------------------------
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
        case S_GAME: renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
	player1()->somethingHappened = false;
	player2()->somethingHappened = false;

	if ((int)(g_dElapsedTime * 5) != prevTime)
	{
		prevTime = g_dElapsedTime * 5;
		for (int i = 0; i < numberOfEnemies(); ++i)
			enemies()[i]->move();
	}

	for (int i = 0; i < 2; ++i)
	{
		Player *player = players()[i];
		if (player->bounceTime < g_dElapsedTime)
		{
			if (g_abKeyPressed[i % 2 ? K_UP : K_W])
				movePlayer(player, up);

			if (g_abKeyPressed[i % 2 ? K_LEFT : K_A])
				movePlayer(player, left);

			if (g_abKeyPressed[i % 2 ? K_DOWN : K_S])
				movePlayer(player, down);

			if (g_abKeyPressed[i % 2 ? K_RIGHT : K_D])
				movePlayer(player, right);

			if (g_abKeyPressed[i % 2 ? K_RETURN : K_SPACE])
				playerAction(player);
		}
		if (player->somethingHappened)
			player->bounceTime = g_dElapsedTime + 0.125;
	}

	if (player1()->somethingHappened || player2()->somethingHappened)
	{
		if (player1()->standingOn(grid())->icon == (char)186 && player2()->standingOn(grid())->icon == (char)186)
		{
			if (level->currentStorey + 1 < level->numberOfStoreys)
				level->currentStorey++;
			else
				level->currentStorey = 0;
		}
	}
}

void movePlayer(Player* player, Direction dir) 
{
	if (player->position.facing == dir)
	{
		if (player->canMoveIn(grid()))
		{
			player->move();
		}
	}
	else
	{
		player->position.facing = dir;
	}
	player->somethingHappened = true;
}

void playerAction(Player* player)
{
	Node* item = player->facingIn(grid());
	if (item->icon == (char)178)
	{
		open(item, 176);
		player->somethingHappened = true;
	}
	else if (item->icon == (char)176)
	{
		close(item, 178);
		player->somethingHappened = true;
	}

	if (item->icon == (char)47)
	{
		open(item, 96);
		player->somethingHappened = true;
	}
	else if (item->icon == (char)96)
	{
		close(item, 47);
		player->somethingHappened = true;
	}
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
    g_Console.clearBuffer(0xFF);
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
	renderMessage(attrs()[player1()->facingIn(grid())->icon], player1());
	renderMessage(attrs()[player2()->facingIn(grid())->icon], player2());
}

void renderMap()
{
	unsigned int offsetX = (g_Console.getConsoleSize().X - grid()->size.X) / 2;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - grid()->size.Y) / 2;

	COORD coord;
	for (int r = 0; r < grid()->size.Y; ++r) 
	{
		coord.Y = r + offsetY;
		for (int c = 0; c < grid()->size.X; ++c)
		{
			Node &n = grid()->nodes[r][c];
			coord.X = c + offsetX;
			g_Console.writeToBuffer(coord, n.icon, n.getAttribute());
		}
	}
}

void renderCharacter()
{
	unsigned int offsetX = (g_Console.getConsoleSize().X - grid()->size.X) / 2;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - grid()->size.Y) / 2;
    
	for (int i = 0; i < 2; ++i)
	{
		Player *player = players()[i];
		COORD c1;
		c1.X = player->position.coord.X + offsetX;
		c1.Y = player->position.coord.Y + offsetY;

		g_Console.writeToBuffer(c1, player->icon, player->getAttribute());
	}

	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		Enemy *enemy = enemies()[i];
		COORD c1;
		c1.X = enemy->position.coord.X + offsetX;
		c1.Y = enemy->position.coord.Y + offsetY;

		g_Console.writeToBuffer(c1, enemy->icon, enemy->getAttribute());
	}
}

void renderMessage(std::string str, Player *p)
{	
	COORD c;
	c.Y = (g_Console.getConsoleSize().Y - grid()->size.Y) / 4;
	if (p == player2())
	{
		c.Y = g_Console.getConsoleSize().Y - c.Y;
		if (str[0] == ']') str = "[enter" + str;
	}
	else
	{
		if (str[0] == ']') str = "[space" + str;
	}

	for (c.X = 0; c.X < g_Console.getConsoleSize().X; ++c.X)
		g_Console.writeToBuffer(c, ' ', 0xff);

	int length = str.length();
	c.X = (g_Console.getConsoleSize().X - str.length()) / 2;
	g_Console.writeToBuffer(c, str, 0xf0);
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

