#include "Player.h"

//--------------------------------------------------------------
// Purpose  : Default constrcutor. (Sets all items in inventory to empty state)
//
// Input    : void
// Output   : void
//--------------------------------------------------------------
Player::Player() : openedInventory(false)
{
	for (int i = 0; i < 9; i++)
	{
		items[i] = State();
	}
}

//--------------------------------------------------------------
// Purpose  : Default constructor. (Sets all items in inventory to empty state)
//
// Input    : const char(icon), Position, Colour (foreground colour), Colour (background colour) 
// Output   : void
//--------------------------------------------------------------
Player::Player(const char i, Position p, Colour fc, Colour bc)
	: Person(i, p, fc, bc, 0.075), openedInventory(false)
{
	for (int i = 0; i < 9; i++)
	{
		items[i] = State();
	}
}

//--------------------------------------------------------------
// Purpose  : Default destructor.
//
// Input    : void 
// Output   : void
//--------------------------------------------------------------
Player::~Player()
{
}

//--------------------------------------------------------------
// Purpose  : Storing item in empty spaces in inventory
//
// Input    : State (item being stored) 
// Output   : void
//--------------------------------------------------------------
void Player::storeItem(State item)
{
	for (int i = 0; i < 8; i++)
	{
		if (items[i].icon == ' ')
		{
			items[i] = item;
			return;
		} // else tell user that inventory is full
	}
}

//--------------------------------------------------------------
// Purpose  : Checking if player has an item
//
// Input    : State (checking what items player has) 
// Output   : bool
//--------------------------------------------------------------
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