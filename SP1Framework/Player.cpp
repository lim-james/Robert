#include "Player.h"

Player::Player() : openedInventory(false)
{
	for (int i = 0; i < 9; i++)
	{
		items[i] = State();
	}
}

Player::Player(const char i, Position p, Colour fc, Colour bc)
	: Person(i, p, fc, bc, 0.125), openedInventory(false)
{
	for (int i = 0; i < 9; i++)
	{
		items[i] = State();
	}
}

Player::~Player()
{
}

void Player::storeItem(State item)
{
	for (int i = 0; i < 8; i++)
	{
		if (items[i] == State())
		{
			items[i] = item;
			return;
		} // else tell user that inventory is full
	}

	items[itemIndex] = item;
	itemIndex++;
}

bool Player::hasItem(State item)
{
	for (int i = 0; i < 9; i++)
	{
		if (items[i] == item)
		{
			items[i] = State(); // removes item from inventory after usage
			return true;
		}
	}
	return false;
}
