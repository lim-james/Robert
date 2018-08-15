 #ifndef POSITION_H
#define POSITION_H

#include <Windows.h>

enum Direction { up, down, left, right };

struct Position {
	COORD coord;
	Direction facing;

	Position();
	Position(COORD, Direction);
};

#endif
