#include "TileSet.h"

#include <fstream>

TileSet::TileSet(const std::vector<Sprite*>& tiles, std::string pathTo, int tilemap_width, int tilemap_height)
{
	this->width = tilemap_width;
	this->height = tilemap_height;
	for (Sprite* sprite : tiles)
	{
		tileSprites.push_back(sprite);
	}

	std::string col;
	std::ifstream level(pathTo);
	if (level.good())
	{
		while (std::getline(level, col))
		{
			std::vector<uint8_t> row;
			for (char chr : col)
			{
				switch (chr)
				{
					case '0':
					{
						row.push_back(0);
						break;
					}
					case 'i':
					{
						row.push_back(1);
						break;
					}
					case 'w':
					{
						row.push_back(2);
						break;
					}
					case 's':
					{
						row.push_back(3);
						break;
					}
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
	}
}

void TileSet::render(SDL_Renderer* renderer, Camera cam, int tileSize)
{
	for (int i = 0; i < width; i++)
	{
		for (int k = 0; k < height; k++) {
			tileSprites[levelLayout[k][i]]->render(tileSize * i - cam.getX(), tileSize * k - cam.getY(), cam.getScale(), renderer);
		}
	}
}
