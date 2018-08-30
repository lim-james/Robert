#include "RenderPersonHelpers.h"

//--------------------------------------------------------------
// Purpose  : Render player onto viewport
//
// Input    : Player* 
// Output   : void
//--------------------------------------------------------------
void renderPlayers(Player* player)
{
	Player* other = player == player1() ? player2() : player1();

	if (other->currentStorey == player->currentStorey)
		renderPerson(other, player);
	renderPerson(player, player);
}

//--------------------------------------------------------------
// Purpose  : Render enemies based on the player rendering for
//			  Iterates through all enemies on the player's level
//
// Input    : Player* 
// Output   : void
//--------------------------------------------------------------
void renderEnemies(Player* player)
{
	unsigned int storey = player->currentStorey;
	for (unsigned int i = 0; i < numberOfEnemies(storey); ++i)
	{
		Enemy *enemy = enemies(storey)[i];
		if (!grid(storey)->nodes[enemy->position.coord.Y][enemy->position.coord.X].seen)
			continue;
		renderPerson(enemy, player);
	}
}

//--------------------------------------------------------------
// Purpose  : Render person into map visible in the viewport 
//
// Input    : Person* (being rendered), Player* (rendering for) 
// Output   : void
//--------------------------------------------------------------
void renderPerson(Person* person, Player* player)
{
	renderMapPoint(person->position.coord, person->getIcon(), person->getAttribute(), player);
}