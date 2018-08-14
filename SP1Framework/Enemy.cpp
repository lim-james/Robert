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
	currentIndex = 0;

	icon = i;
	foregroundColor = fc;
	backgroundColor = bc;
}

Enemy::~Enemy()
{
}

void Enemy::move() 
{
	if (currentIndex < numberOfPositions - 1)
		currentIndex++;
	else
		currentIndex = 0;
	position = positions[currentIndex];
}