#pragma once
#include <SDL.h>
#include "../../Config.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionBody.h"
#include "../Display/Sprite.h"
#include "../Math/Vector2D.h"

class Camera;
class CollisionBody;

class Character
{
public:	
	Character(Sprite* sprite, const Vector2D &pos);
	Character(Sprite* sprite, const Vector2D &pos, CollisionBody* collider);

	virtual ~Character();
	void free();


	virtual void move(double delta) {};
	
	virtual void render(SDL_Renderer* renderer, const Camera &cam) const;

	virtual void collision() {}

	virtual void collision(Character* character) {}


	void setSprite(Sprite* sprite);

	void setCollider(CollisionBody* collider);

	void setName(const std::string &name);

	std::string getName() const;

	float getSpeed() const;

	void setSpeed(float newSpeed);

	//this is public to make our life easier with collisions
	Vector2D position;
	Vector2D velocity = Vector2D(0.0f, 0.0f);

protected:
	Sprite* sprite;

	CollisionBody* collider;

	std::string charName;

	float speed = 0.5f;
};
