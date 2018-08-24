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
#include <thread>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(80, 40, "ROBERT");

const struct SplitScreen {
	static const int width = 40;
	static const int height = 40;

	static const int paddingX = 1;
	static const int paddingY = 2;

	static const int centerX() { return width / 2; }
	static const int centerY() { return height / 2; }
} splitScreen;

std::string levelFiles[L_COUNT] = {
	"SPLASHSCREEN_LEVEL.txt",
	"VILLAGE_1ST_LEVEL.txt",
	"LOSESCREEN_LEVEL.txt"
};
//Level *level = new Level("AUNTY'S_HOUSE_LEVEL.txt");

LEVELSTATES currentLevel = L_START;

Level *level = new Level("SPLASHSCREEN_LEVEL.txt");

void setLevel(LEVELSTATES l)
{
	currentLevel = l;
	delete level;
	level = new Level(levelFiles[currentLevel]);
	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		enemies()[i]->generatePath(enemies()[i]->position, enemies()[i]->targetPosition, grid());
	}
}

Player** players() { return level->players; }
Player* player1() { return level->players[0]; }
Player* player2() { return level->players[1]; }
Grid* grid() { return level->storeys[level->currentStorey]; }
unsigned int numberOfEnemies() { return level->numberOfEnemies[level->currentStorey]; }
Enemy** enemies() { return level->enemies[level->currentStorey]; }
std::map<State, std::string> attrs() { return level->attrs; };

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
	g_Console.setConsoleFont(0, 25, L"Raster Fonts");
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
	g_abKeyPressed[K_TAB] = isKeyPressed(VK_TAB);
	g_abKeyPressed[K_BACKSLASH] = isKeyPressed(VK_OEM_5);
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

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
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
	playerKeyEvents();  // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void playerKeyEvents()
{
	player1()->somethingHappened = false;
	player2()->somethingHappened = false;

	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		Enemy *e = enemies()[i];
		if (g_dElapsedTime > e->bounceTime)
		{
			e->bounceTime = e->movementDelay + g_dElapsedTime;
			if (e->isInView(player1(), grid()))
			{
				e->movementDelay = 0.1;
				if (e->chase(player1(), grid()))
					setLevel(L_LOSE);
			} 
			else if (e->isInView(player2(), grid()))
			{
				e->movementDelay = 0.1;
				if (e->chase(player2(), grid()))
					setLevel(L_LOSE);
			}
			else
			{
				e->movementDelay = 0.25;
				//std::thread m(&Enemy::move, e, grid());
				//m.detach();
				e->move(grid());
			}
		}
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

			if (g_abKeyPressed[i % 2 ? K_BACKSLASH : K_TAB])
			{
				player->openedInventory = !player->openedInventory;
				player->somethingHappened = true;
			}
			
		}
		if (player->somethingHappened)
			player->bounceTime = g_dElapsedTime + 0.125;
	}

	if (player1()->somethingHappened || player2()->somethingHappened)
	{
		if (player1()->standingOn(grid())->getIcon() == (char)186 && player2()->standingOn(grid())->getIcon() == (char)186)
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
	if (player->isHidden) 
		return;
	
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

	// door
	if (item->getState() == State((char)178, true, true, (Colour)8, (Colour)15) && (currentLevel == L_START || currentLevel == L_LOSE))
	{
		setLevel(L_AUNTYS_HOUSE);
	}
	// key
	else if (item->getState() == State((char)157, true, false, (Colour)11, (Colour)5) && (currentLevel == L_AUNTYS_HOUSE))
	{
		player->storeItem(item->getState());
		item->toggle();
	}
	// cupboard
	else if (item->getState() == State((char)254, true, false, (Colour)3, (Colour)15) && (currentLevel == L_AUNTYS_HOUSE))
	{
		player->isHidden = !player->isHidden;
	}
	// bed
	else if (attrs()[item->getState()] == "bed")
	{
		player->isHidden = !player->isHidden;
	}
	// unlock safe
	else if ((item->getState() == State((char)240, true, true, (Colour)13, (Colour)15)) && player->hasItem(State((char)157, true, false, (Colour)11, (Colour)5)))
	{
		setLevel(L_START);
	}
	else
	{
		item->toggle();
	}

	player->somethingHappened = true;
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void renderInventory(Player* player)
{
	char i[7][7] = {
		{ 201, 205, 203, 205, 203, 205, 187 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 204, 205, 206, 205, 206, 205, 185 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 204, 205, 206, 205, 206, 205, 185 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 200, 205, 202, 205, 202, 205, 188 }
	};
	i[1][1] = player->items[0].icon;

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			COORD c = { x, y };
			if (player == player1())
			{
				renderInventoryPoint1(c, i[y][x], white);
			}
			else
			{
				renderInventoryPoint2(c, i[y][x], white);
			}
		}
	}
}

