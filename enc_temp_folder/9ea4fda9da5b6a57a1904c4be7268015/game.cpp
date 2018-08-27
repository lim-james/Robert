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

#define WIDTH 120
#define HEIGHT 30

// Console object
Console g_Console(WIDTH, HEIGHT, "ROBERT");

const struct SplitScreen {
	static const int width = WIDTH / 2;
	static const int height = HEIGHT;

	static const int paddingX = 1;
	static const int paddingY = 7;

	static const int centerX() { return width / 2; }
	static const int centerY() { return height / 2; }
	static const int diagonal() { return sqrt(pow(centerX(), 2.0) + pow(centerY(), 2.0)); }
} splitScreen;

std::string levelFiles[L_COUNT] = {
	"VILLAGE_LEVEL.txt"
};
//Level *level = new Level("AUNTY'S_HOUSE_LEVEL.txt");

LEVELSTATES currentLevel = L_AUNTYS_HOUSE;

Level *level = new Level(levelFiles[currentLevel]);

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
//** cameras() { return level->cameras[level->currentStorey]; }
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
	g_abKeyPressed[K_LSHIFT] = isKeyPressed(VK_LSHIFT);
	g_abKeyPressed[K_RSHIFT] = isKeyPressed(VK_RSHIFT);
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

void playerKeyEvents()
{
	player1()->somethingHappened = false;
	player2()->somethingHappened = false;

	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		Enemy *e = enemies()[i];
		Node* item = e->facingIn(grid());

		if (g_dElapsedTime > e->bounceTime)
		{
			if (e->isInView(player1(), grid()))
			{
				if (!e->isStationary)
				{
					e->chase(player1(), grid());
				}
				else
				{
					e->alert(numberOfEnemies(), enemies(), player1(), grid());
				}
			}
			else if (e->isInView(player2(), grid()))
			{
				if (!e->isStationary)
				{
					e->chase(player2(), grid());
				}
				else
				{
					e->alert(numberOfEnemies(), enemies(), player2(), grid());
				}
			}
			else
			{
				e->check(grid());
				e->move(grid());
			}
			e->bounceTime = e->getMovementDelay() + g_dElapsedTime;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		Player *player = players()[i];
		player->isSprinting = false;
		if (g_abKeyPressed[i % 2 ? K_RSHIFT : K_LSHIFT])
		{
			player->isSprinting = true;
		}

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
			player->bounceTime = g_dElapsedTime + player->getMovementDelay();


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
	if (item->getState() == State((char)178, true, false, (Colour)8, (Colour)15, 0, false))
	{
		setLevel(L_AUNTYS_HOUSE);
	}
	// key
	else if (item->getState() == State((char)157, true, true, (Colour)11, (Colour)5, 0, false) && currentLevel == L_AUNTYS_HOUSE)
	{
		player->storeItem(item->getState());
		item->toggle();
	}
	// cupboard
	else if (item->getState() == State((char)254, true, false, (Colour)3, (Colour)15, 0, false) && currentLevel == L_AUNTYS_HOUSE)
	{
		player->isHidden = !player->isHidden;
	}
	// bed
	else if (attrs()[item->getState()] == "bed")
	{
		player->isHidden = !player->isHidden;
	}
	// unlock safe and take document
	else if ((item->getState() == State((char)240, true, true, (Colour)13, (Colour)15, 0, false) && player->hasItem(State((char)157, true, true, (Colour)11, (Colour)5, 0, false))))
	{
		player->storeItem(State((char)77, true, true, (Colour)0, (Colour)15, 0, false));
		item->toggle();
	}
	else if (attrs()[item->getState()] == "] open_door" || 
			attrs()[item->getState()] == "] close_door" ||
			attrs()[item->getState()] == "] open_window" || 
			attrs()[item->getState()] == "] close_window")
	{
		item->toggle();
		item->getPlayingSound() = !item->getPlayingSound();
		item->getPlayingSound() = !item->getPlayingSound();
	}
	// end game
	else if (attrs()[item->getState()] == "] sewer" && player->hasItem(State((char)77, true, true, (Colour)0, (Colour)15, 0, false)))
	{
		g_eGameState = S_LOSESCREEN;
		Sleep(1000);
	}
	else
	{
		if ((item->isPickable && item->toggled) || !item->isPickable)
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
	i[1][3] = player->items[1].icon;
	i[1][5] = player->items[2].icon;
	i[3][1] = player->items[3].icon;
	i[3][3] = player->items[4].icon;
	i[3][5] = player->items[5].icon;
	i[5][1] = player->items[6].icon;
	i[5][3] = player->items[7].icon;
	i[5][5] = player->items[8].icon;

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

	c.X += 0;
	c.Y += 0;

	renderPoint(c, i, attr, player1());
}

void renderInventoryPoint2(COORD c, char i, WORD attr)
{
	unsigned int offsetX = g_Console.getConsoleSize().X - ((g_Console.getConsoleSize().X - grid()->size.X - 14) / 4) - 7;
	unsigned int offsetY = (g_Console.getConsoleSize().Y - 7) / 2;

	c.X += 0;
	c.Y += 0;

	renderPoint(c, i, attr, player2());
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
	
	if (currentLevel != S_LOSESCREEN)
	{
		for (int r = 0; r < grid()->size.Y; ++r)
			for (int c = 0; c < grid()->size.X; ++c)
				grid()->nodes[r][c].seen = false;
		renderPlayerVision(player1());
		renderPlayerVision(player2());
	}
	renderMap(player);        // renders the map to the buffer first
	renderMessage(attrs()[player1()->facingIn(grid())->getState()], player1());
	renderMessage(attrs()[player2()->facingIn(grid())->getState()], player2());

	if (player1()->openedInventory)
		renderInventory(player1());
	if (player2()->openedInventory)
		renderInventory(player2());

	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		renderEnemyVision(enemies()[i], player);
		//std::vector<position> &path = enemies()[i]->getpath();
		//for (int p = 0; p < path.size(); ++p)
		//{
			//renderpoint(path[p].coord, ' ', yellow * 17, player1());
			//renderpoint(path[p].coord, ' ', yellow * 17, player2());
		//}
	}

    renderPlayers(player);  // renders the character into the buffer
	renderEnemies(player);
}

void renderMap(Player* player)
{
	COORD coord;
	if (currentLevel == S_LOSESCREEN)
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

void renderPlayers(Player* player)
{
	Player* other = player == player1() ? player2() : player1();

	renderPerson(other, player);
	renderPerson(player, player);
}

void renderEnemies(Player* player)
{
	for (int i = 0; i < numberOfEnemies(); ++i)
	{
		Enemy *enemy = enemies()[i];
		if (!grid()->nodes[enemy->position.coord.Y][enemy->position.coord.X].seen)
			continue;
		renderPerson(enemy, player);
	}
}

void renderPerson(Person* person, Player* player)
{
	renderMapPoint(person->position.coord, person->getIcon(), person->getAttribute(), player);
}

void renderEnemyVision(Enemy* e, Player* player)
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
	renderEnemyVisionPoint(e, e->position.coord, x1, y1, player);
	renderEnemyVisionPoint(e, e->position.coord, x2, y2, player);
}

void renderEnemyVisionPoint(Enemy* e, COORD c, short x, short y, Player* player)
{
	c.Y += y;
	c.X += x;
	if (distance(e->position.coord, c) > e->getViewRange() ||
		c.X < 0 || c.X >= grid()->size.X ||
		c.Y < 0 || c.Y >= grid()->size.Y ||
		!grid()->nodes[c.Y][c.X].getIsSeeThrough() ||
		!grid()->nodes[c.Y][c.X].seen)
		return;

	renderMapPoint(c, ' ', lightGrey * 17, player);

	renderEnemyVisionPoint(e, c, x, y, player);
}

void renderPlayerVision(Player* p)
{
	float x1, y1, x2, y2;
	for (float a = 1; a <= 180; ++a)
	{
		double angle = a / 180.0 * M_PI;
		switch (p->position.facing)
		{
		case up:
			x1 = +1; y1 = -1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case down:
			x1 = +1; y1 = +1;
			x2 = -1; y2 = +1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case left:
			x1 = -1; y1 = +1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		case right:
			x1 = +1; y1 = +1;
			x2 = +1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		}
	}
}

void renderPlayerVisionPoint(Player* player, float x, float y, float xDiff, float yDiff)
{
	COORD c;
	c.X = x + xDiff;
	c.Y = y + yDiff;
	Node &n = grid()->nodes[c.Y][c.X];
	if (c.X < 0 || c.X >= grid()->size.X ||
		c.Y < 0 || c.Y >= grid()->size.Y)
		return;

	n.seen = true;
	if (!n.getIsSeeThrough() || sqrt(pow(player->position.coord.X - c.X, 2.0) + pow(player->position.coord.Y - c.Y, 2.0)) >= splitScreen.height - 2 * splitScreen.paddingY)
		return;
	renderPlayerVisionPoint(player, x + xDiff, y + yDiff, xDiff, yDiff);
}

void renderMapPoint(COORD c, char i, WORD attr, Player *player)
{
	int sizeX = splitScreen.centerX();
	int sizeY = splitScreen.centerY();

	COORD pos = player->position.coord;

	if (pos.Y > sizeY - splitScreen.paddingY)
	{
		if (grid()->size.Y - pos.Y < sizeY - splitScreen.paddingY)
		{
			pos.Y = splitScreen.height - grid()->size.Y + pos.Y - splitScreen.paddingY;
			c.Y = splitScreen.height - grid()->size.Y + c.Y - splitScreen.paddingY;
		}
		else
		{
			c.Y -= pos.Y - sizeY;
			pos.Y = sizeY;
		}
	}
	else
	{
		pos.Y += splitScreen.paddingY;
		c.Y += splitScreen.paddingY;
	}

	if (pos.X > sizeX - splitScreen.paddingX)
	{
		if (grid()->size.X - pos.X < sizeX - splitScreen.paddingX)
		{
			pos.X = splitScreen.width - grid()->size.X + pos.X - splitScreen.paddingX;
			c.X = splitScreen.width - grid()->size.X + c.X - splitScreen.paddingX;
		}
		else
		{
			c.X -= pos.X - sizeX;
			pos.X = splitScreen.centerX();
		}
	}
	else
	{
		pos.X += splitScreen.paddingX;
		c.X += splitScreen.paddingX;
	}

	if (c.X >= splitScreen.paddingX && c.X < splitScreen.width - splitScreen.paddingX &&
		c.Y >= splitScreen.paddingY && c.Y < splitScreen.height - splitScreen.paddingY)
		renderPoint(c, i, attr, player);
}

void renderPoint(COORD c, char i, WORD attr, Player *player)
{
	if (player == player2())
		c.X += splitScreen.width;
	g_Console.writeToBuffer(c, i, attr);
}

void renderLine(COORD c, LPCSTR str, WORD attr, Player *player)
{
	if (player == player2())
		c.X += splitScreen.width;
	g_Console.writeToBuffer(c, str, attr);
}

void renderMessage(std::string str, Player *p)
{	
	COORD c;
	c.Y = splitScreen.paddingY / 2;

	for (c.X = 0; c.X < splitScreen.width; ++c.X)
		renderPoint(c, ' ', 0x00, p);

	if (p == player2())
	{
		if (str[0] == ']') 
			str = "[enter" + str;
	}
	else
	{
		if (str[0] == ']') 
			str = "[space" + str;
	}
	
	int length = str.length();
	c.X = (splitScreen.width - str.length()) / 2;
	renderLine(c, (LPCSTR)str.c_str(), white, p);
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
		if(enemies()[i]->position.coord == player1()->position.coord || enemies()[i]->position.coord == player2()->position.coord)
			g_eGameState = S_LOSESCREEN;
	}
}

int distance(COORD a, COORD b)
{
	return sqrt(pow(a.X - b.X, 2.0) + pow(a.Y - b.Y, 2.0));
}