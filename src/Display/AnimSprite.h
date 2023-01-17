#pragma once
#include "Sprite.h"
#include <vector>

class AnimSprite : Sprite
{
public:
	AnimSprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* renderer, int fSize, int fCount = 1);

	void render(int x, int y, int frame, SDL_Renderer* renderer) const;

	void free();

	float currentFrame = 0;

protected:
	std::vector<SDL_Rect> frames;

	int frameCount;
};