void renderInventoryPoint1(COORD c, char i, WORD attr)
{
	unsigned int offsetX = (g_Console.getConsoleSize().X - grid()->size.X - 14) / 4;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - 7) / 2;


	c.X += offsetX;
	c.Y += offsetY;

	g_Console.writeToBuffer(c, i, attr);
}

void renderInventoryPoint2(COORD c, char i, WORD attr)
{
	unsigned int offsetX = g_Console.getConsoleSize().X - ((g_Console.getConsoleSize().X - grid()->size.X - 14) / 4) - 7;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - 7) / 2;
	c.X += offsetX;
	c.Y += offsetY;

	g_Console.writeToBuffer(c, i, attr);
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
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame(Player* player)
{
	if (currentLevel != L_START && currentLevel != L_LOSE)
	{
		renderPlayerVision(player1());
		renderPlayerVision(player2());
	}
	renderMap(player);        // renders the map to the buffer first
	//renderMessage(attrs()[player1()->facingIn(grid())->getState()], player1());
	//renderMessage(attrs()[player2()->facingIn(grid())->getState()], player2());

	//if (player1()->openedInventory)
	//	renderInventory(player1());
	//if (player2()->openedInventory)
	//	renderInventory(player2());

	//for (int i = 0; i < numberOfEnemies(); ++i)
	//{
	//	renderEnemyVision(enemies()[i]);
	//	std::vector<Position> &path = enemies()[i]->getPath();
	//	for (int p = 0; p < path.size(); ++p)
	//	{
	//		renderPoint(path[p].coord, ' ', yellow * 17, player1());
	//		renderPoint(path[p].coord, ' ', yellow * 17, player2());
	//	}
	//}

    renderCharacter(player);  // renders the character into the buffer
}

void renderMap(Player* player)
{
	COORD coord;
	if (currentLevel == L_START || currentLevel == L_LOSE)
	{
		for (int r = 0; r < grid()->size.Y; ++r)
		{
			coord.Y = r;
			for (int c = 0; c < grid()->size.X; ++c)
			{
				Node &n = grid()->nodes[r][c];
				coord.X = c;
				if (n.seen)
				{
					renderPoint(coord, n.getIcon(), n.getAttribute(), player1());
					renderPoint(coord, n.getIcon(), n.getAttribute(), player2());
				}
			}
		}
	} 
	else
	{
		COORD &pos = player->position.coord;
		int sizeX = splitScreen.centerX() - splitScreen.paddingX;
		int sizeY = splitScreen.centerY() - splitScreen.paddingY;
		for (int r = -sizeY; r < sizeY; ++r)
		{
			coord.Y = r + sizeY + splitScreen.paddingY;
			for (int c = -sizeX; c < sizeX; ++c)
			{
				coord.X = c + sizeX + splitScreen.paddingX;
				int y = r;
				if (pos.Y < sizeY)
					y += sizeY;
				else if (pos.Y > grid()->size.Y - sizeY)
					y += grid()->size.Y - sizeY;
				else
					y += pos.Y;

				int x = c;
				if (pos.X < sizeX)
					x += sizeX;
				else if (pos.X > grid()->size.X - sizeX)
					x += grid()->size.X - sizeX;
				else
					x += pos.X;
				
				Node &n = grid()->nodes[y][x];
				if (n.seen)
					renderPoint(coord, n.getIcon(), n.getAttribute(), player);
			}
		}
	}
	
}

