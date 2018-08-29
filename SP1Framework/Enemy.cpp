#include "Enemy.h"

bool Enemy::A_STAR_NODE::operator==(A_STAR_NODE const&rhs) const
{
	return coord == rhs.coord;
}

Enemy::Enemy()
{
	state = normal; 
}

Enemy::Enemy(std::string file)
{
	state = normal;
	int i, fc, bc;
	std::ifstream ifs(file);
	ifs >> i >> fc >> bc;
	ifs >> isStationary;
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

	position = positions[0];
	targetPosition = positions[1];

	icon = i;
	foregroundColor = (Colour)fc;
	backgroundColor = (Colour)bc;
}

Enemy::~Enemy()
{
}

void Enemy::updateTargetPosition(Grid* grid)
{
	std::vector<Position> choices;
	for (int i = 0; i < numberOfPositions; ++i)
	{
		if (positions[i].distance(position) < 25)
		{
			choices.push_back(positions[i]);
		}
	}
	targetPosition = choices[rand() % choices.size()];
	generatePath(position, targetPosition, grid);
	nextPosition = 0;
}

void Enemy::generatePath(Position start, Position goal, Grid* grid)
{
	std::vector<A_STAR_NODE*> OPEN;
	std::vector<A_STAR_NODE*> CLOSED;

	A_STAR_NODE* startNode = new A_STAR_NODE;
	startNode->coord = start.coord;
	startNode->facing = start.facing;
	startNode->parent = startNode;
	startNode->g = 0;
	startNode->h = goal.distance(*startNode);
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
			
		if (curr->coord == goal.coord)
			break;

		for (int i = 0; i < 4; ++i)
		{
			A_STAR_NODE* neighbour = new A_STAR_NODE;
			
			neighbour->coord = curr->coord;
			neighbour->coord.X += x[i];
			neighbour->coord.Y += y[i];
			neighbour->facing = dir[i];

			neighbour->g = curr->g + 1;
			neighbour->h = goal.distance(*neighbour);// abs(goal.coord.Y - neighbour->coord.Y) + abs(goal.coord.X - neighbour->coord.X);
			neighbour->f = neighbour->g + neighbour->h;
			neighbour->parent = curr;

			COORD &c = neighbour->coord;

			if (c.X < 0 || c.X >= grid->size.X ||
				c.Y < 0 || c.Y >= grid->size.Y ||
				(grid->nodes[c.Y][c.X].getIsBlocked() &&
				grid->nodes[c.Y][c.X].getOtherState().isBlocked))
				continue;

			bool found = false;
			for (int close = 0; close < CLOSED.size(); ++close)
			{
				if (CLOSED[close]->coord == neighbour->coord)
				{
					found = true;
					break;
				}
			}
			if (found) continue;

			if (grid->nodes[c.Y][c.X].getIsBlocked() && !grid->nodes[c.Y][c.X].getOtherState().isBlocked)
			{
				neighbour->node = grid->nodes[c.Y] + c.X;
				neighbour->action = [](Node* n) {
					n->toggle();
					return !n->getIsBlocked();
				};
			}
			else 
			{
				neighbour->node = grid->nodes[0];
				neighbour->action = [](Node* n) { return false; };
			}

			int index = OPEN.size(); 
			for (int n = 0; n < OPEN.size(); ++n)
			{
				if (OPEN[n]->coord == neighbour->coord)
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
	while (!(endNode->coord == endNode->parent->coord))
	{
		getPath().push_back(*endNode);
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
				if (position.distance(pos) <= radius && playingSound)
				{
					if (!(targetPosition.coord == pos.coord))
					{
						int xD[4] = { 0, 0, 1, -1 };
						int yD[4] = { 1, -1, 0, 0 };
						Direction dir[4] = { up, down, left, right };
						int d = 0;
						for (int i = 0; i < 4; ++i)
						{
							if (!grid->nodes[y + yD[i]][x + xD[i]].getIsBlocked())
							{
								d = i;
								break;
							}
						}
						state = distracted;
						targetPosition = pos;
						targetPosition.coord.X += xD[d];
						targetPosition.coord.Y += yD[d];
						nextPosition = 0;
						
						generatePath(position, targetPosition, grid);
					}
					
				}
			}
		}
	}
}

void Enemy::move(Grid* grid) 
{
	if (targetPosition.coord == position.coord)
	{
		if (state == distracted)
		{
			int xD[4] = { 0, 0, 1, -1 };
			int yD[4] = { 1, -1, 0, 0 };
			Direction dir[4] = { down, up, right, left };
			for (int i = 0; i < 4; ++i)
			{
				if (dir[i] == targetPosition.facing)
				{
					grid->nodes[position.coord.Y + yD[i]][position.coord.X + xD[i]].toggle();
					break;
				}
			}
		}
		state = normal;
		updateTargetPosition(grid);
		return;
	}
	if (getPath()[nextPosition].perform())
	{
		return;
	}
	position = getPath()[nextPosition++];


}

void Enemy::chase(Person* p, Grid* grid)
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
}

std::vector<PathNode>& Enemy::getPath()
{
	return state == normal ? standardPath : chasePath;
}

int Enemy::getViewRange()
{
	return state == chasing ? viewRange * 5 : viewRange;
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

void Enemy::alert(unsigned int count, Enemy** enemies, Person* p, Grid* grid)
{
	int shortestDist = 0;
	Enemy *enemy;
	for (int e = 0; e < count; ++e)
	{
		Enemy *curr = enemies[e];
		if (!curr->isStationary)
		{
			int temp = position.distance(curr->position);
			if (shortestDist == 0)
			{
				shortestDist = temp;
			}
			else
			{
				if (shortestDist > temp)
				{
					shortestDist = temp;
					enemy = curr;
				}
			}
		}
	}
	enemy->chase(p, grid);
}