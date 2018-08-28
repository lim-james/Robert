#ifndef ENEMY_VISION_HELPERS_H
#define ENEMY_VISION_HELPERS_H

#include "RenderPointHelpers.h"
#include "MathHelpers.h"

void renderEnemyVision(Enemy*, Player*);	// renders enemy's vision
void renderEnemyVisionPoint(Enemy*, COORD, short, short, Player*);	// renders enemy's view points

#endif