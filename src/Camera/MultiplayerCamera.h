#pragma once
#include "Camera.h"
class MultiplayerCamera : public Camera
{
public:
	MultiplayerCamera();
	MultiplayerCamera(Character* firstPlayer, Character* secondPlayer, SDL_Window* window);
	MultiplayerCamera(Character* firstPlayer, Character* secondPlayer, SDL_Window* window, SDL_Renderer* renderer);
	~MultiplayerCamera();

	void free();
	
	void run();

protected:
	Character* secondPlayer;
};

