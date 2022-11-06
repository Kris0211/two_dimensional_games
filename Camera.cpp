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

float Camera::getX() const { return position.x; }

float Camera::getY() const { return position.y; }

double Camera::getScale() const { return scale; }

double Camera::getScaleFactor() const { return scaleFactor; }

void Camera::setScaleFactor(const double factor) { scaleFactor = factor; }


void Camera::run(double delta)
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);

	if (trackedPlayer->getPosition().x < position.x + static_cast<float>(windowSizeX) * 0.2f) {
		position.x = trackedPlayer->getPosition().x - static_cast<float>(windowSizeX) * 0.2f;
	}

	if (trackedPlayer->getPosition().x > position.x + static_cast<float>(windowSizeX) * 0.8f) {
		position.x = trackedPlayer->getPosition().x - static_cast<float>(windowSizeX) * 0.8f;
	}
	
	position.y = position.y + 0.04f * (trackedPlayer->getPosition().y - static_cast<float>(windowSizeY) * 0.5f - position.y);
}
