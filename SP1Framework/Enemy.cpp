#include "Enemy.h"


bool Enemy::A_STAR_NODE::operator==(A_STAR_NODE const&rhs) const
{
	return pos.coord == rhs.pos.coord;
}

Enemy::Enemy()
{
	state = normal;
}

Enemy::Enemy(const char i, std::string file, Colour fc, Colour bc)
{
	state = normal;
	std::ifstream ifs(file);
	ifs >> viewRange;
	ifs >> numberOfPositions >> movementDelay;
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
	nextPosition = 1;
	nextIndex = 1;

	position = positions[0];
	targetPosition = positions[nextIndex];

	icon = i;
	foregroundColor = fc;
	backgroundColor = bc;
}

Enemy::~Enemy()
{
}

void Enemy::generatePath(Position start, Position goal, Grid* grid)
{
	std::vector<A_STAR_NODE*> OPEN;
	std::vector<A_STAR_NODE*> CLOSED;

	A_STAR_NODE* startNode = new A_STAR_NODE;
	startNode->pos = start;
	startNode->parent = startNode;
	startNode->g = 0;
	startNode->h = pow(goal.distance(startNode->pos), 2.0); //abs(goal.coord.Y - startNode->pos.coord.Y) + abs(goal.coord.X - startNode->pos.coord.X);
	startNode->f = startNode->g + startNode->h;

	OPEN.push_back(startNode);

	int x[4] = { 0, 0, 1, -1 };
	int y[4] = { 1, -1, 0, 0 };
	Direction dir[4] = { down, up, right, left };

	while (!OPEN.empty())
	{
		int index = 0;
		A_STAR_NODE* curr = OPEN[0];
		for (int i = 1; i < OPEN.size(); ++i)
		{
			if (OPEN[i]->f < curr->f || (OPEN[i]->f == curr->f && OPEN[i]->h < curr->h))
			{
				curr = OPEN[i];
				index = i;
			} 
		}
		OPEN.erase(OPEN.begin() + index);
		CLOSED.push_back(curr);

		if (curr->pos.coord == goal.coord)
			break;

		for (int i = 0; i < 4; ++i)
		{
			A_STAR_NODE* neighbour = new A_STAR_NODE;
			neighbour->pos = curr->pos;
			neighbour->pos.coord.X += x[i];
			neighbour->pos.coord.Y += y[i];
			neighbour->pos.facing = dir[i];

			neighbour->g = curr->g + 1;
			neighbour->h = abs(goal.coord.Y - neighbour->pos.coord.Y) + abs(goal.coord.X - neighbour->pos.coord.X);
			neighbour->f = neighbour->g + neighbour->h;
			neighbour->parent = curr;

			COORD &c = neighbour->pos.coord;

			if (c.X < 0 || c.X >= grid->size.X ||
				c.Y < 0 || c.Y >= grid->size.Y ||
				(grid->nodes[c.Y][c.X].getIsBlocked() &&
				grid->nodes[c.Y][c.X].getOtherState().isBlocked) || 
				std::find(CLOSED.begin(), CLOSED.end(), neighbour) != CLOSED.end())
				continue;

			int index = OPEN.size();
			for (int n = 0; n < OPEN.size(); ++n)
			{
				if (OPEN[n]->pos.coord == neighbour->pos.coord)
				{
					index = n;
					break;
				}
			}

			if (index != OPEN.size())
			{
				if (neighbour->g < OPEN[index]->g)
				{
					OPEN[index] = neighbour;
				}
			}
			else
			{
				OPEN.push_back(neighbour);
			}
		}
	}

	A_STAR_NODE *endNode = CLOSED[CLOSED.size() - 1];
	getPath().clear();
	while (!(endNode->pos.coord == endNode->parent->pos.coord))
	{
		getPath().push_back(endNode->pos);
		endNode = endNode->parent;
	}
	std::reverse(getPath().begin(), getPath().end());
}

float Enemy::getMovementDelay()
{
	return state == chasing ? movementDelay / 2.0 : movementDelay;
}

void Enemy::check(Grid* grid)
{
	for (SHORT y = 0; y < grid->size.Y; y++)
	{
		for (SHORT x = 0; x < grid->size.X; x++)
		{
			int radius = grid->nodes[y][x].getState().soundRadius;
			bool playingSound = grid->nodes[y][x].getPlayingSound();
			if (radius != 0)
			{
				Position pos({x,y}, left);
				if (position.distance(pos) <= radius && playingSound == 1)
				{
					targetPosition = pos;
				}
			}
		}
	}
}

void Enemy::move(Grid* grid) 
{
	if (targetPosition.coord == position.coord)
	{
		if (targetPosition.coord == positions[nextIndex].coord)
		{
			this->position.facing = positions[nextIndex].facing;
			if (nextIndex < numberOfPositions - 1)
			{
				nextIndex++;
				nextPosition = 0;
			}
			else
			{
				nextIndex = 0;
			}
			generatePath(position, positions[nextIndex], grid);
			return;
		}
		else
		{
			state = normal;
			targetPosition = positions[nextIndex];
			nextPosition = 0;
			generatePath(position, targetPosition, grid);
			return;
		}
	}

	position = getPath()[nextPosition++];
}

bool Enemy::chase(Person* p, Grid* grid)
{
	state = chasing;
	if (!(targetPosition.coord == p->position.coord))
	{
		nextPosition = 0;
		targetPosition = p->position;
		generatePath(position, targetPosition, grid);
	}
	move(grid);
	position.facing = position.directionOf(p->position);
	return position.coord == p->position.coord;
}

std::vector<Position>& Enemy::getPath()
{
	return state == normal ? standardPath : chasePath;
}

int Enemy::getViewRange()
{
	switch (state)
	{
	case normal:
		return viewRange;
	case chasing:
		return viewRange * 5;
	}
}

bool Enemy::isInView(Person* p, Grid* grid)
{
	if (position.directionOf(p->position) == position.facing)
	{
		double d = position.distance(p->position);
		double xDiff = p->position.coord.X - position.coord.X;
		double yDiff = p->position.coord.Y - position.coord.Y;
		double m = yDiff / xDiff;
		double c = m * -position.coord.X + position.coord.Y;

		if (d <= getViewRange())
		{
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
				if (!grid->nodes[(int)y][(int)x].getIsSeeThrough())
					return false;
			}
			return true;
		}
	}
	return false;
}

bool Enemy::cameraSight()
{

}