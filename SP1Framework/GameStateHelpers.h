#ifndef GAME_STATE_HELPERS_H
#define GAME_STATE_HELPERS_H

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_LOADINGSCREEN1,
	S_LOADINGSCREEN2,
	S_LOADINGSCREEN3,
	S_LOADINGSCREEN4,
	S_LOADINGSCREEN5,
	S_GAME,
	S_LOSESCREEN,
	S_COUNT
};

// Game specific variables here
extern EGAMESTATES g_eGameState;

#endif