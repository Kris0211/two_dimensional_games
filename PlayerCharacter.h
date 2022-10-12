#pragma once
#include "Sprite.h"
#include "Vector2D.h"

class PlayerCharacter
{
public:
	~PlayerCharacter();
	
	PlayerCharacter(Sprite* sprite, Vector2D pos);
	
	PlayerCharacter(Sprite* sprite, int x, int y);

	void free();

	void move(Vector2D &vel);

	void smoothMove(Vector2D &vel, float smooth = 0.5);

	void render(SDL_Renderer* renderer, SDL_Rect* clip = nullptr);

	Vector2D getPosition();

	void setPosition(Vector2D &pos);

	void setPosition(int x, int y);

	void setSprite(Sprite* sprite);

	void setMovementSpeed(const int multiplier);

	int getMovementSpeed();;

private:
	PlayerCharacter();

private:
	Sprite* playerSprite;
	
	Vector2D position;
	
	Vector2D velocity;

	int speedMultiplier;
};
