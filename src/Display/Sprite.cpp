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

bool Sprite::loadFromFile(const std::string pathTo, SDL_Renderer* renderer)
{
	// Free previous texture
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

void Sprite::render(const int x, const int y, double scale, SDL_Renderer* renderer) const
{
	SDL_Rect rect;
	rect.x = static_cast<int>((x - width * 0.5) * scale);
	rect.y = static_cast<int>((y - height * 0.5) * scale);
	rect.w = static_cast<int>(width * scale);
	rect.h = static_cast<int>(height * scale);

	SDL_RenderCopy(renderer, sprTexture, nullptr, &rect);
}

int Sprite::getWidth() const { return width; }

int Sprite::getHeight() const { return height; }
