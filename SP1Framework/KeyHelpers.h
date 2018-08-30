#ifndef KEY_HELPERS_H
#define KEY_HELPERS_H

#include "Framework/console.h"

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
	K_LSHIFT,
	K_RSHIFT,
	K_F1,
	K_F2,
	K_F3,
	K_F12,
	K_COUNT
};

extern bool g_abKeyPressed[K_COUNT];

void getInput(void);      // get input from player

#endif