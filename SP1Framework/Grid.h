#ifndef GRID_H
#define GRID_H

#include <fstream>
#include <map>
#include <string>

#include "Node.h"
#include "Door.h"

struct Grid
{
	COORD size;				// size of grid X and Y
	Node **nodes;			// dynamic array based on the size to store each node

	Grid();								// default constructor
	Grid(std::string, std::string);		// reads attributes and map from files
	~Grid();							// default deconstructor
};

#endif