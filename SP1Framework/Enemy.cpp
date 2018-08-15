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
				positions[p].facing = right;
				break;
			default:
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
	double yDiff = -(positions[nextIndex].coord.Y - position.coord.Y);
	double xDiff = positions[nextIndex].coord.X - position.coord.X;
	
	if (xDiff == 0 && yDiff == 0)
	{
		this->position.facing = positions[nextIndex].facing;
		if (nextIndex < numberOfPositions - 1)
			nextIndex++;
		else
			nextIndex = 0;
		return;
	}

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
		this->position.facing = up;
	else if (refAngle >= 135.0 && refAngle < 225.0)
		this->position.facing = left;
	else if (refAngle >= 225.0 && refAngle < 315.0)
		this->position.facing = down;
	else
		this->position.facing = right;

	Person::move();
}