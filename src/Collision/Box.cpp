#include "Box.h"

#include "Ball.h"
#include "CollisionManager.h"
#include "../Pawn/Character.h"

Box::Box(const Vector2D &rect, bool isRigid) : CollisionBody(isRigid, BOX), rect(rect) {}

Box::Box(const Vector2D &fixedPos, const Vector2D &rect, bool isRigid) : CollisionBody(fixedPos, isRigid, BOX), rect(rect) {}

void Box::collide(bool separation, bool reflection)
{
	for (CollisionBody* collider : CollisionManager::colliders)
	{
		if (collider == this) continue;

		Vector2D colliderPos;
		if (collider->character)
		{
			colliderPos = collider->character->position;
		}
		else
		{
			colliderPos = collider->getFixedPosition();
		}

		if (collider->getBodyType() == BALL)
		{
			const Ball* ballCollider = dynamic_cast<Ball*>(collider);

			Vector2D f = Vector2D::clamp(colliderPos, character->position - rect * 0.5, character->position + rect * 0.5);
			if ((colliderPos - f).length() < ballCollider->getRadius())
			{
				if (collider->character->position != f)
				{
					Vector2D vec = (colliderPos - f).normal() * (ballCollider->getRadius() - (colliderPos - f).length());
					if (collider->isRigid() && collider->character != nullptr)
					{
						character->position -= vec * 0.5;
						collider->character->position += vec * 0.5;
					}
					else
					{
						character->position -= vec;
					}
				}

				if (collider->character != nullptr)
				{
					character->collision(collider->character);
				}
				else
				{
					character->collision();
				}
			}
		}
		else // BodyType == BOX
		{
			const Box* boxCollider = dynamic_cast<Box*>(collider);
			const float left = character->position.x + rect.x * 0.5 - (colliderPos.x - boxCollider->getRect().x * 0.5);
			const float right = colliderPos.x + boxCollider->getRect().x * 0.5 - (character->position.x - rect.x * 0.5);
			const float top = character->position.y + rect.y * 0.5 - (colliderPos.y - boxCollider->getRect().y * 0.5);
			const float bottom = colliderPos.y + boxCollider->getRect().y * 0.5 - (character->position.y - rect.y * 0.5);
			if (left > 0 && right > 0 && top > 0 && bottom > 0)
			{
				Vector2D v = Vector2D(left < right ? -left : right, top < bottom ? -top : bottom);
				if (abs(v.x) < abs(v.y))
				{
					v.y = 0;
				}
				else 
				{
					v.x = 0;
				}

				if (collider->isRigid() && collider->character)
				{
					character->position += v * 0.5;
					collider->character->position -= v * 0.5;
				}
				else
				{
					character->position += v * 0.5;
				}

				if (collider->character != nullptr)
				{
					character->collision(collider->character);
				}
				else
				{
					character->collision();
				}
			}
		}
	}
}

Vector2D Box::getRect() const { return rect;}
