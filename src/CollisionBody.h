#pragma once
#include "Vector2D.h"

class CollisionBody
{
public:
	virtual ~CollisionBody() = default;

	virtual void collide(bool separation, bool reflection) = 0;

	bool isRigid() const { return rigid; }
	void setRigid(const bool rigid) { this->rigid = rigid; }

	Vector2D getColliderPosition() const{ return position; }
	void setColliderPosition(const Vector2D &newPosition) { this->position = newPosition; }

protected:
	bool rigid = true;
	Vector2D position;
};

