#include "TileSet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/Box.h"
#include <fstream>

TileSet::TileSet(const std::vector<Sprite*> &tiles, const std::vector<bool>& tileCollision, std::string pathTo)
{
	this->width = TILEMAP_WIDTH;
	this->height = TILEMAP_HEIGHT;
	this->tileCollision = tileCollision;

	for (Sprite* sprite : tiles)
	{
		tileSprites.push_back(sprite);
	}

	std::ifstream level(pathTo);
	if (level.good())
	{
		std::string col;
		while (std::getline(level, col))
		{
			std::vector<uint8_t> row;
			for (char chr : col)
			{
				switch (chr)
				{
					case '.':
					{
						row.push_back(0);
						break;
					}
					case '+':
					{
						row.push_back(1);
						break;
					}
				default: break;
				}
			}
			levelLayout.push_back(row);
		}
	}
	else printf("Error loading level!\n");
}

void TileSet::free()
{
	for (Sprite* sprite : tileSprites)
	{
		sprite->free();
		sprite = nullptr;
	}
	for (CollisionBody* c : colliders)
	{
		CollisionManager::removeCollider(c);
		delete c;
	}
	colliders.clear();
}

Vector2D TileSet::getParallaxScale() const { return parallaxScale; }

Vector2D TileSet::getParallaxOffset() const { return parallaxOffset; }

void TileSet::setParallaxScale(const Vector2D& newScale) { parallaxScale = newScale; }

void TileSet::setParallaxOffset(const Vector2D& newOffset) { parallaxOffset = newOffset; }

void TileSet::render(SDL_Renderer* renderer, const Camera &cam) const
{
	for (int i = 0; i < width; i++)
	{
		for (int k = 0; k < height; k++) {
			tileSprites[levelLayout[k][i]]->render(
				TILE_SIZE * i - cam.getX() * parallaxScale.x + parallaxOffset.x, 
				TILE_SIZE * k - cam.getY() * parallaxScale.y + parallaxOffset.y,
				cam.getZoom(), renderer);
		}
	}
}

void TileSet::generateCollision()
{
	if (!tileCollision.empty())
	{
		for (CollisionBody* c : colliders)
		{
			CollisionManager::removeCollider(c);
			delete c;
		}
		colliders.clear();
	}

	for (unsigned long long y = 0; y < levelLayout.size(); y++)
	{
		for (unsigned long long x = 0; x < levelLayout[y].size(); x++)
		{
			if (tileCollision[levelLayout[y][x]])
			{
				CollisionBody* c = new Box(Vector2D(x * TILE_SIZE + parallaxOffset.x, y * TILE_SIZE + parallaxOffset.y), Vector2D(TILE_SIZE, TILE_SIZE), false);
				CollisionManager::addCollider(c);
				colliders.push_back(c);
			}
		}
	}
}
