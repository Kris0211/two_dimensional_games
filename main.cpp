#include <cstdio>
#include <chrono>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>

#include "src/Collision/Ball.h"
#include "src/Camera/MultiplayerCamera.h"
#include "src/Collision/Box.h"
#include "src/Display/Sprite.h"
#include "src/Display/TileSet.h"
#include "src/Math/Vector2D.h"
#include "src/Pawn/Character.h"
#include "src/Pawn/KeyboardPlayer.h"
#include "src/Pawn/ArrowsPlayer.h"
#include "Config.h"
#include "src/Collision/CollisionManager.h"
#include "src/Display/TargetArrow.h"
#include "src/Level/LevelGenerator.h"
#include "src/Pawn/Target.h"

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

	window = SDL_CreateWindow("Zadanie 7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	Sprite coin;
	Sprite grass;
	Sprite cobble;
	Sprite arrow;

	if (!saulball.loadFromFile("res/img/saulball_small.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!walterbox.loadFromFile("res/img/heisenberg_small.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!coin.loadFromFile("res/img/coin.png", defaultRenderer)) {
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

	if (!arrow.loadFromFile("res/img/arrow.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}
	
	std::vector<Sprite*> tileMap = { &cobble, &grass };
	std::vector<bool> tileColliders = { true, false };

	LevelGenerator level(tileMap, tileColliders, defaultRenderer);
	level.generateLevel(10);
	
	KeyboardPlayer player1(&walterbox, Vector2D(400.0, 300.0), new Box(Vector2D(50.0f, 50.0f), true));
	ArrowsPlayer player2(&saulball, Vector2D(500.0, 300.0), new Ball(20.0f, true));
	Target target(&coin, new Ball(40.0f, true), &player1, &player2, &level);

	TargetArrow targetArrow(&arrow, &target);
	MultiplayerCamera cam(&player1, &player2, window);
	
	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;
	
	SDL_Event event;
	bool run = true;

	srand(time(nullptr));
	target.nextLevel();

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
		
		//Background color
		SDL_SetRenderDrawColor(defaultRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(defaultRenderer);

		player1.move(deltaTime);
		player2.move(deltaTime);
		cam.run();

		CollisionManager::handleCollisions();

		// Render players
		level.render(defaultRenderer, cam);
		player1.render(defaultRenderer, cam);
		player2.render(defaultRenderer, cam);
		target.render(defaultRenderer, cam);
		//targetArrow.render(defaultRenderer, window, cam); //This does not work as it should.

		if (target.touched) target.nextLevel();

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

	close();
	return 0;
}
