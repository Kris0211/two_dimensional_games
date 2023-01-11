#pragma once
#include "Character.h"
#include "ArrowsPlayer.h"
#include "KeyboardPlayer.h"
#include "../Level/LevelGenerator.h"
#include  "../../Config.h"

class Target : public Character
{
public:
	KeyboardPlayer* kPlayer;
	ArrowsPlayer* aPlayer;
	LevelGenerator* level;
	int lvl = 0;
	int kPlayerScore = 0;
	int aPlayerScore = 0;
	bool touched = false;

	Target(Sprite* spr, CollisionBody* col, KeyboardPlayer* kp, ArrowsPlayer* ap, LevelGenerator* level)
	: Character(spr, Vector2D(TILE_SIZE * (11 * rand() % 2), TILE_SIZE * (11 * rand() % 2)) , col), kPlayer(kp), aPlayer(ap), level(level) {}

	void collision(Character* player) override;
	void nextLevel();

private:
	void setupNewGame();
};
