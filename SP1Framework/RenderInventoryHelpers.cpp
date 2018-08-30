#include "RenderInventoryHelpers.h"

//--------------------------------------------------------------
// Purpose  : Render the inventory
//
// Input    : Player* 
// Output   : void
//--------------------------------------------------------------
void renderInventory(Player* player)
{
	char i[7][7] = {
		{ 201, 205, 203, 205, 203, 205, 187 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 204, 205, 206, 205, 206, 205, 185 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 204, 205, 206, 205, 206, 205, 185 },
	{ 186, 32, 186, 32, 186, 32, 186 },
	{ 200, 205, 202, 205, 202, 205, 188 }
	};
	i[1][1] = player->items[0].icon;
	i[1][3] = player->items[1].icon;
	i[1][5] = player->items[2].icon;
	i[3][1] = player->items[3].icon;
	i[3][3] = player->items[4].icon;
	i[3][5] = player->items[5].icon;
	i[5][1] = player->items[6].icon;
	i[5][3] = player->items[7].icon;
	i[5][5] = player->items[8].icon;

	for (SHORT y = 0; y < 7; y++)
	{
		for (SHORT x = 0; x < 7; x++)
		{
			renderInventoryPoint({ x, y }, i[y][x], white, player);
		}
	}
}

//--------------------------------------------------------------
// Purpose  : The point in which the inventory is being rendered at
//
// Input    : COORD, char (which is the icon), WORD, Player* 
// Output   : void
//--------------------------------------------------------------
void renderInventoryPoint(COORD c, char i, WORD attr, Player* player)
{
	renderPoint(c, i, attr, player);
}