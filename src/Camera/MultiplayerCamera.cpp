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

	int distSquared = (secondPlayer->getPosition().x - trackedPlayer->getPosition().x) * (secondPlayer->getPosition().x - trackedPlayer->getPosition().x) +
		(secondPlayer->getPosition().y - trackedPlayer->getPosition().y) * (secondPlayer->getPosition().y - trackedPlayer->getPosition().y);

	//Vector2D trackedPosition = distSquared > distanceTreshold ? (trackedPlayer->getPosition() * 3  + secondPlayer->getPosition()) / 4
	//	: (trackedPlayer->getPosition() + secondPlayer->getPosition()) / 2;

	Vector2D trackedPosition = (trackedPlayer->getPosition() + secondPlayer->getPosition()) / 2;

	//trackedPosition = (trackedPlayer->getPosition() * 2 + secondPlayer->getPosition()) / 3;

	if (trackedPosition.y < position.y + static_cast<float>(windowSizeY) * 0.3f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.3f;
	}

	if (trackedPosition.y > position.y + static_cast<float>(windowSizeY) * 0.7f)
	{
		position.y = trackedPosition.y - static_cast<float>(windowSizeY) * 0.7f;
	}

	position.x = position.x + 0.03f * (trackedPosition.x - static_cast<float>(windowSizeX) * 0.5f - position.x);

	scale = 1.0 - std::max(abs(trackedPlayer->getPosition().x - secondPlayer->getPosition().x),
		abs(trackedPlayer->getPosition().y - secondPlayer->getPosition().y)) * scaleFactor;
		//distSquared > distanceTreshold ? : 0.906; //Don't ask why, I don't know either.
	//printf("%f", scale);
}

void MultiplayerCamera::setDistanceTreshold(int treshold) { distanceTreshold = treshold; }
