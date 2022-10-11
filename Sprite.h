#pragma once
#include <string>
#include <SDL.h>

class Sprite
{
public:
	Sprite();

	~Sprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* rederer);

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr) const;

	void free();

	int getWidth() const;

	int getHeight() const;

protected:
	SDL_Texture* sprTexture;

	int width;

	int height;
};