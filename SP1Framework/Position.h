#ifndef POSITION_H
#define POSITION_H

#include <Windows.h>
#include <cmath>

# define M_PI 3.14159265358979323846

enum Direction { up, down, left, right };

struct Position {
	COORD coord;
	Direction facing;

	Position();
	Position(COORD, Direction);

	double distance(Position&);
	Direction directionOf(Position&);
};

#endif
