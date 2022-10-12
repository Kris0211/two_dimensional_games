#pragma once
#include "PlayerCharacter.h"

PlayerCharacter::~PlayerCharacter()
{
	free();
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, Vector2D pos)
{
	this->playerSprite = sprite;
	this->position = pos;
	this->velocity = Vector2D(0, 0);
}

PlayerCharacter::PlayerCharacter(Sprite* sprite, int x, int y)
{
	this->playerSprite = sprite;
	this->position = Vector2D(x, y);
	this->velocity = Vector2D(0, 0);
}

void PlayerCharacter::free()
{
	playerSprite = nullptr;
}

void PlayerCharacter::move(Vector2D &vel) 
{
	position += vel;
}

void PlayerCharacter::smoothMove(Vector2D& vel, float smooth)
{
	position += vel;
}

void PlayerCharacter::render(SDL_Renderer* renderer, SDL_Rect* clip)
{
	playerSprite->render(position.getX(), position.getY(), renderer, clip);
}

Vector2D PlayerCharacter::getPosition() { return position; }

void PlayerCharacter::setPosition(Vector2D &pos) { position = pos; }

void PlayerCharacter::setPosition(int x, int y) { position = Vector2D(x, y); }

void PlayerCharacter::setSprite(Sprite* sprite) { playerSprite = sprite; }
