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

	const Vector2D trackedPosition = (trackedPlayer->getPosition() * 2 + secondPlayer->getPosition()) / 3;

	if (trackedPosition.y < position.y + static_cast<float>(windowSizeY) * 0.4f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.4f;
	}

	if (trackedPosition.y > position.y + static_cast<float>(windowSizeY) * 0.6f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.6f;
	}

	position.x = position.x + 0.03f * (trackedPosition.x - static_cast<float>(windowSizeX) * 0.5f - position.x);

	scale = 1.0 - std::max(abs(trackedPlayer->getPosition().x - secondPlayer->getPosition().x), 
		abs(trackedPlayer->getPosition().y - secondPlayer->getPosition().y)) * scaleFactor;
}