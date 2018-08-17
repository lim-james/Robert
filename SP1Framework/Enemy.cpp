#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const char i, std::string file, Colour fc, Colour bc)
{
	std::ifstream ifs(file);
	ifs >> numberOfPositions;
	positions = new Position[numberOfPositions];
	for (int p = 0; p < numberOfPositions; ++p) {
		ifs >> positions[p].coord.X >> positions[p].coord.Y;
		char dir;
		ifs >> dir;
		switch (dir)
		{
			case 'U':
				positions[p].facing = up;
				break;
			case 'D':
				positions[p].facing = down;
				break;
			case 'L':
				positions[p].facing = left;
				break;
			case 'R':
			default:
				positions[p].facing = right;
				break;
		}
	}
	nextIndex = 1;

	position = positions[0];

	icon = i;
	foregroundColor = fc;
	backgroundColor = bc;
}

Enemy::~Enemy()
{
}

void Enemy::move() 
{
	Position &p = positions[nextIndex];
	double yDiff = -(p.coord.Y - position.coord.Y);
	double xDiff = p.coord.X - position.coord.X;
	
	if (xDiff == 0 && yDiff == 0)
	{
		this->position.facing = positions[nextIndex].facing;
		if (nextIndex < numberOfPositions - 1)
			nextIndex++;
		else
			nextIndex = 0;
		return;
	}

	position.facing = position.directionOf(p);

	Person::move();
}