#ifndef GAME_STATE_HELPERS_H
#define GAME_STATE_HELPERS_H

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_LOSESCREEN,
	S_COUNT
};

// Game specific variables here
extern EGAMESTATES g_eGameState;

#endif