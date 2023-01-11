#pragma once
#include "Character.h"

class KeyboardPlayer : public Character
{
public:
	KeyboardPlayer(Sprite* spr, const Vector2D& pos, CollisionBody* col);

	void move(double deltaTime) override;

	void collision() override;

	void calculatePhysics(double height, double range);

	void jump();

	double speed = 0.2;
	double jumpHeight = JUMP_HEIGHT;
	double jumpRange = JUMP_RANGE;
	double jumpTime = JUMP_TIME;

private:
	Vector2D accel = Vector2D(0.0f, 0.0f);

	double sinceLastJump = 0.0;
	
	float jumpVelocity;

	float gravity = GRAVITY;

	bool onGround = false;

	bool canDoubleJump = false;

};
