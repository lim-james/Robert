#include "PlayerVisionHelpers.h"

void renderPlayerVision(Player* p)
{
	float x1, y1, x2, y2;
	for (float a = 1; a <= 180; ++a)
	{
		double angle = a / 180.0 * M_PI;
		switch (p->position.facing)
		{
		case up:
			x1 = +1; y1 = -1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case down:
			x1 = +1; y1 = +1;
			x2 = -1; y2 = +1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * sin(angle), y1 * cos(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * sin(angle), y2 * cos(angle));
			break;
		case left:
			x1 = -1; y1 = +1;
			x2 = -1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		case right:
			x1 = +1; y1 = +1;
			x2 = +1; y2 = -1;
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x1 * cos(angle), y1 * sin(angle));
			renderPlayerVisionPoint(p, p->position.coord.X, p->position.coord.Y, x2 * cos(angle), y2 * sin(angle));
			break;
		}
	}
}

void renderPlayerVisionPoint(Player* player, float x, float y, float xDiff, float yDiff)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	COORD c;
	c.X = x + xDiff;
	c.Y = y + yDiff;
	Node &n = g->nodes[c.Y][c.X];
	if (c.X < 0 || c.X >= g->size.X ||
		c.Y < 0 || c.Y >= g->size.Y)
		return;

	n.seen = true;
	if (!n.getIsSeeThrough() || sqrt(pow(player->position.coord.X - c.X, 2.0) + pow(player->position.coord.Y - c.Y, 2.0)) >= splitScreen.height - 2 * splitScreen.paddingY)
		return;
	renderPlayerVisionPoint(player, x + xDiff, y + yDiff, xDiff, yDiff);
}