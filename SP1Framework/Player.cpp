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

void Player::storeItem(State item)
{
	items[itemIndex] = item;
	itemIndex++;
}

bool Player::hasItem(State item)
{
	for (int i = 0; i < 9; i++)
	{
		if (items[i] == item)
		{
			items[i] = State((char)32, false, true, (Colour)15, (Colour)15); // removes item from inventory after usage
			return true;
		}
	}
	return false;
}