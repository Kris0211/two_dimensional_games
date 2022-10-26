#pragma once
#include "Camera.h"
#include "Sprite.h"
#include "Vector2D.h"

class Camera;

class PlayerCharacter
{
public:
	~PlayerCharacter();
	
	PlayerCharacter(Sprite* sprite, Vector2D pos, const float speed = 1.0);
	
	PlayerCharacter(Sprite* sprite, float x, float y, const float speed = 1.0);

	void free();

	void move(double delta);

	void smoothMove(double delta, float smooth = 0.9);

	void render(SDL_Renderer* renderer, Camera cam) const;

	Vector2D getPosition();

	void setPosition(Vector2D &pos);

	void setPosition(float x, float y);

	void setSprite(Sprite* sprite);

	void setMovementSpeed(const float multiplier);

	float getMovementSpeed() const;

private:
	Sprite* playerSprite;
	
	Vector2D position;
	
	Vector2D velocity;

	float speedMultiplier;
};
