#ifndef SPLITSCREEN_HELPERS_H
#define SPLITSCREEN_HELPERS_H

#define WIDTH 120
#define HEIGHT 30

#include <cmath>

const struct SplitScreen {
	static const int width = WIDTH / 2;
	static const int height = HEIGHT;

	static const int paddingX = 1;
	static const int paddingY = 7;

	static const int centerX() { return width / 2; }
	static const int centerY() { return height / 2; }
	static const int diagonal() { return sqrt(pow(centerX(), 2.0) + pow(centerY(), 2.0)); }
} splitScreen;

#endif