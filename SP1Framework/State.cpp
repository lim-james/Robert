#include "State.h"

State::State()
	: icon(' '), isBlocked(false), foregroundColour(black), backgroundColour(black)
{
}

State::State(char i, bool b, Colour fc, Colour bc)
	: icon(i), isBlocked(b), foregroundColour(fc), backgroundColour(bc)
{
}