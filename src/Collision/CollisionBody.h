#pragma once
#include "../Math/Vector2D.h"

class Character;

enum BodyType 
{ 
	BALL,
	BOX 
};

class CollisionBody
{
public:
	CollisionBody(const bool isRigid, const BodyType type) : rigid(isRigid), type(type) {}
	CollisionBody(const Vector2D &pos, const bool isRigid, const BodyType type) : position(pos), rigid(isRigid), type(type) {}

	virtual ~CollisionBody() = default;

	virtual void collide(bool separation, bool reflection) = 0;

	bool isRigid() const { return rigid; }
	
	void setRigid(const bool rigid) { this->rigid = rigid; }

	Vector2D getFixedPosition() const { return position; }

	BodyType getBodyType() const { return type; }
	
	Character* character = nullptr;

protected:
	Vector2D position;
	bool rigid = true;
	BodyType type;

	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 800;
};

