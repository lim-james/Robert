#ifndef ENEMY_H
#define ENEMY_H

#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "Person.h"
#include "Grid.h"

enum E_STATE { normal, chasing }; //do i need this even

class Enemy : public Person
{
	class A_STAR_NODE : public PathNode
	{
	public:
		int f, g, h;
		A_STAR_NODE *parent;

		bool operator==(A_STAR_NODE const&) const;
	};

public:
	int nextIndex, nextPosition, numberOfPositions, closestEnemy;
	E_STATE state;
	Position *positions, targetPosition;
	std::vector<PathNode> standardPath;
	std::vector<PathNode> chasePath;
	int viewRange;
	bool isStationary;

	Enemy();									// default constructor
	Enemy(std::string);	// comprehensive constructor
	~Enemy();									// default 

	void setTargetPosition(Position*, unsigned int);
	void generatePath(Position, Position, Grid*);

	float getMovementDelay();
	void check(Grid*);
	void move(Grid*);
	void chase(Person*, Grid*);
	std::vector<PathNode>& getPath();
	int getViewRange();
	bool isInView(Person*, Grid*);
	void alert(unsigned int, Enemy**, Person*, Grid*);
};

#endif