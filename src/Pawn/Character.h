#pragma once
#include "../Camera/Camera.h"
#include "../Collision/CollisionBody.h"
#include "../Display/Sprite.h"
#include "../Math/Vector2D.h"

class Camera;

class Character
{
public:	
	Character(Sprite* sprite, const Vector2D &pos);
	Character(Sprite* sprite, const Vector2D &pos, CollisionBody* collider);

	~Character();
	void free();


	virtual void move(double delta);
	
	virtual void render(SDL_Renderer* renderer, const Camera &cam) const;

	virtual void collision(Character* character);


	void setSprite(Sprite* sprite);

	void setCollider(CollisionBody* collider);

	Vector2D getPosition() const;

	void setPosition(const Vector2D &pos);

	Vector2D getVelocity() const;

	void setName(std::string name);

	std::string getName() const;

	float getSpeed() const;

	void setSpeed(float newSpeed);

protected:
	Sprite* sprite;

	CollisionBody* collider;
	
	Vector2D position;
	Vector2D velocity;

	std::string charName;

	float speed = 1.0f;
};
