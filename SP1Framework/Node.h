#ifndef NODE_H
#define NODE_H

#include <Windows.h>
#include "Colours.h"

struct Node
{
	char icon;					// stores the icon of the node
	bool isBlocked;				// if true the player cannot walk through
	Colour foregroundColour;	// colour of icon
	Colour backgroundColour;	// colour of background

	Node();										// default constructor
	Node(const char, bool, Colour, Colour);		// comprehensive constructor
	~Node();									// default deconstructor

	WORD getAttribute();						// returns attribute
};

#endif