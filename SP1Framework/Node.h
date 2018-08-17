#ifndef NODE_H
#define NODE_H

#include <Windows.h>
#include "State.h"

struct Node
{
	State onState;
	State offState;
	bool isBlocked, seen, toggled, isPickable;				// if true the player cannot walk through

	Node();										// default constructor
	Node(State, State, bool, bool, bool);		// comprehensive constructor
	~Node();									// default deconstructor

	State getState();
	char getIcon();
	bool getIsBlocked();
	WORD getAttribute();						// returns attribute
};

#endif