#include "Enemy.h"


bool Enemy::A_STAR_NODE::operator==(A_STAR_NODE const&rhs) const
{
	return pos.coord == rhs.pos.coord;
}

void Enemy::generatePath(Position start, Position goal, Grid* grid)
{
	std::deque<A_STAR_NODE*> OPEN;
	std::deque<A_STAR_NODE*> CLOSED;

	A_STAR_NODE* startNode = new A_STAR_NODE;
	startNode->pos = start;
	startNode->parent = startNode;
	startNode->g = 0;
	startNode->h = abs(goal.coord.Y - startNode->pos.coord.Y) + abs(goal.coord.X - startNode->pos.coord.X);
	startNode->f = startNode->g + startNode->h;

	OPEN.push_back(startNode);

	int x[4] = { 0, 0, 1, -1 };
	int y[4] = { 1, -1, 0, 0 };

	while (true)
	{
		std::sort(OPEN.begin(), OPEN.end(), [](A_STAR_NODE *lhs, A_STAR_NODE *rhs)
		{
			return lhs->f < rhs->f;
		});
		A_STAR_NODE* curr = OPEN[0];
		OPEN.pop_front();
		CLOSED.push_back(curr);

		if (curr->pos.coord == goal.coord)
			break;

		for (int i = 0; i < 4; ++i)
		{
			A_STAR_NODE* neighbour = new A_STAR_NODE;
			neighbour->pos = curr->pos;
			neighbour->pos.coord.X += x[i];
			neighbour->pos.coord.Y += y[i];

			neighbour->g = curr->g + 1;
			neighbour->h = abs(goal.coord.Y - neighbour->pos.coord.Y) + abs(goal.coord.X - neighbour->pos.coord.X);
			neighbour->f = neighbour->g + neighbour->h;
			neighbour->parent = curr;

			if (curr->pos.coord.Y <= 0 || curr->pos.coord.Y >= grid->size.Y ||
				curr->pos.coord.X <= 0 || curr->pos.coord.X >= grid->size.X ||
				grid->nodes[neighbour->pos.coord.Y][neighbour->pos.coord.X].getIsBlocked() ||
				std::find(CLOSED.begin(), CLOSED.end(), neighbour) != CLOSED.end())
				continue;


			if (std::find(OPEN.begin(), OPEN.end(), neighbour) != OPEN.end())
			{
				auto node = std::find(OPEN.begin(), OPEN.end(), neighbour);
				unsigned int index = std::distance(OPEN.begin(), node);
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
	getPath()->clear();
	while (!(endNode->pos.coord == endNode->parent->pos.coord))
	{
		getPath()->push_back(endNode->pos);
		endNode = endNode->parent;
	}
}

Enemy::Enemy()
{
	state = normal;
}

Enemy::Enemy(const char i, std::string file, Colour fc, Colour bc)
{
	state = normal;
	std::ifstream ifs(file);
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

void Enemy::check(Grid* grid)
{
	for (SHORT y = 0; y < grid->size.Y; y++)
	{
		for (SHORT x = 0; x < grid->size.X; x++)
		{
			int radius = grid->nodes[y][x].getState().soundRadius;
			if (radius != 0)
			{
				Position pos({x,y}, left);
				if (position.distance(pos) <= radius)
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
				nextPosition = 1;
			}
			else
			{
				nextIndex = 0;
			}
			//generatePath(position, positions[nextIndex], grid);
			return;
		}
		else
		{
			targetPosition = positions[nextIndex];
			//generatePath(position, targetPosition, grid);
			return;
		}
	}

	position.facing = position.directionOf(targetPosition);//getPath()->at(nextPosition));

	Person::move();
}

bool Enemy::chase(Person* p, Grid* grid)
{
	state = chasing;
	if (!(targetPosition.coord == p->position.coord))
	{
		targetPosition = p->position;
		//generatePath(position, targetPosition, grid);
	}
	move(grid);
	return position.coord == p->position.coord;
}

std::vector<Position>* Enemy::getPath()
{
	return state == normal ? standardPath : chasePath;
}