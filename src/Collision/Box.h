#pragma once
#include "CollisionBody.h"
#include "../Math/Vector2D.h"

class Box : public CollisionBody
{
public:
	Box(const Vector2D &rect, bool isRigid);
	Box(const Vector2D &fixedPos, const Vector2D &rect, bool isRigid);
	~Box() override;

	void collide(bool separation = true, bool reflection = true) override;

	Vector2D getRect() const;

private:
	Vector2D rect;
};