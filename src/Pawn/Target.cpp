#include "Target.h"

#include <SDL_timer.h>
#include <iostream>

void Target::collision(Character* player)
{
	if (player->getName() == p1Name) kPlayerScore++;
	if (player->getName() == p2Name) aPlayerScore++;
	touched = true;
}

void Target::nextLevel()
{
	touched = false;
	if (lvl != 0) std::cout << kPlayerScore << " : " << aPlayerScore << "\n";
	if (kPlayerScore == 3)
	{
		std::cout << "PLAYER 1 WINS!\n";
		setupNewGame();
	}
	else if (aPlayerScore == 3)
	{
		std::cout << "PLAYER 2 WINS!\n";
		setupNewGame();
	}
	else
	{
		lvl++;
	}

	const int lvlSize = lvl + 8 + lvl%2;

	level->generateLevel(lvlSize);

	Vector2D playerSpawn = Vector2D(TILE_SIZE * (1 + 2 * (rand() % (lvlSize - 1))), TILE_SIZE * (1 + 2 * (rand() % (lvlSize - 1))));
	kPlayer->position = playerSpawn;

	playerSpawn = Vector2D(TILE_SIZE * (1 + 2 * (rand() % (lvlSize - 1))), TILE_SIZE * (1 + 2 * (rand() % (lvlSize - 1))));
	aPlayer->position = playerSpawn;

	position = Vector2D(TILE_SIZE * (lvlSize + 1 * rand() % 2) + 8, TILE_SIZE * (lvlSize + 1 * rand() % 2) + 8);

	SDL_Delay(1000);
}

void Target::setupNewGame()
{
	lvl = 1;
	kPlayerScore = 0;
	aPlayerScore = 0;
	level->generateLevel(10);
}
