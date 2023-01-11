#pragma once
#include "Character.h"

class ArrowsPlayer : public Character
{
public:

	float gravity = GRAVITY;

	ArrowsPlayer(Sprite* spr, const Vector2D& pos, CollisionBody* col);

	void move(double deltaTime) override;
};
