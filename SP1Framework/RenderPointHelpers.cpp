#include "RenderPointHelpers.h"

//--------------------------------------------------------------
// Purpose  : Render specified point in map into the viewport
//
// Input    : COORD   (position)
//			  char	  (character to be rendered)
//			  WORD	  (attribute of that point)
//			  Player* (player rendering for)
// Output   : void
//--------------------------------------------------------------
void renderMapPoint(COORD c, char i, WORD attr, Player *player)
{
	unsigned int storey = player->currentStorey;
	Grid *g = grid(storey);

	int sizeX = splitScreen.centerX();
	int sizeY = splitScreen.centerY();

	COORD pos = player->position.coord;

	if (pos.Y > sizeY - splitScreen.paddingY)
	{
		if (g->size.Y - pos.Y < sizeY - splitScreen.paddingY)
		{
			pos.Y = splitScreen.height - g->size.Y + pos.Y - splitScreen.paddingY;
			c.Y = splitScreen.height - g->size.Y + c.Y - splitScreen.paddingY;
		}
		else
		{
			c.Y -= pos.Y - sizeY;
			pos.Y = sizeY;
		}
	}
	else
	{
		pos.Y += splitScreen.paddingY;
		c.Y += splitScreen.paddingY;
	}

	if (pos.X > sizeX - splitScreen.paddingX)
	{
		if (g->size.X - pos.X < sizeX - splitScreen.paddingX)
		{
			pos.X = splitScreen.width - g->size.X + pos.X - splitScreen.paddingX;
			c.X = splitScreen.width - g->size.X + c.X - splitScreen.paddingX;
		}
		else
		{
			c.X -= pos.X - sizeX;
			pos.X = splitScreen.centerX();
		}
	}
	else
	{
		pos.X += splitScreen.paddingX;
		c.X += splitScreen.paddingX;
	}

	// check whether point is within viewport size
	if (c.X >= splitScreen.paddingX && c.X < splitScreen.width - splitScreen.paddingX &&
		c.Y >= splitScreen.paddingY && c.Y < splitScreen.height - splitScreen.paddingY)
		renderPoint(c, i, attr, player);
}

//--------------------------------------------------------------
// Purpose  : Render point onto respective side of splitscreen
//
// Input    : COORD   (position)
//			  char	  (character to be rendered)
//			  WORD	  (attribute of that point)
//			  Player* (player rendering for)
// Output   : void
//--------------------------------------------------------------
void renderPoint(COORD c, char i, WORD attr, Player *player)
{
	if (player == player2())
		c.X += splitScreen.width;
	g_Console.writeToBuffer(c, i, attr);
}

//--------------------------------------------------------------
// Purpose  : Render a line onto respective side of splitscreen
//
// Input    : COORD   (position)
//			  LPCSTR  (string to be rendered)
//			  WORD	  (attribute of that line)
//			  Player* (player rendering for)
// Output   : void
//--------------------------------------------------------------
void renderLine(COORD c, LPCSTR str, WORD attr, Player *player)
{
	if (player == player2())
		c.X += splitScreen.width;
	g_Console.writeToBuffer(c, str, attr);
}