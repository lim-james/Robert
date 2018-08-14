#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

struct Player : Person {
	Player();										// default constructor
	Player(const char, Position, Colour, Colour);		// comprehensive constructor
	~Player();										// default deconstructor
};

#endif