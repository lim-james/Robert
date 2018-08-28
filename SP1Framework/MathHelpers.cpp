#include "MathHelpers.h"

int distance(COORD a, COORD b)
{
	return sqrt(pow(a.X - b.X, 2.0) + pow(a.Y - b.Y, 2.0));
}