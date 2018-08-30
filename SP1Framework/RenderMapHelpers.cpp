#include "RenderMapHelpers.h"

//--------------------------------------------------------------
// Purpose  : Render map around the player if seen
//
// Input    : Player* (rendering for) 
// Output   : void
//--------------------------------------------------------------
void renderMap(Player* player)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	COORD coord;
	COORD &pos = player->position.coord;
	int sizeX = splitScreen.centerX() - splitScreen.paddingX;
	int sizeY = splitScreen.centerY() - splitScreen.paddingY;
	for (int r = -sizeY; r < sizeY; ++r)
	{
		coord.Y = r + sizeY + splitScreen.paddingY;
		for (int c = -sizeX; c < sizeX; ++c)
		{
			coord.X = c + sizeX + splitScreen.paddingX;
			int y = r;
			if (pos.Y < sizeY)
				y += sizeY;
			else if (pos.Y > g->size.Y - sizeY)
				y += g->size.Y - sizeY;
			else
				y += pos.Y;

			int x = c;
			if (pos.X < sizeX)
				x += sizeX;
			else if (pos.X > g->size.X - sizeX)
				x += g->size.X - sizeX;
			else
				x += pos.X;

			Node &n = g->nodes[y][x];
			if (n.seen)
				renderPoint(coord, n.getIcon(), n.getAttribute(), player);
		}

	}
}