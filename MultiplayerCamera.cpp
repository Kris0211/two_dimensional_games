#include "MultiplayerCamera.h"

MultiplayerCamera::MultiplayerCamera()
{
	this->trackedPlayer = nullptr;
	this->secondPlayer = nullptr;
	this->window = nullptr;
	this->position = Vector2D(0, 0);
}

MultiplayerCamera::MultiplayerCamera(PlayerCharacter* firstPlayer, PlayerCharacter* secondPlayer, SDL_Window* window)
{
	this->trackedPlayer = firstPlayer;
	this->secondPlayer = secondPlayer;
	this->window = window;
	this->position = (firstPlayer->getPosition() + secondPlayer->getPosition()) / 2;
}

MultiplayerCamera::~MultiplayerCamera()
{
	free();
}

void MultiplayerCamera::free() 
{
	secondPlayer->free();
	Camera::free();
}

void MultiplayerCamera::run(double delta)
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);

	Vector2D trackedPosition = (trackedPlayer->getPosition() * 2 + secondPlayer->getPosition()) / 3;

	if (trackedPosition.y < position.y + windowSizeX * 0.4) {
		position.y = trackedPosition.y - windowSizeX * 0.4;
	}

	if (trackedPosition.y > position.y + windowSizeY * 0.6) {
		position.y = trackedPosition.y - windowSizeY * 0.6;
	}

	position.x = position.x + 0.03 * (trackedPosition.x - windowSizeX * 0.5 - position.x);
}