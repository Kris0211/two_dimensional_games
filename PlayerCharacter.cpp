#pragma once
#include "PlayerCharacter.h"

PlayerCharacter::~PlayerCharacter()
{
	free();
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, Vector2D pos, const float speed)
{
	this->playerSprite = sprite;
	this->position = pos;
	this->velocity = Vector2D(0, 0);
	this->speedMultiplier = speed;
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, float x, float y, const float speed)
{
	this->playerSprite = sprite;
	this->position = Vector2D(x, y);
	this->velocity = Vector2D(0, 0);
	this->speedMultiplier = speed;
}

void PlayerCharacter::free()
{
	playerSprite = nullptr;
}

void PlayerCharacter::move(double delta)
{
	const Uint8* keyPress = SDL_GetKeyboardState(nullptr);
	velocity = Vector2D(keyPress[SDL_SCANCODE_RIGHT] - keyPress[SDL_SCANCODE_LEFT],
						keyPress[SDL_SCANCODE_DOWN] - keyPress[SDL_SCANCODE_UP]);
	if (velocity.length() != 0.0)
	{
		velocity.normalize();
	}
	position += velocity * speedMultiplier;
}

void PlayerCharacter::smoothMove(double delta, float smooth)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2D target(x - position.x, y - position.y);
	target *= speedMultiplier * delta;
	velocity = target * static_cast<float>(1.0 - smooth) + velocity * smooth;
	position += velocity;
}

void PlayerCharacter::render(SDL_Renderer* renderer, SDL_Rect* clip) const
{
	playerSprite->render(position.x, position.y, renderer, clip);
}

Vector2D PlayerCharacter::getPosition() { return position; }

void PlayerCharacter::setPosition(Vector2D &pos) { position = pos; }

void PlayerCharacter::setPosition(float x, float y) { position = Vector2D(x, y); }

void PlayerCharacter::setSprite(Sprite* sprite) { playerSprite = sprite; }

void PlayerCharacter::setMovementSpeed(const float multiplier) { speedMultiplier = multiplier; }

float PlayerCharacter::getMovementSpeed() const { return speedMultiplier; }

