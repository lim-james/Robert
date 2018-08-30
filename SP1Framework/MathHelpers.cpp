#include "MathHelpers.h"

//--------------------------------------------------------------
// Purpose  : Get X and Y coordinates to calculate distance
//
// Input    : int
// Output   : int
//--------------------------------------------------------------
int distance(COORD a, COORD b)
{
	return sqrt(pow(a.X - b.X, 2.0) + pow(a.Y - b.Y, 2.0));
}