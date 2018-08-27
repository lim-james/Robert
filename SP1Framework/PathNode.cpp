#include "PathNode.h"

PathNode::PathNode()
{
}

PathNode::PathNode(Position pos, Node *n, bool a(Node*))
	: Position(pos), node(n), action(a)
{
}


bool PathNode::perform()
{
	return action(node);
}