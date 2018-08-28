#ifndef PLAYER_VISION_HELPERS_H
#define PLAYER_VISION_HELPERS_H

#include "SplitscreenHelpers.h"
#include "LevelHelpers.h"
#include "MathHelpers.h"

void renderPlayerVision(Player*);	// renders enemy's vision
void renderPlayerVisionPoint(Player*, float, float, float, float);	// renders enemy's view points

#endif