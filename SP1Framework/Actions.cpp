#include "Actions.h"

void open(Node *n, char i) 
{
	n->icon = i;
	n->isBlocked = false;
}

void close(Node *n, char i) 
{
	n->icon = i;
	n->isBlocked = true;
}

void removeNode(Node *n)
{
	n->icon = ' ';
}

void onStove(Node *n)
{
	n->foregroundColour = red;
}

void offStove(Node *n)
{
	n->foregroundColour = black;
}