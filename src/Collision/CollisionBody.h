#pragma once
#include <SDL.h>
#include "../Pawn/Character.h"
#include "../Math/Vector2D.h"

enum BodyType 
{ 
	BALL,
	BOX 
};

class CollisionBody
{
public:
	CollisionBody(bool isRigid, BodyType type) : rigid(isRigid), type(type) {}
	CollisionBody(const Vector2D &pos, bool isRigid, BodyType type) : position(pos), rigid(isRigid), type(type) {}

	virtual ~CollisionBody() = default;

	virtual void collide(bool separation, bool reflection) = 0;

	bool isRigid() const { return rigid; }
	
	void setRigid(const bool rigid) { this->rigid = rigid; }

	Character* getCharacter() const { return character; }

	void setCharacter(Character* chr) { this->character = chr; }

	Vector2D getFixedPosition() const { return position; }

	BodyType getBodyType() const { return type; }

protected:
	bool rigid = true;
	Character* character = nullptr;
	Vector2D position;
	BodyType type;

	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 800;
};

