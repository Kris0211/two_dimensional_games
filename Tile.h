#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, char type = 0);

	void render(SDL_Rect& camera);

	char getType();

private:
	SDL_Rect box;

	int type;
};
