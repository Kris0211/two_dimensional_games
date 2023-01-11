#include "MultiplayerCamera.h"
#include "../Math/Vector2D.h"
#include "../../Config.h"

MultiplayerCamera::MultiplayerCamera()
{
	this->trackedPlayer = nullptr;
	this->secondPlayer = nullptr;
	this->window = nullptr;
	this->position = Vector2D(0, 0);
}

MultiplayerCamera::MultiplayerCamera(Character* firstPlayer, Character* secondPlayer, SDL_Window* window)
{
	this->trackedPlayer = firstPlayer;
	this->secondPlayer = secondPlayer;
	this->window = window;
	this->position = (firstPlayer->position + secondPlayer->position) / 2;
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

void MultiplayerCamera::run()
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);
		
	zoom = (windowSizeY - TILE_SIZE) / (trackedPlayer->position - secondPlayer->position).length();
	if (zoom > maxZoom) zoom = maxZoom;
	
	position = (trackedPlayer->position + secondPlayer->position) * 0.5;
	position -= Vector2D(windowSizeX, windowSizeY) * 0.5 / zoom;
}
