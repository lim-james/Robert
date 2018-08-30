#include "LevelHelpers.h"

LEVELSTATES currentLevel = L_AUNTYS_HOUSE;

Level *level = new Level(levelFiles[currentLevel]);

//--------------------------------------------------------------
// Purpose  : Get level files from .txt
//			  Init contents and enemy pos.
// Input    : File path 
// Output   : N.A.
//--------------------------------------------------------------
void setLevel(LEVELSTATES l)
{
	currentLevel = l;
	delete level;
	level = new Level(levelFiles[currentLevel]);
	for (int p = 0; p < 2; ++p)
	{
		Player *player = players()[p];
		for (int i = 0; i < numberOfEnemies(player->currentStorey); ++i)
		{
			Enemy* e = enemies(player->currentStorey)[i];
			e->generatePath(e->position, e->targetPosition, grid(player->currentStorey));
		}
	}
}

Player** players() { return level->players; }
Player* player1() { return level->players[0]; }
Player* player2() { return level->players[1]; }
Grid* grid(unsigned int x) { return level->storeys[x]; }
unsigned int numberOfEnemies(unsigned int x) { return level->numberOfEnemies[x]; }
Enemy** enemies(unsigned int x) { return level->enemies[x]; }
std::map<State, std::string> attrs() { return level->attrs; };