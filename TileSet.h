#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Camera.h"
#include "Sprite.h"

class Camera;

class TileSet
{
public:
	TileSet(const std::vector<Sprite*> &tileSet, std::string pathTo, int tilemap_width, int tilemap_height);
	void render(SDL_Renderer* renderer, Camera cam, int tileSize = 64);
	void free();

private:
	std::vector<Sprite*> tileSprites;
	std::vector<std::vector<uint8_t>> levelLayout;
	int width;
	int height;
};
