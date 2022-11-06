#include "AnimSprite.h"

AnimSprite::AnimSprite()
{
	sprTexture = nullptr;
	width = 0;
	height = 0;
	frameCount = 1;
}

bool AnimSprite::loadFromFile(const std::string pathTo, SDL_Renderer* renderer, const int fSize, const int fCount)
{
	frameCount = fCount;
	Sprite::loadFromFile(pathTo, renderer);
	if (sprTexture != nullptr) {
		for (int i = 0; i < fCount; i++)
		{
			SDL_Rect clip;
			frames.push_back(clip);
			frames[i].x = fSize * i;
			frames[i].y = 0;
			frames[i].w = fSize;
			frames[i].h = fSize;
		}
	}
	return sprTexture != nullptr;
}

void AnimSprite::render(const int x, const int y, const int frame, SDL_Renderer* renderer) const
{
	const SDL_Rect rect = {
		x,
		y,
		frames[frame].w,
		frames[frame].h
	};
	const SDL_Rect clip = frames[frame];
	SDL_RenderCopy(renderer, sprTexture, &clip, &rect);
}

void AnimSprite::free()
{
	if (sprTexture != nullptr)
	{
		Sprite::free();
		frames.clear();
		frameCount = 0;
	}
}
