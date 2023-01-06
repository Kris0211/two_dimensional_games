#include "Box.h"
#include "Ball.h"
#include "CollisionManager.h"

Box::Box(const Vector2D &rect, bool isRigid) : CollisionBody(isRigid, BOX), rect(rect) {}

Box::Box(const Vector2D &fixedPos, const Vector2D &rect, bool isRigid) 
	: CollisionBody(fixedPos, isRigid, BOX), rect(rect) {}

void Box::collide(bool separation, bool reflection)
{
	Ball* ballCollider;
	Box* boxCollider;

	for (CollisionBody* collider : CollisionManager::colliders)
	{
		if (collider == this) continue;

		Vector2D colliderPos;
		if (collider->getCharacter())
		{
			colliderPos = collider->getCharacter()->position;
		}
		else
		{
			colliderPos = collider->getFixedPosition();
		}

		if (collider->getBodyType() == BALL)
		{
			ballCollider = static_cast<Ball*>(collider);

			Vector2D f = Vector2D::clamp(colliderPos, getCharacter()->position - rect * 0.5, getCharacter()->position + rect * 0.5);
			if ((colliderPos - f).length() < ballCollider->getRadius())
			{
				if (collider->getCharacter()->position != f)
				{
					Vector2D vec = (colliderPos - f).normal() * (ballCollider->getRadius() - (colliderPos - f).length());
					if (collider->isRigid() && collider->getCharacter() != nullptr)
					{
						getCharacter()->position -= vec * 0.5;
						collider->getCharacter()->position += vec * 0.5;
					}
					else
					{
						getCharacter()->position -= vec;
					}
				}

				if (collider->getCharacter() != nullptr)
				{
					getCharacter()->collision(collider->getCharacter());
				}
			}
		}
		else // BodyType == BOX
		{
			boxCollider = dynamic_cast<Box*>(collider);
			float left = (getCharacter()->position.x + rect.x * 0.5) - (colliderPos.x - boxCollider->getRect().x * 0.5);
			float right = (colliderPos.x + boxCollider->getRect().x * 0.5) - (getCharacter()->position.x - rect.x * 0.5);
			float top = (getCharacter()->position.y + rect.y * 0.5) - (colliderPos.y - boxCollider->getRect().y * 0.5);
			float bottom = (colliderPos.y + boxCollider->getRect().y * 0.5) - (getCharacter()->position.y - rect.y * 0.5);
			if (left > 0 && right > 0 && top > 0 && bottom > 0)
			{
				Vector2D v = Vector2D(left < right ? -left : right, top < bottom ? -top : bottom);
				if (abs(v.x) < abs(v.y)) v.y = 0;
				else v.x = 0;
				if (collider->isRigid() && collider->getCharacter())
				{
					getCharacter()->position += v * 0.5;
					collider->getCharacter()->position -= v * 0.5;
				}
				else
				{
					getCharacter()->position += v * 0.5;
				}

				if (collider->getCharacter() != nullptr)
				{
					getCharacter()->collision(collider->getCharacter());
				}
			}
		}
	}
}