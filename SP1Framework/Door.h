#ifndef DOOR_H
#define DOOR_H

#include "Node.h"

struct Door: Node
{
	Door();												// default constructor
	Door(const char, Colour, Colour);		// comprehensive constructor
	~Door();											// default deconstructor
};

void openDoor(Node*, char);		// opens door
void closeDoor(Node*, char);	// closes door

#endif
