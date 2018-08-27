#ifndef PERSON_H
#define PERSON_H

#include <Windows.h>
#include "Grid.h"
#include "PathNode.h"

class Person
{
public:
	char icon;					// stores the icon of the node
	Position position;				// position and facing direction of player
	Colour foregroundColor;		// colour of icon
	Colour backgroundColor;		// colour of background
	double bounceTime = 0;
	bool isHidden;
	float movementDelay;
	bool isSprinting;

	Person();										// default constructor
	Person(const char, Position, Colour, Colour, float);		// comprehensive constructor
	~Person();										// default deconstructor

	float getMovementDelay();
	char getIcon();
	WORD getAttribute();							// returns attribute
	bool canMoveIn(Grid*);							// moves player in a specified direction
	void move();									// moves player in a specified direction
	Node* facingIn(Grid*);
	Node* standingOn(Grid*);
};

#endif
