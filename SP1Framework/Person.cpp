#include "Person.h"

Person::Person() 
	: position(Position()), icon(' '), foregroundColor(black), backgroundColor(white), isHidden(false)
{
}

Person::Person(const char i, Position p, Colour fc, Colour bc)
	: icon(i), position(p), foregroundColor(fc), backgroundColor(bc), isHidden(false)
{
}

Person::~Person()
{
}

//--------------------------------------------------------------
// Purpose  : When called it returns the icon
// Input    : void
// Output   : char
//--------------------------------------------------------------
char Person::getIcon()
{
	return isHidden ? ' ' : icon;
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
			return p.Y > 0 && !grid->nodes[p.Y - 1][p.X].getIsBlocked();
		case down:
			return p.Y < grid->size.Y - 1 && !grid->nodes[p.Y + 1][p.X].getIsBlocked();
		case left:
			return p.X > 0 && !grid->nodes[p.Y][p.X - 1].getIsBlocked();
		case right:
			return p.X < grid->size.X - 1 && !grid->nodes[p.Y][p.X + 1].getIsBlocked();
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
			return grid->nodes[position.coord.Y] + position.coord.X - (position.coord.X > 0);
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

bool Person::isInView(Person* p, Grid* grid)
{
	if (position.directionOf(p->position) == position.facing)
	{
		double d = position.distance(p->position);
		double xDiff = p->position.coord.X - position.coord.X;
		double yDiff = p->position.coord.Y - position.coord.Y;
		double m = yDiff / xDiff;
		double c = m * -position.coord.X + position.coord.Y;

		for (double i = 0; i < d; ++i) {
			double x, y;
			if ((int)xDiff == 0) {
				y = i / d * yDiff + position.coord.Y;
				x = position.coord.X;
			}
			else
			{
				x = xDiff * i / d + position.coord.X;
				y = m * x + c;
			}
			if (grid->nodes[(int)y][(int)x].getIsBlocked())
				return false;
		}
		return true;
	}
	return false;
}