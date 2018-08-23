#include "State.h"

State::State()
	: icon(' '), isBlocked(false), foregroundColour(black), backgroundColour(black), soundRadius(0)
{
}

State::State(char i, bool b, bool s, Colour fc, Colour bc, int sr)
	: icon(i), isBlocked(b), isSeeThrough(s), foregroundColour(fc), backgroundColour(bc), soundRadius(sr)
{
}

bool State::operator==(const State &s) const
{
	return icon == s.icon && 
		isBlocked == s.isBlocked && 
		isSeeThrough == s.isSeeThrough && 
		foregroundColour == s.foregroundColour && 
		backgroundColour == s.backgroundColour && 
		soundRadius == s.soundRadius;
}

bool State::operator<(const State &s) const 
{
	return (int)icon < (int)s.icon;
}