#include "KeyboardPlayer.h"

#include <iostream>

KeyboardPlayer::KeyboardPlayer(Sprite* spr, const Vector2D& pos, CollisionBody* col) : Character(spr, pos, col)
{
	charName = "Player1";
	calculatePhysics(JUMP_HEIGHT, JUMP_TIME);
}

void KeyboardPlayer::move(double deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
	velocity.x = static_cast<float>(keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A]);
	position.x += velocity.x * static_cast<float>(deltaTime);

	if (keyboard[SDL_SCANCODE_W] && onGround)
	{
		velocity.y = jumpVelocity;
	}
	else if (!onGround)
	{
		velocity.y += accel.y * static_cast<float>(deltaTime);
	}

	if (!onGround)
	{
		position.y += velocity.y * deltaTime + accel.y * 0.5 * deltaTime * deltaTime;
	}
	else
	{
		velocity.y = 0;
	}

	accel.y = velocity.y > 0 ? gravity * 2 : gravity;

	onGround = false;
	sinceLastJump += deltaTime;
	std::cout << onGround << "\n";
}

void KeyboardPlayer::collision()
{
	velocity.y = 0;
	onGround = true;
	canDoubleJump = true;
	sinceLastJump = 0.0;
}

void KeyboardPlayer::calculatePhysics(const double height, const double range)
{
	jumpVelocity = -2.0 * speed * jumpHeight / jumpRange;
	gravity = 2.0 * jumpHeight / (jumpRange * jumpRange);
	std::cout << "Velocity: " << -jumpVelocity << "\nGravity: " << gravity << "\n";
}

void KeyboardPlayer::jump()
{
	if (!onGround && canDoubleJump)
	{
		velocity.y = jumpVelocity;
		canDoubleJump = false;
		sinceLastJump = 0.0;
	}
}
