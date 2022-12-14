#pragma once
#include <SDL.h>

#include "../Pawn/PlayerCharacter.h"
#include "../Math/Vector2D.h"

class PlayerCharacter;

class Camera
{
public:
	Camera();
	Camera(PlayerCharacter* player, SDL_Window* window);
	~Camera();

	float getX() const;
	float getY() const;
	double getZoom() const;

	void setMaxZoom(double newZoom);

	void free();

	void run(double delta);

protected:
	PlayerCharacter* trackedPlayer;
	SDL_Window* window;
	Vector2D position;
	double zoom = 1.0;
	double maxZoom = 1.0;
};
