#pragma once
#include <SDL_render.h>
#include <vector>
#include "../Pawn/Character.h"

class IntVector2D;
class CollisionBody;
class Camera;
class Sprite;

class LevelGenerator
{
public:

	// making it public to make our life easier with collisions
	std::vector<CollisionBody*> colliders;

	LevelGenerator(const std::vector<Sprite*>& tileSet, const std::vector<bool>& tileCollision, SDL_Renderer* renderer);

	void generateLevel(uint8_t size, bool generateCollision = true);

	void generateCollision();

	void render(SDL_Renderer* renderer, const Camera& camera) const;

private:
	std::vector<Sprite*> tileSet;
	std::vector<bool> tileCollision;
	std::vector<std::vector<uint8_t>> layout;
	uint8_t tileSize;

	static void backtrackingGenerator(const IntVector2D &pos, uint8_t limit, std::vector<std::vector<uint8_t>>& layout);
};