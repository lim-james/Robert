#include "EnemyHelpers.h"

void refreshEnemies()
{
	if (player1()->currentStorey == player2()->currentStorey)
	{
		unsigned int storey = player1()->currentStorey;
		Grid *g = grid(storey);
		unsigned int num = numberOfEnemies(storey);
		Enemy** es = enemies(storey);

		for (int e = 0; e < num; ++e)
		{
			Enemy *enemy = es[e];
			Node* item = enemy->facingIn(g);

			if (g_dElapsedTime > enemy->bounceTime)
			{
				if (!player1()->isHidden && enemy->isInView(player1(), g) && !player1()->isGod)
				{
					if (!enemy->isStationary)
					{
						enemy->chase(player1(), g);
					}
					else
					{
						enemy->alert(num, es, player1(), g);
					}
				}
				else if (!player2()->isHidden && enemy->isInView(player2(), g) && !player2()->isGod)
				{
					if (!enemy->isStationary)
					{
						enemy->chase(player2(), g);
					}
					else
					{
						enemy->alert(num, es, player2(), g);
					}
				}
				else
				{
					if (enemy->position.coord == enemy->targetPosition.coord)
						enemy->updateTargetPosition(g);
					enemy->check(g);
					enemy->move(g);
				}
				enemy->bounceTime = enemy->getMovementDelay() + g_dElapsedTime;
			}
		}
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			Player *player = players()[i];
			unsigned int storey = player->currentStorey;

			Grid *g = grid(storey);
			unsigned int num = numberOfEnemies(storey);
			Enemy** es = enemies(storey);

			for (int e = 0; e < num; ++e)
			{
				Enemy *enemy = es[e];
				Node* item = enemy->facingIn(g);

				if (g_dElapsedTime > enemy->bounceTime)
				{
					if (!player->isHidden && enemy->isInView(player, g) && !player->isGod)
					{
						if (!enemy->isStationary)
						{
							enemy->chase(player, g);
						}
						else
						{
							enemy->alert(num, es, player, g);
						}
					}
					else
					{
						if (enemy->position.coord == enemy->targetPosition.coord)
							enemy->updateTargetPosition(g);
						enemy->check(g);
						enemy->move(g);
					}
					enemy->bounceTime = enemy->getMovementDelay() + g_dElapsedTime;
				}
			}
		}
	}

}