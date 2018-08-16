#include "Node.h"

Node::Node() 
	: icon(' '), isBlocked(false), foregroundColour(white), backgroundColour(black), seen(false)
{
}

Node::Node(const char i, bool b, Colour fc, Colour bc) 
	: icon(i), isBlocked(b), foregroundColour(fc), backgroundColour(bc), seen(false)
{
}


Node::~Node()
{
}

//--------------------------------------------------------------
// Purpose  : When called it returns both the foreground and
//			  background colours in one attribute
// Input    : void
// Output   : WORD
//--------------------------------------------------------------
WORD Node::getAttribute()
{
	return this->foregroundColour + this->backgroundColour * 16;
}