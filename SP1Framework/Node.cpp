#include "Node.h"

Node::Node() 
	: icon(' '), isBlocked(false), foregroundColor(white), backgroundColor(black)
{
}

Node::Node(const char i, bool b, Colour fc, Colour bc) 
	: icon(i), isBlocked(b), foregroundColor(fc), backgroundColor(bc)
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
	return this->foregroundColor + this->backgroundColor * 16;
}