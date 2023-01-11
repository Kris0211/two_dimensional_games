#pragma once
#include "Camera.h"

Camera::Camera()
{
	this->trackedPlayer = nullptr;
	this->window = nullptr;
	this->position = Vector2D(0, 0);
}

Camera::Camera(Character* player, SDL_Window* window)
{
	this->trackedPlayer = player;
	this->window = window;
	this->position = player->position;
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

float Camera::getX() const { return position.x; }

float Camera::getY() const { return position.y; }

double Camera::getZoom() const { return zoom; }

Vector2D Camera::getPosition() const { return position; }

void Camera::setMaxZoom(const double newZoom) { maxZoom = newZoom; }


void Camera::run()
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);

	if (trackedPlayer->position.x < position.x + static_cast<float>(windowSizeX) * 0.2f) {
		position.x = trackedPlayer->position.x - static_cast<float>(windowSizeX) * 0.2f;
	}

	if (trackedPlayer->position.x > position.x + static_cast<float>(windowSizeX) * 0.8f) {
		position.x = trackedPlayer->position.x - static_cast<float>(windowSizeX) * 0.8f;
	}
	
	position.y = position.y + 0.04f * (trackedPlayer->position.y - static_cast<float>(windowSizeY) * 0.5f - position.y);
}
