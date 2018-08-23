#ifndef POSITION_H
#define POSITION_H

#include <Windows.h>
#include <cmath>

# define M_PI 3.14159265358979323846

enum Direction { up, down, left, right };

class Position {
public:
	COORD coord;
	Direction facing;

	Position();
	Position(COORD, Direction);

	double distance(Position&);
	Direction directionOf(Position&);
};

bool operator==(const COORD &lhs, const COORD &rhs);

#endif
