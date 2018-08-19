#ifndef STATE_H
#define STATE_H

#include "Colours.h"

struct State
{
	char icon;					// stores the icon of the node
	bool isBlocked;
	Colour foregroundColour;	// colour of icon
	Colour backgroundColour;
	
	State();
	State(char, bool, Colour, Colour);

	bool operator<(const State &s) const;
};

#endif