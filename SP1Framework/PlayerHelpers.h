#ifndef PLAYER_HELPERS_H
#define PLAYER_HELPERS_H

#include "TimeHelpers.h"
#include "GameStateHelpers.h"
#include "KeyHelpers.h"
#include "ItemHelpers.h"
#include "LevelHelpers.h"

void playerKeyEvents();       // moves the character, collision detection, physics, etc
void movePlayer(Player*, Direction);	// moves a player in direction
void playerAction(Player*);	// check if player can perform action and performs it

#endif