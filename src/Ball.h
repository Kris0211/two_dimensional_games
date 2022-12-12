#pragma once
#include <SDL.h>

#include "CollisionBody.h"
#include "Sprite.h"
#include "Vector2D.h"

class Ball : public CollisionBody
{
public:
	Ball(SDL_Renderer* renderer, Sprite* sprite, const Vector2D& position = Vector2D(0, 0), const Vector2D& velocity = Vector2D(1, 1));
	~Ball() override;

	void collide(bool separation = true, bool reflection = true) override;

	Vector2D getPosition() const;
	void setPosition(Vector2D position);
	void setScale(float scale);

private:
	SDL_Renderer* renderer;

	Sprite* ballSprite;

	float radius;
	float scale = 1.0f;

	Vector2D position;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
};
