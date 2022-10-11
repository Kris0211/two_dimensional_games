#pragma once
#include <string>
#include <SDL.h>

class Sprite
{
public:
	Sprite();

	~Sprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* rederer);

	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = nullptr);

	void free();

	int getWidth();

	int getHeight();

private:
	SDL_Texture* sprTexture;

	int width;

	int height;
};