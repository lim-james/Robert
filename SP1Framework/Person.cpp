#include "Person.h"

Person::Person() 
	: position(Position()), icon(' '), foregroundColor(black), backgroundColor(white)
{
}

Person::Person(const char i, Position p, Colour fc, Colour bc)
	: icon(i), position(p), foregroundColor(fc), backgroundColor(bc)
{
}

Person::~Person()
{
}

//--------------------------------------------------------------
// Purpose  : When called it returns both the foreground and
//			  background colours in one attribute
// Input    : void
// Output   : WORD
//--------------------------------------------------------------
WORD Person::getAttribute()
{
	return foregroundColor + backgroundColor * 16;
}

//--------------------------------------------------------------
// Purpose  : Returns whether player can move in direction 
//		      it's facing in the grid.
// Input    : Grid*
// Output   : bool
//--------------------------------------------------------------
bool Person::canMoveIn(Grid* grid) 
{
	COORD &p = position.coord;
	switch (position.facing)
	{
		case up:
			return p.Y > 0 && !grid->nodes[p.Y - 1][p.X].isBlocked;
		case down:
			return p.Y < grid->size.Y - 1 && !grid->nodes[p.Y + 1][p.X].isBlocked;
		case left:
			return p.X > 0 && !grid->nodes[p.Y][p.X - 1].isBlocked;
			break;
		case right:
			return p.X < grid->size.X - 1 && !grid->nodes[p.Y][p.X + 1].isBlocked;
		default:
			return false;
	}
}

//--------------------------------------------------------------
// Purpose  : Called to move the player. 
//            Direction is specified by the programmer
// Input    : Direction
// Output   : void
//--------------------------------------------------------------
void Person::move() 
{
	switch (position.facing)
	{
		case up:
			position.coord.Y--;
			break;
		case down:
			position.coord.Y++;
			break;
		case left:
			position.coord.X--;
			break;
		case right:
			position.coord.X++;
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
// Purpose  : Returns what player is facing.
// Input    : Grid*
// Output   : Node
//--------------------------------------------------------------
Node* Person::facingIn(Grid* grid)
{
	switch (position.facing)
	{
		case up:
			return grid->nodes[position.coord.Y - (position.coord.Y > 0)] + position.coord.X;
		case down:
			return grid->nodes[position.coord.Y + (position.coord.Y < grid->size.Y - 1)] + position.coord.X;
		case left:
			return grid->nodes[position.coord.Y] + position.coord.X - (position.coord.Y < 0);
		case right:
			return grid->nodes[position.coord.Y] + position.coord.X + (position.coord.X < grid->size.X - 1);
	}
}

// --------------------------------------------------------------
// Purpose  : Returns what player is standing on.
// Input    : Grid*
// Output   : Node
//--------------------------------------------------------------
Node* Person::standingOn(Grid* grid)
{
	return grid->nodes[position.coord.Y] + position.coord.X;
}