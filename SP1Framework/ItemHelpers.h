#ifndef ITEM_HELPERS_H
#define ITEM_HELPERS_H

#include "State.h"

enum ITEMS
{
	DOOR,
	CLOSET,
	KEY,
	SAFE,
	DOCUMENT,
	WALL,
	ITEM_COUNT
};

const State interactiveItems[ITEM_COUNT] = {
	State((char)178, true, false, (Colour)8, (Colour)15, 40, false),
	State((char)254, true, false, (Colour)3, (Colour)15, 0, false),
	State((char)157, true, true, (Colour)11, (Colour)5, 0, false),
	State((char)240, true, true, (Colour)13, (Colour)15, 0, false),
	State((char)77, true, true, (Colour)0, (Colour)15, 0, false),
	State((char)87, true, false, (Colour)8, (Colour)8, 0, false)
};

#endif