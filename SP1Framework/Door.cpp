#include "Door.h"

Door::Door()
{
}

Door::Door(const char c, Colour fc, Colour bc)
	: Node(c, true, fc, bc)
{
}


Door::~Door()
{
}

void openDoor(Node *n, char i) {
	Door *d = (Door*)n;
	d->icon = i;
	d->isBlocked = false;
}

void closeDoor(Node *n, char i) {
	Door *d = (Door*)n;
	d->icon = i;
	d->isBlocked = true;
}