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
// Purpose  : Returns whether player is facing specified object.
//			  And performs the callback action with the new char
// Input    : char, Grid*, callback, char
// Output   : bool
//--------------------------------------------------------------
bool Person::ifFacing(char c, Grid* grid, void action(Node*, char), char icon)
{
	COORD &p = position.coord;
	Node *n = grid->nodes[p.Y] + p.X;

	switch (position.facing)
	{
		case up:
			if (p.Y > 0 && grid->nodes[p.Y - 1][p.X].icon == c)
				n = grid->nodes[p.Y - 1] + p.X;
			else
				return false;
			break;
		case down:
			if (p.Y < grid->size.Y - 1 && grid->nodes[p.Y + 1][p.X].icon == c)
				n = grid->nodes[p.Y + 1] + p.X;
			else
				return false;
			break;
		case left:
			if (p.X > 0 && grid->nodes[p.Y][p.X - 1].icon == c)
				n = grid->nodes[p.Y] + p.X - 1;
			else
				return false;
			break;
		case right:
			if (p.X < grid->size.X - 1 && grid->nodes[p.Y][p.X + 1].icon == c)
				n = grid->nodes[p.Y] + p.X + 1;
			else
				return false;
			break;
		default:
			return false;
	}
	
	action(n, icon);
	return true;
}

//--------------------------------------------------------------
// Purpose  : Returns what player is facing.
// Input    : Grid*
// Output   : cHar
//--------------------------------------------------------------
char Person::facingIn(Grid* grid)
{
	switch (position.facing)
	{
	case up:
		return grid->nodes[position.coord.Y - 1][position.coord.X].icon;
	case down:
		return grid->nodes[position.coord.Y + 1][position.coord.X].icon;
	case left:
		return grid->nodes[position.coord.Y][position.coord.X - 1].icon;
	case right:
		return grid->nodes[position.coord.Y][position.coord.X + 1].icon;
	}
}