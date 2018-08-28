#include "RenderPersonHelpers.h"

void renderPlayers(Player* player)
{
	Player* other = player == player1() ? player2() : player1();

	if (other->currentStorey == player->currentStorey)
		renderPerson(other, player);
	renderPerson(player, player);
}

void renderEnemies(Player* player)
{
	unsigned int storey = player->currentStorey;
	for (int i = 0; i < numberOfEnemies(storey); ++i)
	{
		Enemy *enemy = enemies(storey)[i];
		if (!grid(storey)->nodes[enemy->position.coord.Y][enemy->position.coord.X].seen)
			continue;
		renderPerson(enemy, player);
	}
}

void renderPerson(Person* person, Player* player)
{
	renderMapPoint(person->position.coord, person->getIcon(), person->getAttribute(), player);
}