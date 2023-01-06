#pragma once
#include "Camera.h"
class MultiplayerCamera : public Camera
{
public:
	MultiplayerCamera();
	MultiplayerCamera(Character* firstPlayer, Character* secondPlayer, SDL_Window* window);
	~MultiplayerCamera();

	void free();

	void run(double delta);

protected:
	Character* secondPlayer;
};

