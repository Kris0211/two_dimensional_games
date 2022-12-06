#include "Ball.h"

Ball::Ball(SDL_Renderer* renderer, Sprite* sprite, const Vector2D &position, const Vector2D &velocity)
{
	this->renderer = renderer;
	this->ballSprite = sprite;
	this->radius = static_cast<float>(sprite->getWidth()) / 2.0f;
	this->position = position;
	this->velocity = velocity;
}

Ball::~Ball()
{
	ballSprite->free();
	ballSprite = nullptr;
	renderer = nullptr;
}

void Ball::move(double deltaTime)
{
	position += velocity * 2;// *deltaTime;
}

void Ball::collide(const bool separation, const bool reflection)
{
	// touch grass err I mean walls
	if (position.x + radius >= SCREEN_WIDTH)
	{
		velocity.x *= -1;
		position.x = static_cast<float>(SCREEN_WIDTH) - radius;
	}

	if (position.x - radius < 0.0)
	{
			velocity.x *= -1;
			position.x = radius;
	}

	if (position.y + radius >= SCREEN_HEIGHT)
	{
		velocity.y *= -1;
		position.y = static_cast<float>(SCREEN_HEIGHT) - radius;
	}

	if (position.y - radius < 0.0)
	{
		velocity.y *= -1;
		position.y = radius;
	}

	// touch balls ._.
	/*for (Ball* ball : balls)
	{
		if (ball == this) continue;  // Don't collide with yourself

		Vector2D vec = (position - ball->position);
		const float dist = vec.length();
		if (dist < this->radius + ball->radius)
		{
			vec.normalize();
			if (separation) // separate balls o.o
			{
				position += vec * (ball->radius - dist * 0.5f);
				ball->setPosition(ball->position - vec * (radius - dist * 0.5f));
			}

			if (reflection) // reflect balls :|
			{
				velocity = velocity - vec * Vector2D::dotProduct(velocity, vec) * 2.0f;
				vec *= -1.0f;
				ball->setVelocity(ball->velocity - vec * Vector2D::dotProduct(ball->velocity, vec) * 2.0f);
			}
		}

	}*/

}

void Ball::render() const
{
	ballSprite->render(static_cast<int>(position.x), static_cast<int>(position.y), scale, renderer);
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