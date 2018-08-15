#include "Actions.h"

void open(Node *n, char i) {
	n->icon = i;
	n->isBlocked = false;
}

void close(Node *n, char i) {
	n->icon = i;
	n->isBlocked = true;
}