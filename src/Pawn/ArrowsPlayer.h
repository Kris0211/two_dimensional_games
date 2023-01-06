#pragma once
#include "Character.h"

class ArrowsPlayer : public Character
{
public:
	ArrowsPlayer(Sprite* sprite, const Vector2D& pos, CollisionBody* collider);

	void move(double deltaTime) override;
};

