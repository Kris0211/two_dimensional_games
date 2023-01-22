#include "TileSet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/Box.h"
#include <fstream>
#include <iostream>
#include <map>

TileSet::TileSet(const std::vector<Sprite*> &tiles, const std::vector<bool>& tileCollision, const char* pathTo)
{
	this->tileCollision = tileCollision;
	this->parallaxScale = Vector2D(1, 1);

	for (Sprite* sprite : tiles)
	{
		tileSprites.push_back(sprite);
	}

	std::ifstream level;
	level.open(pathTo);
	if (level.is_open())
	{
		std::string line;
		std::map<char, uint8_t> symbols;

		int symbolSize;
		level >> symbolSize;

		getline(level, line);
		getline(level, line);
		for (int i = 0; i < symbolSize; i++)
		{
			symbols.emplace(line[i], i);
		}
		
		while (getline(level, line))
		{
			std::vector<uint8_t> row;
			for (char c : line)
			{
				auto it = symbols.find(c);
				if (it != symbols.end())
				{
					row.push_back(it->second);
				}
				else
				{
					row.push_back(-1); // Mark unknown/invalid symbols with -1
				}
			}
			levelLayout.push_back(row);
			std::cout << "\n";
		}
		level.close();
	}
	else std::cout <<"Error loading level \"" << pathTo << "\"!\n";
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
	const uint8_t tileSetSize = tileSprites.size();
	Vector2D cameraPos(cam.getX(), cam.getY());
	for (unsigned long long i = 0; i < levelLayout.size(); i++)
	{
		for (unsigned long long k = 0; k < levelLayout[i].size(); k++)
		{
			const uint8_t tile = levelLayout[i][k];
			if (tile < 0 || tile > tileSetSize) continue; // We are not checking if tile_id = -1 because sometimes it's 255 and no one knows why
			tileSprites[tile]->render(
				TILE_SIZE * k - cam.getX() * parallaxScale.x + parallaxOffset.x,
				TILE_SIZE * i - cam.getY() * parallaxScale.y + parallaxOffset.y,
				cam.getZoom(), renderer
			);
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

	for (unsigned long long i = 0; i < levelLayout.size(); i++)
	{
		for (unsigned long long k = 0; k < levelLayout[i].size(); k++)
		{
			if (tileCollision[levelLayout[i][k]])
			{
				CollisionBody* c = new Box(
					Vector2D(k * TILE_SIZE + parallaxOffset.x, i * TILE_SIZE + parallaxOffset.y), 
					Vector2D(TILE_SIZE, TILE_SIZE), false);
				CollisionManager::addCollider(c);
				colliders.push_back(c);
			}
		}
	}
}
