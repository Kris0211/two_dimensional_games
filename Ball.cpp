#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer, Sprite* sprite, const Vector2D position, const Vector2D velocity)
{
	this->renderer = renderer;
	this->ballSprite = sprite;
	this->radius = sprite->getWidth() / 2.0f;
	this->position = position;
	this->velocity = velocity;
}

Ball::~Ball()
{
	renderer = nullptr;
	ballSprite->free();
	ballSprite = nullptr;
}

void Ball::move()
{
	position += velocity;
	touch();
	ballSprite->render(position.x, position.y, scale, renderer);
}

void Ball::touch()
{
	if ((position.x + radius) >= SCREEN_WIDTH || (position.x - radius) < 0.0)
	{
		printf("cholibka.x\n");
		velocity.x *= -1;
	}
	if ((position.y + radius) >= SCREEN_HEIGHT || (position.y - radius) < 0.0)
	{
		printf("cholibka.y\n");
		velocity.y *= -1;
	}
}


Vector2D Ball::getPosition() const { return position; }

Vector2D Ball::getVelocity() const { return velocity; }

void Ball::setPosition(const Vector2D position) { this->position = position; }

void Ball::setVelocity(const Vector2D velocity) { this->velocity = velocity; }

void Ball::setScale(const float scale) 
{ 
	this->scale = scale;
	this->radius *= scale;
}
