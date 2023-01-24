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
	TileSet(const std::vector<Sprite*> &tileSet, const std::vector<bool> &tileCollision, const char* pathTo);
	
	void render(SDL_Renderer* renderer, const Camera &cam) const;

	void generateCollision();

	void free();

	Vector2D getParallaxScale() const;
	Vector2D getParallaxOffset() const;

	void setParallaxScale(const Vector2D& newScale);
	void setParallaxOffset(const Vector2D& newOffset);

	std::vector<CollisionBody*> colliders;
	std::vector<bool> tileCollision;

private:
	std::vector<std::vector<uint8_t>> levelLayout;
	std::vector<Sprite*> tileSprites;
	
	Vector2D parallaxScale = Vector2D(1.0f, 1.0f);
	Vector2D parallaxOffset;

	int width;
	int height;
};
