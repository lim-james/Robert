#ifndef NODE_H
#define NODE_H

#include <Windows.h>
#include "State.h"

class Node
{
public:
	State onState;
	State offState;
	bool seen, toggled, isPickable;				// if true the player cannot walk through

	Node();										// default constructor
	Node(State, State, bool, bool, bool);		// comprehensive constructor
	~Node();									// default deconstructor

	State &getState();
	char &getIcon();
	bool &getIsBlocked();
	bool &getIsSeeThrough();
	bool &getPlayingSound();
	WORD getAttribute();

	void toggle();
};

#endif