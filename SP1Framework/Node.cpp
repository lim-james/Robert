#include "Node.h"

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

State &Node::getState()
{
	return toggled ? onState : offState;
}

char &Node::getIcon()
{
	return getState().icon;
}

bool &Node::getIsBlocked()
{
	return getState().isBlocked;
}

bool &Node::getIsSeeThrough()
{
	return getState().isSeeThrough;
}

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
	return getState().foregroundColour + getState().backgroundColour * 16;

}

void Node::toggle()
{
	toggled = !toggled;
}