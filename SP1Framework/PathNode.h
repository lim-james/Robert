#ifndef PATHNODE_H
#define PATHNODE_H

#include "Node.h"
#include "Position.h"

class PathNode: public Position
{
public:
	Node *node;
	bool (*action)(Node*);

	PathNode();
	PathNode(Position, Node*, bool(Node*));

	bool perform();
};

#endif