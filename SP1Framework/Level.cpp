#include "Level.h"

//--------------------------------------------------------------
// Purpose  : Get the other files used in the game.
//			  Initialising the respective aspects of the level
//            
// Input    : File path (string) 
// Output   : N.A.
//--------------------------------------------------------------
Level::Level(std::string file) 
{
	std::ifstream ifs(file);
	std::string playersFile, attrFile, attrNameFile;
	ifs >> playersFile >> attrFile >> attrNameFile >> numberOfStoreys;

	initPlayers(playersFile);
	initAttrs(attrNameFile);
	storeys = new Grid*[numberOfStoreys];
	numberOfEnemies = new unsigned int[numberOfStoreys];
	enemies = new Enemy**[numberOfStoreys];

	for (int i = 0; i < numberOfStoreys; ++i)
	{
		std::string storeyFile;
		ifs >> storeyFile;
		storeys[i] = new Grid(attrFile, storeyFile);

		ifs >> numberOfEnemies[i];
		enemies[i] = new Enemy*[numberOfEnemies[i]];
		for (int e = 0; e < numberOfEnemies[i]; ++e)
		{
			std::string enemyFile;
			ifs >> enemyFile;
			enemies[i][e] = new Enemy(enemyFile);
		}
	}
	ifs >> players[0]->currentStorey >> players[1]->currentStorey;
}

//--------------------------------------------------------------
// Purpose  : Initialisation function for players
//            Initialize player with position
// Input    : string
// Output   : void
//--------------------------------------------------------------
void Level::initPlayers(std::string file)
{
	std::ifstream ifs(file);
	for (int i = 0; i < 2; ++i)
	{
		COORD c;
		ifs >> c.X >> c.Y;
		Direction facing;
		char dir;
		ifs >> dir;
		switch (dir)
		{
			case 'U':
				facing = up;
				break;
			case 'D':
				facing = down;
				break;
			case 'L':
				facing = left;
				break;
			case 'R':
				facing = right;
				break;
			default:
				break;
		}
		players[i] = new Player((char)178, Position(c, facing), i % 2 ? red : blue, white);
	}
}

//--------------------------------------------------------------
// Purpose  : Initialisation function for attributes
//            Initialize map with char and its name
// Input    : string
// Output   : void
//--------------------------------------------------------------
void Level::initAttrs(std::string file)
{
	std::ifstream ifs(file);
	int count;
	ifs >> count;
	for (int i = 0; i < count; ++i)
	{
		int icon, foregroundColour, backgroundColour, soundRadius;
		bool isBlocked, isSeeThrough, playingSound;
		std::string value;
		ifs >> icon >> isBlocked >> isSeeThrough >> foregroundColour >> backgroundColour >> soundRadius >> playingSound  >> value;
		State key((char)icon, isBlocked, isSeeThrough, (Colour)foregroundColour, (Colour)backgroundColour, soundRadius, playingSound);

		std::replace(value.begin(), value.end(), '_', ' ');
		attrs[key] = value;
	}
}