#pragma once
#include <SDL.h>

#include "CollisionBody.h"
#include "../Display/Sprite.h"
#include "../Math/Vector2D.h"

class Ball : public CollisionBody
{
public:
	Ball(SDL_Renderer* renderer, float radius, const Vector2D &position = Vector2D(0, 0));
	~Ball() override;

	void collide(bool separation = true, bool reflection = true) override;

	Vector2D getPosition() const;
	void setPosition(Vector2D position);
	void setScale(float scale);

private:
	SDL_Renderer* renderer;

	float radius = 10.0f;
	float scale = 1.0f;

	Vector2D position;
};
