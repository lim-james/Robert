#include "PathNode.h"

//--------------------------------------------------------------
// Purpose  : Default constructor.
//
// Input    : void 
// Output   : N.A.
//--------------------------------------------------------------
PathNode::PathNode()
{
}

//--------------------------------------------------------------
// Purpose  : Comprehensive constructor.
//			  Initialises the respective variables
//
// Input    : Position, Node, function pointer
//							  Input  : Node*
//							  Output : bool
// Output   : N.A.
//--------------------------------------------------------------
PathNode::PathNode(Position pos, Node *n, bool a(Node*))
	: Position(pos), node(n), action(a)
{
}

//--------------------------------------------------------------
// Purpose  : performs the action specified for this node.
//			  returns the outcome based on the action.
//
// Input    : void
// Output   : bool
//--------------------------------------------------------------
bool PathNode::perform()
{
	return action(node);
}