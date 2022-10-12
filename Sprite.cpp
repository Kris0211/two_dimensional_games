#pragma once
#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite()
{
	sprTexture = nullptr;
	width = 0;
	height = 0;
}

Sprite::~Sprite()
{
	free();
}

bool Sprite::loadFromFile(std::string pathTo, SDL_Renderer* renderer)
{
	free();

	//Load image at specified path
	SDL_Texture* newTexture = IMG_LoadTexture(renderer, pathTo.c_str());
	if (newTexture == nullptr)
	{
		printf("Unable to load texture from %s! SDL Error: %s\n", pathTo.c_str(), SDL_GetError());
		return false;
	}

	//Get image dimensions
	SDL_QueryTexture(newTexture, nullptr, nullptr, &width, &height);
	
	//Return success
	sprTexture = newTexture;
	return sprTexture != nullptr;
}

void Sprite::free()
{
	if (sprTexture != nullptr)
	{
		sprTexture = nullptr;
		width = 0;
		height = 0;
	}
}

void Sprite::render(const int x, const int y, SDL_Renderer* renderer, SDL_Rect* clip) const
{
	SDL_Rect rect = { x, y, width, height };
	if (clip != nullptr)
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(renderer, sprTexture, clip, &rect);
}

int Sprite::getWidth() const { return width; }

int Sprite::getHeight() const { return height; }
