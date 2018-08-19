#ifndef LEVEL_H
#define LEVEL_H

#include "Grid.h"
#include "Enemy.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

struct Level {
	unsigned int numberOfStoreys;
	unsigned int currentStorey;
	Grid **storeys;
	unsigned int *numberOfEnemies;
	Enemy ***enemies;
	Player *players[2];

	// stores attributes of nodes
	std::map<State, std::string> attrs;

	Level(std::string);

	void initPlayers(std::string);
	void initAttrs(std::string);
};

#endif