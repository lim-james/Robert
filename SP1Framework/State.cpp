#include "State.h"

State::State()
	: icon(' '), isBlocked(false), foregroundColour(black), backgroundColour(black), soundRadius(0), playingSound(0)
{
}

State::State(char i, bool b, bool s, Colour fc, Colour bc, int sr, bool ps)
	: icon(i), isBlocked(b), isSeeThrough(s), foregroundColour(fc), backgroundColour(bc), soundRadius(sr), playingSound(ps)
{
}

//--------------------------------------------------------------
// Purpose  : When called it returns both the foreground and
//			  background colours in one attribute
// Input    : void
// Output   : WORD
//--------------------------------------------------------------
WORD State::getAttribute()
{
	return foregroundColour + backgroundColour * 16;

}

bool State::operator==(const State &s) const
{
	return icon == s.icon && 
		isBlocked == s.isBlocked && 
		isSeeThrough == s.isSeeThrough && 
		foregroundColour == s.foregroundColour && 
		backgroundColour == s.backgroundColour && 
		soundRadius == s.soundRadius &&
		playingSound == s.playingSound;
}

bool State::operator<(const State &s) const 
{
	if ((int)icon < (int)s.icon)
		return true;
	else if ((int)icon == (int)s.icon)
		return foregroundColour < s.foregroundColour;
	return false;
}