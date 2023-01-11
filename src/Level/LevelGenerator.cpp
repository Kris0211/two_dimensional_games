#include "LevelGenerator.h"

#include <algorithm>
#include <ctime>
#include <random>
#include <SDL_timer.h>
#include "../../Config.h"
#include "../Camera/Camera.h"
#include "../Display/Sprite.h"
#include "../Math/Vector2D.h"
#include "../Math/IntVector2D.h"
#include "../Collision/Box.h"
#include "../Collision/CollisionManager.h"

LevelGenerator::LevelGenerator(const std::vector<Sprite*> &tileSet, const std::vector<bool> &tileCollision, SDL_Renderer* renderer)
{
	this->tileSet = tileSet;
	this->tileCollision = tileCollision;
	tileSize = TILE_SIZE;
}

void LevelGenerator::generateLevel(const uint8_t size, const bool generateCollisions)
{
	const uint8_t limit = size * 2 + 1;
	
	std::vector<std::vector<uint8_t>> newLayout;
	newLayout.resize(size * 2 + 1);
	for (int i = 0; i < limit; i++)
	{
		newLayout[i].resize(size * 2 + 1);
	}

	const IntVector2D start(1, 1);
	srand(time(nullptr) + SDL_GetPerformanceCounter());
	backtrackingGenerator(start, limit, newLayout);
	layout = newLayout;

	// Generating corridor around the maze
	{
		for (int i = 0; i < limit; i++) //ensures the corridor generation
		{
			layout[1][i] = 1;
			layout[limit - 2][i] = 1;
			layout[i][1] = 1;
			layout[i][limit - 2] = 1;
		}
		// fills in the border
		layout[0][1] = 0;
		layout[1][0] = 0;
		layout[0][limit - 2] = 0;
		layout[limit - 2][0] = 0;
		layout[1][limit - 1] = 0;
		layout[limit - 1][1] = 0;
		layout[limit - 1][limit - 2] = 0;
		layout[limit - 2][limit - 1] = 0;
	}

	if (generateCollisions) generateCollision();
}

void LevelGenerator::generateCollision()
{
	if (!colliders.empty())
	{
		for (CollisionBody* c : colliders)
		{
			CollisionManager::removeCollider(c);
			delete c;
		}
		colliders.clear();
	}

	for (int y = 0; y < layout.size(); y++)
	{
		for (int x = 0; x < layout[y].size(); x++)
		{
			if (tileCollision[layout[y][x]])
			{
				CollisionBody* c = new Box(Vector2D(x * tileSize, y * tileSize), Vector2D(tileSize, tileSize), false);
				CollisionManager::addCollider(c);
				colliders.push_back(c);
			}
		}
	}
}

void LevelGenerator::render(SDL_Renderer* renderer, const Camera& cam) const
{
	const uint8_t tileSetSize = tileSet.size();
	Vector2D cameraPos(cam.getX(), cam.getY());
	for (int y = 0; y < layout.size(); y++)
	{
		for (int x = 0; x < layout[y].size(); x++)
		{
			const uint8_t tile = layout[y][x];
			if (tile < 0 || tile > tileSetSize) continue;
			tileSet[tile]->render(x * tileSize - cam.getX(), y * tileSize - cam.getY(), cam.getZoom(), renderer);
		}
	}
}

enum DIRECTION
{
	UP, RIGHT, DOWN, LEFT
};

void LevelGenerator::backtrackingGenerator(const IntVector2D &pos, uint8_t limit, std::vector<std::vector<uint8_t>>& newLayout)
{
	int directions[4] = { UP, DOWN, RIGHT, LEFT };
	std::shuffle(directions, directions + 4, std::mt19937(std::random_device()()));
	newLayout[pos.x][pos.y] = 1;

	for (const int dir : directions)
	{
		IntVector2D nextPos = pos;
		switch (dir)
		{
			case UP:
				{
					//printf("going UP\n");
					nextPos.y -= 2;
					if (nextPos.y > 1 && newLayout[nextPos.x][nextPos.y] == 0)
					{
						newLayout[pos.x][pos.y - 1] = 1;
						backtrackingGenerator(nextPos, limit, newLayout);
					}
					break;
				}
			case DOWN:
				{
					//printf("going DOWN\n");
					nextPos.y += 2;
					if (nextPos.y < limit - 1 && newLayout[nextPos.x][nextPos.y] == 0)
					{
						newLayout[pos.x][pos.y + 1] = 1;
						backtrackingGenerator(nextPos, limit, newLayout);
					}
					break;
				}
			case LEFT:
				{
					//printf("going LEFT\n");
					nextPos.x -= 2;
					if (nextPos.x > 1 && newLayout[nextPos.x][nextPos.y] == 0)
					{
						newLayout[pos.x - 1][pos.y] = 1;
						backtrackingGenerator(nextPos, limit, newLayout);
					}
					break;
				}
			case RIGHT:
				{
					//printf("going RIGHT\n");
					nextPos.x += 2;
					if (nextPos.x < limit - 1 && newLayout[nextPos.x][nextPos.y] == 0)
					{
						newLayout[pos.x + 1][pos.y] = 1;
						backtrackingGenerator(nextPos, limit, newLayout);
					}
					break;
				}
			default: break;
		}
	}
}
