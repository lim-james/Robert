#ifndef ENEMY_H
#define ENEMY_H

#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "Person.h"
#include "Grid.h"

enum E_STATE { normal, chasing };

class Enemy : public Person
{
	class A_STAR_NODE
	{
	public:
		int f, g, h;
		Position pos;
		A_STAR_NODE *parent;

		bool operator==(A_STAR_NODE const&) const;
	};

public:
	int nextIndex, nextPosition, numberOfPositions;
	double movementDelay;
	E_STATE state;
	Position *positions, targetPosition;
	std::vector<Position>* standardPath;
	std::vector<Position>* chasePath;

	Enemy();										// default constructor
	Enemy(const char, std::string, Colour, Colour);	// comprehensive constructor
	~Enemy();										// default 

	void generatePath(Position, Position, Grid*);

	void check(Grid*);
	void move(Grid*);
	bool chase(Person*, Grid*);
	std::vector<Position>* getPath();
};

#endif