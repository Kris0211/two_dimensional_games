#pragma once
#include <SDL.h>
#include "PlayerCharacter.h"
#include "Vector2D.h"

class PlayerCharacter;

class Camera
{
public:
	Camera();
	Camera(PlayerCharacter* player, SDL_Window* window);
	~Camera();

	int getX();
	int getY();

	void free();

	void run(double delta);

protected:
	PlayerCharacter* trackedPlayer;
	SDL_Window* window;
	Vector2D position;
};
