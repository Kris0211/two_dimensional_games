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

	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(pathTo.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", pathTo.c_str(), IMG_GetError());
		return false;
	}

	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", pathTo.c_str(), SDL_GetError());
		return false;
	}

	//Get image dimensions
	width = loadedSurface->w;
	height = loadedSurface->h;
	
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	
	//Return success
	sprTexture = newTexture;
	return sprTexture != NULL;
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

void Sprite::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
	SDL_Rect rect = { x, y, width, height };
	if (clip != nullptr)
	{
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(renderer, sprTexture, clip, &rect);
}

int Sprite::getWidth() { return width; }

int Sprite::getHeight() { return height; }
