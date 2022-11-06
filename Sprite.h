#pragma once
#include <string>
#include <SDL.h>

class Sprite
{
public:
	Sprite();

	~Sprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* renderer);

	void render(int x, int y, double scale, SDL_Renderer* renderer) const;

	void free();

	int getWidth() const;

	int getHeight() const;

protected:
	SDL_Texture* sprTexture;

	int width;

	int height;
};