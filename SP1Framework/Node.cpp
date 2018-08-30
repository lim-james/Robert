#include "Node.h"

//--------------------------------------------------------------
// Purpose  : Constructor
//			  Attributes of node.
//
// Input    : void 
// Output   : N.A.
//--------------------------------------------------------------
Node::Node() 
	: onState(State()), offState(State()), seen(false), toggled(false), isPickable(false)
{
}

Node::Node(State on, State off, bool s, bool t, bool isP) 
	: onState(on), offState(off), seen(s), toggled(t), isPickable(isP)
{
	
}


Node::~Node()
{
}

//--------------------------------------------------------------
// Purpose  : Get state if node is toggled
//
// Input    : bool 
// Output   : bool
//--------------------------------------------------------------
State &Node::getState()
{
	return toggled ? onState : offState;
}

State &Node::getOtherState()
{
	return toggled ? offState : onState;
}

//--------------------------------------------------------------
// Purpose  : Get icon of nodde
//
// Input    : void 
// Output   : char
//--------------------------------------------------------------
char &Node::getIcon()
{
	return getState().icon;
}

//--------------------------------------------------------------
// Purpose  : Get state if node is blocked
//
// Input    : bool 
// Output   : bool
//--------------------------------------------------------------
bool &Node::getIsBlocked()
{
	return getState().isBlocked;
}

//--------------------------------------------------------------
// Purpose  : Get state if node is see through
//
// Input    : bool 
// Output   : bool
//--------------------------------------------------------------
bool &Node::getIsSeeThrough()
{
	return getState().isSeeThrough;
}

//--------------------------------------------------------------
// Purpose  : Get state if node is playing sound
//
// Input    : bool 
// Output   : bool
//--------------------------------------------------------------
bool &Node::getPlayingSound()
{
	return getState().playingSound;
}

//--------------------------------------------------------------
// Purpose  : When called it returns both the foreground and
//			  background colours in one attribute
// Input    : void
// Output   : WORD
//--------------------------------------------------------------
WORD Node::getAttribute()
{
	return getState().getAttribute();

}

void Node::toggle()
{
	toggled = !toggled;
}