#include "RenderMessageHelpers.h"

void renderMessage(std::string str, Player *p)
{
	COORD c;
	c.Y = splitScreen.paddingY / 2;

	for (c.X = 0; c.X < splitScreen.width; ++c.X)
		renderPoint(c, ' ', 0x00, p);

	if (p == player2())
	{
		if (str[0] == ']')
			str = "[enter" + str;
	}
	else
	{
		if (str[0] == ']')
			str = "[space" + str;
	}

	int length = str.length();
	c.X = (splitScreen.width - str.length()) / 2;
	renderLine(c, (LPCSTR)str.c_str(), white, p);
}