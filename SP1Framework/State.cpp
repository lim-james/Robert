#include "State.h"

State::State()
	: icon(' '), isBlocked(false), foregroundColour(black), backgroundColour(black)
{
}

State::State(char i, bool b, bool s, Colour fc, Colour bc)
	: icon(i), isBlocked(b), isSeeThrough(s), foregroundColour(fc), backgroundColour(bc)
{
}

bool State::operator==(const State &s) const
{
	return icon == s.icon && isBlocked == s.isBlocked && foregroundColour == s.foregroundColour && backgroundColour == s.backgroundColour;
}

bool State::operator<(const State &s) const 
{
	return (int)icon < (int)s.icon;
}