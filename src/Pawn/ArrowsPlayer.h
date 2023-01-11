#pragma once
#include "Character.h"

class ArrowsPlayer : public Character
{
public:
	ArrowsPlayer(Sprite* spr, const Vector2D& pos, CollisionBody* col);

	void move(double deltaTime) override;
};
