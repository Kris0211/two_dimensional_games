#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Sprite.h"

class TileSet
{
public:
	TileSet(const std::vector<Sprite*> &tileSet, std::string pathTo, int tilemap_width, int tilemap_height);
	void render(SDL_Renderer* renderer, int tileSize = 64);

private:
	std::vector<Sprite*> tileSprites;
	std::vector<std::vector<uint8_t>> levelLayout;
	int width;
	int height;
};
