// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
int prevTime = 0;

// Console object
Console g_Console(256, 64, "SP1 Framework");

// stores grid
Grid *grid = new Grid("AUNTY'S_ATTRIBUTES.txt", "AUNTY'S_HOUSE_1st_STOREY.txt");

// players
Player *player1 = new Player('#', Position(), red, white);
Player *player2 = new Player('#', Position(), blue, white);
Enemy *guard = new Enemy('=', "Guard_1.txt", black, white);

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

	COORD c1;
	c1.X = 1;
	c1.Y = 1;
	player1->position = Position(c1, up);

	COORD c2;
	c2.X = 9;
	c2.Y = 9;
	player2->position = Position(c2, up);

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
	player1->somethingHappened = false;
	player2->somethingHappened = false;

	if ((int)(g_dElapsedTime * 5) != prevTime)
	{
		prevTime = g_dElapsedTime * 5;
		guard->move();
	}
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
	if (player1->bounceTime < g_dElapsedTime)
	{
		// player 1 actions
		if (g_abKeyPressed[K_W])
		{
			if (player1->position.facing == up)
			{
				if (player1->canMoveIn(grid))
				{
					//Beep(1440, 30);
					player1->move();
				}
			}
			else
			{
				player1->position.facing = up;
			}
			player1->somethingHappened = true;
		}
		if (g_abKeyPressed[K_A])
		{
			if (player1->position.facing == left)
			{
				if (player1->canMoveIn(grid))
				{
					//Beep(1440, 30);
					player1->move();
				}
			}
			else
			{
				player1->position.facing = left;
			}
			player1->somethingHappened = true;
		}
		if (g_abKeyPressed[K_S])
		{
			if (player1->position.facing == down)
			{
				if (player1->canMoveIn(grid))
				{
					//Beep(1440, 30);
					player1->move();
				}
			}
			else
			{
				player1->position.facing = down;
			}
			player1->somethingHappened = true;
		}
		if (g_abKeyPressed[K_D])
		{
			if (player1->position.facing == right)
			{
				if (player1->canMoveIn(grid))
				{
					//Beep(1440, 30);
					player1->move();
				}
			}
			else
			{
				player1->position.facing = right;
			}
			player1->somethingHappened = true;
		}
		if (g_abKeyPressed[K_SPACE])
		{
			if (!player1->ifFacing(178, grid, openDoor, 176))
			{
				if (player1->ifFacing(176, grid, closeDoor, 178))
				{
					player1->somethingHappened = true;
				}
			}
			else
			{
				player1->somethingHappened = true;
			}
		}
	}

	if (player2->bounceTime < g_dElapsedTime)
	{
		if (g_abKeyPressed[K_UP])
		{
			if (player2->position.facing == up)
			{
				if (player2->canMoveIn(grid))
				{
					player2->move();
				}
			}
			else
			{
				player2->position.facing = up;
			}
			player2->somethingHappened = true;
		}
		if (g_abKeyPressed[K_LEFT])
		{
			if (player2->position.facing == left)
			{
				if (player2->canMoveIn(grid))
				{
					player2->move();
				}
			}
			else
			{
				player2->position.facing = left;
			}
			player2->somethingHappened = true;
		}
		if (g_abKeyPressed[K_DOWN])
		{
			if (player2->position.facing == down)
			{
				if (player2->canMoveIn(grid))
				{
					player2->move();
				}
			}
			else
			{
				player2->position.facing = down;
			}
			player2->somethingHappened = true;
		}
		if (g_abKeyPressed[K_RIGHT])
		{
			if (player2->position.facing == right)
			{
				if (player2->canMoveIn(grid))
				{
					player2->move();
				}
			}
			else
			{
				player2->position.facing = right;
			}
			player2->somethingHappened = true;
		}

		if (g_abKeyPressed[K_RETURN])
		{
			if (!player2->ifFacing(178, grid, openDoor, 176))
			{
				if (player2->ifFacing(176, grid, closeDoor, 178))
				{
					player2->somethingHappened = true;
				}
			}
			else
			{
				player2->somethingHappened = true;
			}
		}
	}

	

    if (player1->somethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        player1->bounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }

	if (player2->somethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		player2->bounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
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
    g_Console.clearBuffer(0x1F);
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
}

void renderMap()
{
	unsigned int offsetX = (g_Console.getConsoleSize().X - grid->size.X) / 2;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - grid->size.Y) / 2;

	COORD coord;
	for (int r = 0; r < grid->size.Y; ++r) 
	{
		coord.Y = r + offsetY;
		for (int c = 0; c < grid->size.X; ++c)
		{
			Node &n = grid->nodes[r][c];
			coord.X = c + offsetX;
			g_Console.writeToBuffer(coord, n.icon, n.getAttribute());
		}
	}
}

void renderCharacter()
{
	unsigned int offsetX = (g_Console.getConsoleSize().X - grid->size.X) / 2;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - grid->size.Y) / 2;
    
	COORD c1;
	c1.X = player1->position.coord.X + offsetX;
	c1.Y = player1->position.coord.Y + offsetY;

	g_Console.writeToBuffer(c1, player1->icon, player1->getAttribute());

	COORD c2;
	c2.X = player2->position.coord.X + offsetX;
	c2.Y = player2->position.coord.Y + offsetY;

	g_Console.writeToBuffer(c2, player2->icon, player2->getAttribute());

	COORD enemy;
	enemy.X = guard->position.coord.X + offsetX;
	enemy.Y = guard->position.coord.Y + offsetY;

	g_Console.writeToBuffer(enemy, guard->icon, guard->getAttribute());
}

void renderMessage(std::string str, Player *p)
{
	COORD c;
	c.Y = (g_Console.getConsoleSize().Y - grid->size.Y) / 4;
	if (p == player2) c.Y *= 3;

	for (c.X = 0; c.X < g_Console.getConsoleSize().X; ++c.X)
		g_Console.writeToBuffer(c, ' ');

	c.X = (g_Console.getConsoleSize().X - str.length()) / 2;
	g_Console.writeToBuffer(c, str);
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

