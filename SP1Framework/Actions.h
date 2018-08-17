#ifndef ACTIONS_H
#define ACTIONS_H

#include "Node.h"
#include "Person.h"

void open(Node*, char);		// opens door / window
void close(Node*, char);	// closes door / window
void removeNode(Node*);
void onStove(Node*);
void offStove(Node*);

#endif
