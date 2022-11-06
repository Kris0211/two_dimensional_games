#pragma once
#include "Camera.h"
class MultiplayerCamera : public Camera
{
public:
	MultiplayerCamera();
	MultiplayerCamera(PlayerCharacter* firstPlayer, PlayerCharacter* secondPlayer, SDL_Window* window);
	~MultiplayerCamera();

	void free();

	void run(double delta);

protected:
	PlayerCharacter* secondPlayer;
};

