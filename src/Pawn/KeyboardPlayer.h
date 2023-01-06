#pragma once
#include "Character.h"

class KeyboardPlayer : public Character
{
public:
	KeyboardPlayer(Sprite* sprite, const Vector2D& pos, CollisionBody* collider);

	void move(double deltaTime) override;
};

