#pragma once
#include "Camera.h"

Camera::Camera()
{
	this->trackedPlayer = nullptr;
	this->window = nullptr;
	this->position = Vector2D(0, 0);
}

Camera::Camera(PlayerCharacter* player, SDL_Window* window)
{
	this->trackedPlayer = player;
	this->window = window;
	this->position = player->getPosition();
}

Camera::~Camera()
{
	free();
}

void Camera::free()
{
	trackedPlayer = nullptr;
	window = nullptr;
}

int Camera::getX() { return position.x; }

int Camera::getY() { return position.y; }

void Camera::run(double delta)
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);

	if (trackedPlayer->getPosition().x < position.x + windowSizeX * 0.2) {
		position.x = trackedPlayer->getPosition().x - windowSizeX * 0.2;
	}

	if (trackedPlayer->getPosition().x > position.x + windowSizeX * 0.8) {
		position.x = trackedPlayer->getPosition().x - windowSizeX * 0.8;
	}
	
	position.y = position.y + 0.04 * (trackedPlayer->getPosition().y - windowSizeY * 0.5 - position.y);
}
