#include "Tile.h"
#include <iostream>

const int TILE_SIZE = 64;

Tile::Tile(int x, int y, char type)
{
	box.x = x;
	box.y = y;
	box.w = TILE_SIZE;
	box.h = TILE_SIZE;
	this->type = type;
}

void Tile::render(SDL_Rect& camera)
{
	std::cerr<< "Not implemented yet.\n";
}

char Tile::getType() { return type; }

