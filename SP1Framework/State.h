#ifndef STATE_H
#define STATE_H

#include "Colours.h"

class State
{
public:
	char icon;					// stores the icon of the node
	bool isBlocked;
	bool isSeeThrough;
	Colour foregroundColour;	// colour of icon
	Colour backgroundColour;
	int soundRadius;
	bool playingSound;

	State();
	State(char, bool, bool, Colour, Colour, int, bool);

	bool operator==(const State &s) const;
	bool operator<(const State &s) const;
};

#endif