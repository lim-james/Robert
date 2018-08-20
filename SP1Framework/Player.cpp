#include "Player.h"

Player::Player() : openedInventory(false)
{
}

Player::Player(const char i, Position p, Colour fc, Colour bc)
	: Person(i, p, fc, bc), openedInventory(false)
{
}

Player::~Player()
{
}
