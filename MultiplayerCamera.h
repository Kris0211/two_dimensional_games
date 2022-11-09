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

	void setDistanceTreshold(int treshold);

protected:
	PlayerCharacter* secondPlayer;
	int distanceTreshold = 100000;
};

