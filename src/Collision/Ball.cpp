#include "Ball.h"

#include "Box.h"
#include "CollisionManager.h"

Ball::Ball(float radius, bool isRigid) : CollisionBody(isRigid, BALL), radius(radius) {}

Ball::Ball(Vector2D fixedPosition, float radius, bool isRigid) : CollisionBody(fixedPosition, isRigid, BALL) {}

void Ball::collide(const bool separation, const bool reflection)
{
	Ball* ballCollider;
	Box* boxCollider;

	for (CollisionBody* collider : CollisionManager::colliders)
	{
		if (collider == this) continue; //don't collide with self

		Vector2D colliderPos;
		Character* character = this->getCharacter();
		if (collider->getCharacter() != nullptr)
		{
			colliderPos = collider->getCharacter()->position;
		}
		else
		{
			colliderPos = collider->getFixedPosition();
		}

		if (collider->getBodyType() == BALL)
		{
			ballCollider = dynamic_cast<Ball*>(collider);
			
			Vector2D vec = (this->getCharacter()->position - colliderPos);
			float dist = static_cast<float>(vec.length());
			if (dist < radius + ballCollider->getRadius())
			{
				vec.normalize();
				if (separation)
				{
					character->position += vec * (ballCollider->getRadius() - dist * 0.5);
					collider->getCharacter()->position -= vec * (this->getRadius() - dist * 0.5);
				}

				if (reflection)
				{
					character->velocity = character->velocity - vec * Vector2D::dotProduct(character->velocity, vec) * 2.0;
					vec *= -1.0f;
					collider->getCharacter()->velocity = ballCollider->getCharacter()->velocity - vec * Vector2D::dotProduct(ballCollider->getCharacter()->velocity, vec) * 2.0;
				}

				if (collider->getCharacter() != nullptr) 
				{
					character->collision(collider->getCharacter());
				}
			}
		}
		else // BodyType == BOX
		{
			boxCollider = dynamic_cast<Box*>(collider);

			Vector2D f;
			f = Vector2D::clamp(character->position, colliderPos - boxCollider->getRect() * 0.5, colliderPos + boxCollider->getRect() * 0.5);
			if ((character->position - f).length() < radius)
			{
				if (character->position != f)
				{
					Vector2D vec = (character->position - f).normal() * (radius - (character->position - f).length());
					if (collider->isRigid() && collider->getCharacter() != nullptr)
					{
						character->position -= vec * 0.5;
						collider->getCharacter()->position += vec * 0.5;
					}
					else
					{
						character->position += vec;
					}
				}

				if (collider->getCharacter() != nullptr) 
				{
					character->collision(collider->getCharacter());
				}
			}
		}
	}
}

float Ball::getRadius() const {	return radius; }
