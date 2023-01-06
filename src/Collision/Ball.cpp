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
			colliderPos = collider->getCharacter()->getPosition();
		}
		else
		{
			colliderPos = collider->getFixedPosition();
		}

		if (collider->getBodyType() == BALL)
		{
			ballCollider = dynamic_cast<Ball*>(collider);
			
			Vector2D vec = (this->getCharacter()->getPosition() - colliderPos);
			float dist = static_cast<float>(vec.length());
			if (dist < radius + ballCollider->getRadius())
			{
				vec.normalize();
				if (separation)
				{
					character->getPosition() += vec * (ballCollider->getRadius() - dist * 0.5);
					collider->getCharacter()->getPosition() -= vec * (this->getRadius() - dist * 0.5);
				}

				if (reflection)
				{
					character->getVelocity() = character->getVelocity() - vec * Vector2D::dotProduct(character->getVelocity(), vec) * 2.0;
					vec *= -1.0f;
					collider->getCharacter()->getVelocity() = ballCollider->getCharacter()->getVelocity() - vec * Vector2D::dotProduct(ballCollider->getCharacter()->getVelocity(), vec) * 2.0;
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
			f = Vector2D::clamp(character->getPosition(), colliderPos - boxCollider->getRect() * 0.5, colliderPos + boxCollider->getRect() * 0.5);
			if ((character->getPosition() - f).length() < radius)
			{
				if (character->getPosition() != f)
				{
					Vector2D vec = (character->getPosition() - f).normal() * (radius - (character->getPosition() - f).length());
					if (collider->isRigid() && collider->getCharacter() != nullptr)
					{
						character->getPosition() -= vec * 0.5;
						collider->getCharacter()->getPosition() += vec * 0.5;
					}
					else
					{
						character->getPosition() += vec;
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
