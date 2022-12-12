#pragma once
#include "Camera.h"
#include "CollisionBody.h"
#include "Sprite.h"
#include "Vector2D.h"

class Camera;

class PlayerCharacter
{
public:
	~PlayerCharacter();
	
	PlayerCharacter(Sprite* sprite, const Vector2D &pos, float speed = 1.0);

	PlayerCharacter(Sprite* sprite, const Vector2D &pos, CollisionBody* collider, float speed = 1.0);
	
	PlayerCharacter(Sprite* sprite, float x, float y, float speed = 1.0);

	void free();


	void move(double delta, bool use_arrows = true);
	
	void render(SDL_Renderer* renderer, const Camera &cam) const;
		

	Vector2D getPosition();

	void setPosition(const Vector2D &pos);

	void setPosition(float x, float y);

	void setSprite(Sprite* sprite);

	void setCollider(CollisionBody* collider);

	void setColliderPosition(const Vector2D& pos) const;

	void setMovementSpeed(float multiplier);

	float getMovementSpeed() const;

private:
	Sprite* playerSprite;

	CollisionBody* collisionBody;
	
	Vector2D position;
	
	Vector2D velocity;

	float speedMultiplier;
};
