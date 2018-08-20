  #ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person 
{
public:
	bool somethingHappened, openedInventory;
	double bounceTime = 0;

	Player();										// default constructor
	Player(const char, Position, Colour, Colour);		// comprehensive constructor
	~Player();										// default deconstructor
};

#endif