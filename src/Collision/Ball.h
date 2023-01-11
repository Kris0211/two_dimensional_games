	#pragma once
#include <SDL.h>

#include "CollisionBody.h"
#include "../Display/Sprite.h"
#include "../Math/Vector2D.h"

class Ball : public CollisionBody
{
public:
	Ball(float radius, bool isRigid);
	Ball(const Vector2D &fixedPosition, float radius, bool isRigid);
	~Ball() override = default;

	void collide(bool separation = true, bool reflection = true) override;

	float getRadius() const;

private:
	float radius = 10.0f;
};
