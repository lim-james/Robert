#ifndef PERSON_H
#define PERSON_H

#include <Windows.h>
#include "Grid.h"
#include "Position.h"

class Person
{
public:
	char icon;					// stores the icon of the node
	Position position;				// position and facing direction of player
	Colour foregroundColor;		// colour of icon
	Colour backgroundColor;		// colour of background
	double bounceTime = 0;
	bool isHidden;

	Person();										// default constructor
	Person(const char, Position, Colour, Colour);		// comprehensive constructor
	~Person();										// default deconstructor

	char getIcon();
	WORD getAttribute();							// returns attribute
	bool canMoveIn(Grid*);							// moves player in a specified direction
	void move();									// moves player in a specified direction
	Node* facingIn(Grid*);
	Node* standingOn(Grid*);
	bool isInView(Person*, Grid*);
};

#endif
