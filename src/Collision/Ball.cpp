#include "Ball.h"

#include "Box.h"
#include "CollisionManager.h"
#include "../Pawn/Character.h"

Ball::Ball(float radius, bool isRigid) : CollisionBody(isRigid, BALL), radius(radius) {}

Ball::Ball(const Vector2D &fixedPosition, float radius, bool isRigid) : CollisionBody(fixedPosition, isRigid, BALL) {}

void Ball::collide(const bool separation, const bool reflection)
{
	Ball* ballCollider;
	Box* boxCollider;

	for (CollisionBody* collider : CollisionManager::colliders)
	{
		if (collider == this) continue; //don't collide with self

		Vector2D colliderPos;
		Character* character = this->character;
		if (collider->character != nullptr)
		{
			colliderPos = collider->character->position;
		}
		else
		{
			colliderPos = collider->getFixedPosition();
		}

		if (collider->getBodyType() == BALL)
		{
			ballCollider = dynamic_cast<Ball*>(collider);
			
			Vector2D vec = (this->character->position - colliderPos);
			float dist = vec.length();
			if (dist < radius + ballCollider->getRadius())
			{
				vec.normalize();
				if (separation)
				{
					character->position += vec * (ballCollider->getRadius() - dist * 0.5);
					collider->character->position -= vec * (this->getRadius() - dist * 0.5);
				}

				if (reflection)
				{
					character->velocity = character->velocity - vec * Vector2D::dotProduct(character->velocity, vec) * 2.0;
					vec *= -1.0f;
					collider->character->velocity = ballCollider->character->velocity - vec * Vector2D::dotProduct(
						ballCollider->character->velocity, vec) * 2.0;
				}

				if (collider->character != nullptr) 
				{
					character->collision(collider->character);
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
					if (collider->isRigid() && collider->character != nullptr)
					{
						character->position -= vec * 0.5;
						collider->character->position += vec * 0.5;
					}
					else
					{
						character->position += vec;
					}
				}

				if (collider->character != nullptr) 
				{
					character->collision(collider->character);
				}
			}
		}
	}
}

float Ball::getRadius() const {	return radius; }
