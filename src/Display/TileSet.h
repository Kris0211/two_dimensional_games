#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "../../Config.h"
#include "../Camera/Camera.h"
#include "Sprite.h"

class Camera;

class TileSet
{
public:
	TileSet(const std::vector<Sprite*> &tileSet, const std::vector<bool> &tileCollision, std::string pathTo);
	
	void render(SDL_Renderer* renderer, const Camera &cam) const;

	void generateCollision();

	void free();

	std::vector<CollisionBody*> colliders;
	std::vector<bool> tileCollision;

private:
	std::vector<Sprite*> tileSprites;
	std::vector<std::vector<uint8_t>> levelLayout;
	int width;
	int height;
};
