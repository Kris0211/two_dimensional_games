#include <cstdio>
#include <chrono>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

#include "src/Collision/Ball.h"
#include "src/Camera/MultiplayerCamera.h"
#include "src/Display/Sprite.h"
#include "src/Display/TileSet.h"
#include "src/Math/Vector2D.h"
#include "src/Pawn/Character.h"
#include "src/Pawn/KeyboardPlayer.h"
#include "src/Pawn/ArrowsPlayer.h"

constexpr int TILE_SIZE = 64;
constexpr int TILEMAP_WIDTH = 20;
constexpr int TILEMAP_HEIGHT = 20;
const int TOTAL_TILES = TILEMAP_WIDTH * TILEMAP_HEIGHT;
constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 800;

SDL_Window* window = nullptr;
SDL_Surface* bg = nullptr;
SDL_Renderer* defaultRenderer = nullptr;

/**
 * \brief Initialize the game window
 * \return True on successful init, otherwise false
 */
bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Zadanie 6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Failed to create a window! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	defaultRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (defaultRenderer == nullptr)
	{
		printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

/**
 * \brief Closes all resources and terminates SDL
 */
void close()
{
	SDL_DestroyWindow(window);
	window = nullptr;
	bg = nullptr;
	defaultRenderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!init())
	{
		printf("Initialization failed: %s\n", SDL_GetError());
		return -1;
	}
	
	Sprite walterbox;
	Sprite saulball;
	Sprite grass;
	Sprite cobble;

	if (!saulball.loadFromFile("res/img/saul_but_ball.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!walterbox.loadFromFile("res/img/heisenberg.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!grass.loadFromFile("res/img/grass.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cobble.loadFromFile("res/img/cobblestone.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}
	
	KeyboardPlayer player1(&walterbox, Vector2D(400.0, 300.0));
	ArrowsPlayer player2(&saulball, Vector2D(500.0, 300.0));

	std::vector<Sprite*> spritemap = { &grass, &cobble };

	TileSet tilemap(spritemap, "res/lvl/level2.lvl", TILEMAP_WIDTH, TILEMAP_HEIGHT);

	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;
	
	MultiplayerCamera cam(&player1, &player2, window);

	SDL_Event event;
	bool run = true;

	// Main game loop
	while (run)
	{
		//Calculate delta
		Uint64 last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = static_cast<double>((now - last) * 1000) / static_cast<double>(SDL_GetPerformanceFrequency());
		
		//Input processing
		while (SDL_PollEvent(&event))
		{
			// Close game on quit
			if (event.type == SDL_QUIT) run = false;
		}

		player1.move(deltaTime);
		player2.move(deltaTime);
		cam.run(deltaTime);

		//RENDERING
		//Background color
		SDL_SetRenderDrawColor(defaultRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(defaultRenderer);

		// Render tilemap
		tilemap.render(defaultRenderer, cam);
		 
		// Render players
		player1.render(defaultRenderer, cam);
		player2.render(defaultRenderer, cam);

		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	cam.free();
	player2.free();
	player1.free();

	walterbox.free();
	saulball.free();
	grass.free();
	cobble.free();
	
	tilemap.free();

	close();
	return 0;
}
