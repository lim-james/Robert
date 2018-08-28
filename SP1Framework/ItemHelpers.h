#ifndef ITEM_HELPERS_H
#define ITEM_HELPERS_H

#include "State.h"

enum ITEMS
{
	CLOSET,
	ITEM_COUNT
};

const State iterativeItems[ITEM_COUNT] = {
	State((char)254, true, false, (Colour)3, (Colour)15, 0, false),
};

#endif