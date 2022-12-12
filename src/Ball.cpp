#include "Ball.h"

#include "Box.h"
#include "CollisionManager.h"

Ball::Ball(SDL_Renderer* renderer, Sprite* sprite, const Vector2D &position, const Vector2D &velocity)
{
	this->renderer = renderer;
	this->ballSprite = sprite;
	this->radius = static_cast<float>(sprite->getWidth()) / 2.0f;
	this->position = position;
}

Ball::~Ball()
{
	ballSprite->free();
	ballSprite = nullptr;
	renderer = nullptr;
}

void Ball::collide(const bool separation, const bool reflection)
{
	Ball* ballCollider;
	Box* boxCollider;

	for (CollisionBody* collider : CollisionManager::colliders)
	{
		if (collider == this) continue;

		ballCollider = dynamic_cast<Ball*>(collider);
		if (ballCollider != nullptr)
		{
			//do stuff
		}
		else  //collider is a box
		{
			boxCollider = dynamic_cast<Box*>(collider);
			//do stuff
		}
	}

}

Vector2D Ball::getPosition() const { return position; }

void Ball::setPosition(const Vector2D position) { this->position = position; }

void Ball::setScale(const float scale) 
{ 
	this->scale = scale;
	this->radius *= scale;
}
