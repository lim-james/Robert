#include "EnemyVisionHelpers.h"

//--------------------------------------------------------------
// Purpose  : Finding the point in which enemy's vision starts rendering
//
// Input    : Enemy*, Player* 
// Output   : void
//--------------------------------------------------------------
void renderEnemyVision(Enemy* e, Player* player)
{
	short x1, y1, x2, y2;
	switch (e->position.facing)
	{
	case up:
		x1 = +1; y1 = -1;
		x2 = -1; y2 = -1;
		break;
	case down:
		x1 = +1; y1 = +1;
		x2 = -1; y2 = +1;
		break;
	case left:
		x1 = -1; y1 = +1;
		x2 = -1; y2 = -1;
		break;
	case right:
		x1 = +1; y1 = +1;
		x2 = +1; y2 = -1;
		break;
	}
	renderEnemyVisionPoint(e, e->position.coord, x1, y1, player);
	renderEnemyVisionPoint(e, e->position.coord, x2, y2, player);
}

//--------------------------------------------------------------
// Purpose  : render Enemy vision
//
// Input    : Enemy*, Enemy COORD, X position being checked, Y position being checked, Player* 
// Output   : void
//--------------------------------------------------------------
void renderEnemyVisionPoint(Enemy* e, COORD c, short x, short y, Player* player)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	c.Y += y;
	c.X += x;
	if (distance(e->position.coord, c) > e->getViewRange() ||
		c.X < 0 || c.X >= g->size.X ||
		c.Y < 0 || c.Y >= g->size.Y ||
		!g->nodes[c.Y][c.X].getIsSeeThrough() ||
		!g->nodes[c.Y][c.X].seen)
		return;

	renderMapPoint(c, ' ', lightGrey * 17, player);

	renderEnemyVisionPoint(e, c, x, y, player);
}