#pragma once
#include "Character.h"

#include "../Collision/CollisionBody.h"
#include "../Collision/CollisionManager.h"

Character::~Character()
{
	free();
}

Character::Character(Sprite* sprite, const Vector2D &pos)
{
	this->sprite = sprite;
	this->position = pos;
	this->velocity = Vector2D(0, 0);
	this->collider = nullptr;
}

Character::Character(Sprite* sprite, const Vector2D& pos, CollisionBody* collider)
{
	this->sprite = sprite;
	this->position = pos;
	this->velocity = Vector2D(0, 0);
	this->collider = collider;
	CollisionManager::addCollider(this->collider);
}

void Character::free()
{
	sprite = nullptr;
	if (collider != nullptr)
	{
		CollisionManager::removeCollider(collider);
		collider = nullptr;
	}
}


void Character::render(SDL_Renderer* renderer, const Camera &cam) const
{
	sprite->render(static_cast<int>(static_cast<float>(position.x) - cam.getX()), 
		static_cast<int>(static_cast<float>(position.y) - cam.getY()),
		cam.getZoom(), renderer);
}

void Character::setSprite(Sprite* sprite) { this->sprite = sprite; }

void Character::setCollider(CollisionBody* collider) { this->collider = collider; }

Vector2D Character::getPosition() const { return position; }

void Character::setPosition(const Vector2D &pos) { position = pos; }

Vector2D Character::getVelocity() const { return velocity; }

void Character::setName(std::string name) { charName = name; }

std::string Character::getName() const { return charName; }

void Character::setSpeed(float newSpeed) { this->speed = newSpeed; }

float Character::getSpeed() const { return speed; }
