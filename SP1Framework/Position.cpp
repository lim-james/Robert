#include "Position.h"

//--------------------------------------------------------------
// Purpose  : Get position (coord and direction facing)
//
// Input    : void 
// Output   : N.A
//--------------------------------------------------------------
Position::Position() 
	: coord(COORD()), facing(up)
{
}

Position::Position(COORD c, Direction d)
	: coord(c), facing(d)
{
}

//--------------------------------------------------------------
// Purpose  : Distance frm positon
//
// Input    : bool 
// Output   : double
//--------------------------------------------------------------
double Position::distance(Position &p)
{
	return sqrt(pow(p.coord.X - coord.X, 2) + pow(p.coord.Y - coord.Y, 2));
}

//--------------------------------------------------------------
// Purpose  : Range and angle of view frm direction
//
// Input    : void 
// Output   : N.A.
//--------------------------------------------------------------
Direction Position::directionOf(Position &p)
{
	double yDiff = -(p.coord.Y - coord.Y);
	double xDiff = p.coord.X - coord.X;

	double refAngle = std::atan(abs(yDiff) / abs(xDiff)) / M_PI * 180.0;

	if (xDiff >= 0)
	{
		if (yDiff < 0)
		{
			refAngle = 360 - refAngle;
		}
	}
	else
	{
		if (yDiff > 0)
		{
			refAngle = 180 - refAngle;
		}
		else
		{
			refAngle = 180 + refAngle;
		}
	}

	if (refAngle >= 45.0 && refAngle < 135.0)
		return up;
	else if (refAngle >= 135.0 && refAngle < 225.0)
		return left;
	else if (refAngle >= 225.0 && refAngle < 315.0)
		return down;
	else
		return right;
}

bool operator==(const COORD &lhs, const COORD &rhs)
{
	return lhs.X == rhs.X && lhs.Y == rhs.Y;
}