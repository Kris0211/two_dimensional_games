#pragma once
#include "Sprite.h"
#include <vector>

class AnimSprite : Sprite
{
public:
	AnimSprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* renderer, const int fSize, const int fCount = 1);

	void render(int x, int y, int frame, SDL_Renderer* renderer) const;

	void free();

protected:
	std::vector<SDL_Rect> frames;

	int frameCount;
};
