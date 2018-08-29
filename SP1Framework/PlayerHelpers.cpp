#include "PlayerHelpers.h"

void playerKeyEvents()
{

	for (int i = 0; i < 2; ++i)
	{
		Player *player = players()[i];
		unsigned int storey = player->currentStorey;
		Grid *g = grid(storey);

		player->somethingHappened = false;
		player->isSprinting = false;
		if (g_abKeyPressed[i % 2 ? K_RSHIFT : K_LSHIFT])
		{
			player->isSprinting = true;
		}

		if (g_abKeyPressed[i % 2 ? K_F12 : K_F1])
		{
			player->isGod = !player->isGod;
			player->somethingHappened = true;
		}

		if (player->bounceTime < g_dElapsedTime)
		{
			if (g_abKeyPressed[i % 2 ? K_UP : K_W])
				movePlayer(player, up);

			if (g_abKeyPressed[i % 2 ? K_LEFT : K_A])
				movePlayer(player, left);

			if (g_abKeyPressed[i % 2 ? K_DOWN : K_S])
				movePlayer(player, down);

			if (g_abKeyPressed[i % 2 ? K_RIGHT : K_D])
				movePlayer(player, right);

			if (g_abKeyPressed[i % 2 ? K_RETURN : K_SPACE])
				playerAction(player);

			if (g_abKeyPressed[i % 2 ? K_BACKSLASH : K_TAB])
			{
				player->openedInventory = !player->openedInventory;
				player->somethingHappened = true;
			}

		}

		if (player->somethingHappened)
		{
			player->bounceTime = g_dElapsedTime + player->getMovementDelay();
			if (player->standingOn(g)->getIcon() == (char)186)
			{
				if (player->currentStorey + 1 < level->numberOfStoreys)
					player->currentStorey++;
				else
					player->currentStorey = 0;
			}
		}
	}
}

void movePlayer(Player* player, Direction dir)
{
	if (player->isHidden)
		return;

	if (player->position.facing == dir)
	{
		if (player->canMoveIn(grid(player->currentStorey)))
		{
			player->move();
		}
	}
	else
	{
		player->position.facing = dir;
	}
	player->somethingHappened = true;
}

void playerAction(Player* player)
{
	Node* item = player->facingIn(grid(player->currentStorey));

	// door
	if (item->getState() == interactiveItems[CLOSET])
	{
		setLevel(L_AUNTYS_HOUSE);
	}
	// key
	else if (item->getState() == interactiveItems[KEY] && currentLevel == L_AUNTYS_HOUSE)
	{
		player->storeItem(item->getState());
		item->toggle();
	}
	// cupboard
	else if (item->getState() == interactiveItems[CLOSET] && currentLevel == L_AUNTYS_HOUSE)
	{
		player->isHidden = !player->isHidden;
	}
	// bed
	else if (attrs()[item->getState()] == "bed")
	{
		player->isHidden = !player->isHidden;
	}
	// unlock safe and take document
	else if ((item->getState() == interactiveItems[SAFE] && player->hasItem(interactiveItems[KEY])))
	{
		player->storeItem(interactiveItems[DOCUMENT]);
		item->toggle();
	}
	else if (attrs()[item->getState()] == "] open_door" ||
		attrs()[item->getState()] == "] close_door" ||
		attrs()[item->getState()] == "] open_window" ||
		attrs()[item->getState()] == "] close_window")
	{
		item->toggle();
		item->getPlayingSound() = !item->getPlayingSound();
		item->getPlayingSound() = !item->getPlayingSound();
	}
	// end game
	else if (attrs()[item->getState()] == "] sewer" && player->hasItem(interactiveItems[DOCUMENT]))
	{
		g_eGameState = S_LOSESCREEN;
		Sleep(1000);
	}
	else
	{
		if ((item->isPickable && item->toggled) || !item->isPickable)
			item->toggle();
	}

	player->somethingHappened = true;
}