void renderCharacter(Player* player)
{
	int sizeX = splitScreen.centerX();
	int sizeY = splitScreen.centerY();

	Player* other = player == player1() ? player2() : player1();

	COORD pos = player->position.coord;
	COORD otherPos = other->position.coord;

	if (pos.Y > sizeY - splitScreen.paddingY)
	{
		if (grid()->size.Y - pos.Y < sizeY - splitScreen.paddingY)
		{
			pos.Y = splitScreen.height - grid()->size.Y + pos.Y - splitScreen.paddingY;
		 	otherPos.Y = splitScreen.height - grid()->size.Y + otherPos.Y - splitScreen.paddingY;
		}
		else
		{
			otherPos.Y -= pos.Y - sizeY;
			pos.Y = splitScreen.centerY();
		}
	}  
	else
	{
		pos.Y += splitScreen.paddingY;
		otherPos.Y += splitScreen.paddingY;
	}

	if (pos.X > sizeX - splitScreen.paddingX)
	{
		if (grid()->size.X - pos.X < sizeX - splitScreen.paddingX)
		{
			pos.X = splitScreen.width - grid()->size.X + pos.X - splitScreen.paddingX;
			otherPos.X = splitScreen.width - grid()->size.X + otherPos.X - splitScreen.paddingX;
		}
		else
		{
			otherPos.X -= pos.X - sizeX;
			pos.X = splitScreen.centerX();
		}
	}
	else
	{
		pos.X += splitScreen.paddingX;
		otherPos.X += splitScreen.paddingX;
	}	

	renderPoint(pos, player->getIcon(), player->getAttribute(), player);
	if (otherPos.X >= splitScreen.paddingX && otherPos.X < splitScreen.width - splitScreen.paddingX &&
		otherPos.Y >= splitScreen.paddingY && otherPos.Y < splitScreen.height - splitScreen.paddingY)
		renderPoint(otherPos, other->getIcon(), other->getAttribute(), player);

	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		Enemy *enemy = enemies()[i];
		renderPoint(enemy->position.coord, enemy->icon, enemy->getAttribute(), player1());
		renderPoint(enemy->position.coord, enemy->icon, enemy->getAttribute(), player2());
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
		g_Console.writeToBuffer(c, ' ', 0x00);

	int length = str.length();
	c.X = (g_Console.getConsoleSize().X - str.length()) / 2;
	g_Console.writeToBuffer(c, str, 0x0f);
}

void renderEnemyVision(Enemy* e)
{
	short x1, y1, x2, y2;
	switch (e->position.facing)
	{
	case up:
		x1 = +1; y1 = -1;
		x2 = -1; y2 = -1;
		break;
	case down:
		x1 = +1; y1 = +1;
		x2 = -1; y2 = +1;
		break;
	case left:
		x1 = -1; y1 = +1;
		x2 = -1; y2 = -1;
		break;
	case right:
		x1 = +1; y1 = +1;
		x2 = +1; y2 = -1;
		break;
	}
	renderEnemyVisionPoint(e->position.coord, x1, y1);
	renderEnemyVisionPoint(e->position.coord, x2, y2);
}

void renderEnemyVisionPoint(COORD c, short x, short y)
{
	c.Y += y;
	c.X += x;
	if (c.X < 0 || c.X >= grid()->size.X ||
		c.Y < 0 || c.Y >= grid()->size.Y ||
		!grid()->nodes[c.Y][c.X].getIsSeeThrough())
		return;

	renderPoint(c, ' ', lightGrey * 17, player1());
	renderPoint(c, ' ', lightGrey * 17, player2());

	renderEnemyVisionPoint(c, x, y);
}

void renderPlayerVision(Player* p)
{
	float x1, y1, x2, y2;
	for (float a = 1; a <= 45; ++a)
	{
		double angle = a / 180.0 * M_PI;
		switch (p->position.facing)
		{
		case up:
			x1 = +1; y1 = -1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case down:
			x1 = +1; y1 = +1;
			x2 = -1; y2 = +1;
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case left:
			x1 = -1; y1 = +1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		case right:
			x1 = +1; y1 = +1;
			x2 = +1; y2 = -1;
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		}
		
	}
}

void renderPlayerVisionPoint(float x, float y, float xDiff, float yDiff)
{
	COORD c;
	c.X = x + xDiff;
	c.Y = y + yDiff;
	Node &n = grid()->nodes[c.Y][c.X];
	if (c.X < 0 || c.X >= grid()->size.X ||
		c.Y < 0 || c.Y >= grid()->size.Y)
		return;

	n.seen = true;
	if (!n.getIsSeeThrough())
		return;
	renderPlayerVisionPoint(x + xDiff, y + yDiff, xDiff, yDiff);
}

void renderPoint(COORD c, char i, WORD attr, Player *player)
{
	if (player == player2())
		c.X += splitScreen.width;

	g_Console.writeToBuffer(c, i, attr);
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
	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		if (enemies()[i]->isInView(player1(), grid()) || enemies()[i]->isInView(player2(), grid()))
		{
			Sleep(1000);
			setLevel(L_LOSE);
		}
	}
}