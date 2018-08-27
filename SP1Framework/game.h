#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Level.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
	K_W,
	K_A,
	K_S,
	K_D,
    K_ESCAPE,
	K_RETURN,
    K_SPACE,
	K_TAB,
	K_BACKSLASH,
    K_COUNT,
	K_LSHIFT,
	K_RSHIFT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_LOSESCREEN,
    S_COUNT
};

enum LEVELSTATES
{
	L_AUNTYS_HOUSE,
	L_COUNT
};

void setLevel(LEVELSTATES);
Player** players();
Player* player1();
Player* player2();
Grid* grid(unsigned int);
unsigned int numberOfEnemies(unsigned int);
Enemy** enemies(unsigned int);
std::map<State, std::string> attrs();

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory
void splashScreenWait();    // waits for time to pass in splash screen
void loseScreenWait();
void gameplay();            // gameplay logic
void playerKeyEvents();       // moves the character, collision detection, physics, etc
void movePlayer(Player*, Direction);	// moves a player in direction
void playerAction(Player*);	// check if player can perform action and performs it
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit

void renderInventory(Player*);	// renders the player inventory
void renderInventoryPoint(COORD, char, WORD, Player*);	// renders inventory for player

void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderLoseScreen();

void renderGame(Player*);   // renders the game stuff

void renderMap(Player*);           // renders the map to the buffer first

void renderPlayers(Player*);// renders the character into the buffer
void renderEnemies(Player*);// renders the character into the buffer
void renderPerson(Person*, Player*);

void renderEnemyVision(Enemy*, Player*);	// renders enemy's vision
void renderEnemyVisionPoint(Enemy*, COORD, short, short, Player*);	// renders enemy's view points

void renderPlayerVision(Player*);	// renders enemy's vision
void renderPlayerVisionPoint(Player*, float, float, float, float);	// renders enemy's view points

void renderMapPoint(COORD, char, WORD, Player*);
void renderPoint(COORD, char, WORD, Player*);
void renderLine(COORD, LPCSTR, WORD, Player*);

void renderMessage(std::string, Player*); // renders a short message for player

void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void checkGamestate();

int distance(COORD, COORD);

#endif // _GAME_H