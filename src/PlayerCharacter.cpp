#pragma once
#include "PlayerCharacter.h"

PlayerCharacter::~PlayerCharacter()
{
	free();
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, const Vector2D &pos, const float speed)
{
	this->playerSprite = sprite;
	this->position = pos;
	this->velocity = Vector2D(0, 0);
	this->speedMultiplier = speed;
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, float x, float y, const float speed)
{
	this->playerSprite = sprite;
	this->position = Vector2D(x - static_cast<float>(sprite->getWidth()) * 0.5f, y - static_cast<float>(sprite->getHeight()) * 0.5f);
	this->velocity = Vector2D(0, 0);
	this->speedMultiplier = speed;
}

void PlayerCharacter::free()
{
	playerSprite = nullptr;
}

void PlayerCharacter::move(double delta, bool use_arrows)
{
	const Uint8* keyPress = SDL_GetKeyboardState(nullptr);
	if (use_arrows)
	{
		velocity = Vector2D(keyPress[SDL_SCANCODE_RIGHT] - keyPress[SDL_SCANCODE_LEFT],
			keyPress[SDL_SCANCODE_DOWN] - keyPress[SDL_SCANCODE_UP]);
	}
	else
	{
		velocity = Vector2D(keyPress[SDL_SCANCODE_D] - keyPress[SDL_SCANCODE_A],
			keyPress[SDL_SCANCODE_S] - keyPress[SDL_SCANCODE_W]);
	}

	if (velocity.length() != 0.0f)
	{
		velocity.normalize();
	}
	position += velocity * speedMultiplier;
}

void PlayerCharacter::smoothMove(double delta, float smooth)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2D target(static_cast<float>(x) - position.x, static_cast<float>(y) - position.y);
	target *= speedMultiplier;// *delta;
	velocity = target * static_cast<float>(1.0 - static_cast<double>(smooth)) + velocity * smooth;
	position += velocity;
}

void PlayerCharacter::render(SDL_Renderer* renderer) const
{
	playerSprite->render(static_cast<int>(static_cast<int>(position.x) - playerSprite->getWidth() * 0.5), 
		static_cast<int>(static_cast<int>(position.y) - playerSprite->getHeight() * 0.5),
		1.0, renderer);
}

void PlayerCharacter::render(SDL_Renderer* renderer, const Camera &cam) const
{
	playerSprite->render(static_cast<int>(static_cast<float>(position.x) - cam.getX()), 
		static_cast<int>(static_cast<float>(position.y) - cam.getY()),
		cam.getScale(), renderer);
}

Vector2D PlayerCharacter::getPosition() { return position; }

void PlayerCharacter::setPosition(const Vector2D &pos) { position = pos; }

void PlayerCharacter::setPosition(const float x, const float y) { position = Vector2D(x, y); }

void PlayerCharacter::setSprite(Sprite* sprite) { playerSprite = sprite; }

void PlayerCharacter::setMovementSpeed(const float multiplier) { speedMultiplier = multiplier; }

float PlayerCharacter::getMovementSpeed() const { return speedMultiplier; }