#include "MultiplayerCamera.h"
#include "../Math/Vector2D.h"

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

	Vector2D windowRect(windowSizeX, windowSizeY);
	Vector2D trackedPosition = (trackedPlayer->getPosition() + secondPlayer->getPosition()) * 0.5;

	if (trackedPosition.y < position.y + static_cast<float>(windowSizeY) * 0.3f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.3f;
	}

	if (trackedPosition.y > position.y + static_cast<float>(windowSizeY) * 0.7f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.7f;
	}

	position.x = position.x + 0.03f * (trackedPosition.x - static_cast<float>(windowSizeX) * 0.5f - position.x);
	//position.y = position.y + 0.03f * (trackedPosition.x - static_cast<float>(windowSizeX) * 0.5f - position.y);


	zoom = (windowSizeY - 128) / (trackedPlayer->getPosition() - secondPlayer->getPosition()).length();
	if (zoom > maxZoom) zoom = maxZoom;

}


