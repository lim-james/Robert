#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Level.h"
#include "Actions.h"

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
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_COUNT
};

Level* level();
Player** players();
Player* player1();
Player* player2();
Grid* grid();
unsigned int numberOfEnemies();
Enemy** enemies();
std::map<char, std::string> attrs();

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void movePlayer(Player*, Direction);	// moves a player in direction
void playerAction(Player*);	// check if player can perform action and performs it
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderEnemyVision(Enemy*);	// renders enemy's vision
void renderEnemyVisionPoint(COORD, short, short);	// renders enemy's view points
void renderPoint(COORD, char, WORD);
void renderMessage(std::string, Player*); // renders a short message for player
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

#endif // _GAME_H