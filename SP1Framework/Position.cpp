#include "Position.h"

Position::Position() 
	: coord(COORD()), facing(up)
{
}

Position::Position(COORD c, Direction d)
	: coord(c), facing(d)
{
}