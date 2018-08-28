#include "TimeHelpers.h"

double g_dElapsedTime = 0;
double g_dDeltaTime = 0;

double g_dBounceTime = 0; // this is to prevent key bouncing, so we won't trigger keypresses more than once