#pragma once
#include "Character.h"

class KeyboardPlayer : public Character
{
public:
	KeyboardPlayer(Sprite* spr, const Vector2D& pos, CollisionBody* col);

	void move(double deltaTime) override;
};
