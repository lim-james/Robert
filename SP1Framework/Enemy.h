#ifndef ENEMY_H
#define ENEMY_H

#include <fstream>
#include <string>
#include "Person.h"

class Enemy : public Person
{
public:
	int nextIndex, numberOfPositions;
	Position *positions;

	Enemy();										// default constructor
	Enemy(const char, std::string, Colour, Colour);	// comprehensive constructor
	~Enemy();										// default 

	void move();
};

#endif