#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person 
{
public:
	unsigned int currentStorey = 0;
	int itemIndex = 0;
	bool somethingHappened, openedInventory, isGod = false;
	State items[9];

	Player();										// default constructor
	Player(const char, Position, Colour, Colour);	// comprehensive constructor
	~Player();										// default deconstructor

	void storeItem(State item);
	bool hasItem(State item);
};

#endif