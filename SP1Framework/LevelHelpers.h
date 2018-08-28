#ifndef LEVEL_HELPERS_H
#define LEVEL_HELPERS_H

#include "Level.h"

enum LEVELSTATES
{
	L_AUNTYS_HOUSE,
	L_COUNT
};

const std::string levelFiles[L_COUNT] = {
	"VILLAGE_LEVEL.txt"
};

extern LEVELSTATES currentLevel;

extern Level *level;

void setLevel(LEVELSTATES);

Player** players();
Player* player1();
Player* player2();
Grid* grid(unsigned int);
unsigned int numberOfEnemies(unsigned int);
Enemy** enemies(unsigned int);
std::map<State, std::string> attrs();

#endif