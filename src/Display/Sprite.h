#pragma once
#include <SDL.h>
#include <string>

class Sprite
{
public:
	Sprite();

	~Sprite();

	bool loadFromFile(std::string pathTo, SDL_Renderer* renderer);

	void render(int x, int y, double scale, SDL_Renderer* renderer) const;

	void render(int x, int y, double scale, double angle, SDL_Renderer* renderer) const;

	void free();

	int getWidth() const;

	int getHeight() const;

protected:
	SDL_Texture* sprTexture;

	int width;

	int height;
		
};
