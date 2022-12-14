#pragma once
#include "CollisionBody.h"
#include "../Math/Vector2D.h"

class Box : public CollisionBody
{
public:
	Box(SDL_Renderer* renderer, const Vector2D &rect, const Vector2D &position = Vector2D(0, 0));
	~Box() override;

	void collide(bool separation = true, bool reflection = true) override;


};