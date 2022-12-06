#pragma once
#include <SDL.h>
#include <vector>

#include "CollisionBody.h"
#include "Sprite.h"
#include "Vector2D.h"

class Ball : public CollisionBody
{
public:
	Ball(SDL_Renderer* renderer, Sprite* sprite, const Vector2D& position = Vector2D(0, 0), const Vector2D& velocity = Vector2D(1, 1));
	~Ball();

	void move(double deltaTime);

	void collide(const std::vector<Ball*> &balls, bool separation = true, bool reflection = true);

	void render() const;

	Vector2D getPosition() const;
	Vector2D getVelocity() const;

	void setPosition(Vector2D position);
	void setVelocity(Vector2D velocity);
	void setScale(float scale);

private:
	SDL_Renderer* renderer;
	Sprite* ballSprite;
	float radius;
	float scale = 1.0f;
	Vector2D position;
	Vector2D velocity;

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
};
