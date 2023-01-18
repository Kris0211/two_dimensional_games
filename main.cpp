#include <cstdio>
#include <chrono>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "src/Collision/Box.h"
#include "src/Display/Sprite.h"
#include "src/Display/TileSet.h"
#include "src/Math/Vector2D.h"
#include "src/Pawn/Character.h"
#include "src/Pawn/KeyboardPlayer.h"
#include "Config.h"
#include "src/Collision/CollisionManager.h"

SDL_Window* window = nullptr;
SDL_Surface* bg = nullptr;
SDL_Renderer* defaultRenderer = nullptr;

double jumpHeight = JUMP_HEIGHT;
double jumpRange = JUMP_RANGE;
double jumpTime = JUMP_TIME;

double parallaxFg = PARALLAX_FOREGROUND;
double parallaxBg = PARALLAX_BACKGROUND;

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

	window = SDL_CreateWindow("Zadanie 9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	Sprite sky;
	Sprite cobble;
	Sprite cloudLeft;
	Sprite cloudMid;
	Sprite cloudRight;

	if (!walterbox.loadFromFile("res/img/heisenberg_medium.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!sky.loadFromFile("res/img/sky.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cobble.loadFromFile("res/img/cobblestone.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cloudLeft.loadFromFile("res/img/cloud_l.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cloudMid.loadFromFile("res/img/cloud_m.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cloudRight.loadFromFile("res/img/cloud_r.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}
	
	std::vector<Sprite*> gameplayTileMap = { &sky, &cobble, };
	std::vector<bool> gameplayTileColliders = { false, true };

	std::vector<Sprite*> cloudsTileMap = { &cloudLeft, &cloudMid, &cloudRight };
	std::vector<bool> cloudsTileColliders = { false, false, false };

		
	KeyboardPlayer player1(&walterbox, Vector2D(128.0f, 128.0f), new Box(Vector2D(56.0f, 56.0f), true));

	TileSet level(gameplayTileMap, gameplayTileColliders, "res/lvl/level.lvl");
	level.generateCollision();

	TileSet clouds(cloudsTileMap, cloudsTileColliders, "res/lvl/clouds.lvl");
	clouds.setParallaxOffset(Vector2D(-1512.0f, -128.0f));

	Camera cam(&player1, window);

	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;
	
	SDL_Event event;
	bool run = true;

	player1.calculatePhysics(jumpHeight, jumpRange);

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

			// Jump logic
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_w)
				{
					player1.jump();
				}
				if (event.key.keysym.sym == SDLK_1)
				{
					parallaxFg += 0.1;
					std::cout << "Parallax Foreground: " << parallaxFg << "\n";
					//foreground.parallaxScale.x = paralaxFg;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					parallaxFg -= 0.1;
					std::cout << "Parallax Foreground: " << parallaxFg << "\n";
					//foreground.parallaxScale.x = paralaxFg;
				}
				if (event.key.keysym.sym == SDLK_3)
				{
					parallaxBg += 0.1;
					std::cout << "Parallax Background: " << parallaxBg << "\n";
					//background.parallaxScale.x = paralaxBg;
				}
				if (event.key.keysym.sym == SDLK_4)
				{
					parallaxBg -= 0.1;
					std::cout << "Parallax Background: " << parallaxBg << "\n";
					//background.parallaxScale.x = paralaxBg;
				}
				if (event.key.keysym.sym == SDLK_r)
				{
					player1.position = Vector2D(128.0f, 128.0f);
				}
			}
		}
		
		//Background color
		SDL_SetRenderDrawColor(defaultRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(defaultRenderer);

		player1.move(deltaTime);
		cam.run();

		CollisionManager::handleCollisions();

		//Render level
		level.render(defaultRenderer, cam);

		//Render players
		player1.render(defaultRenderer, cam);
				
		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	cam.free();
	player1.free();

	walterbox.free();
	sky.free();
	cobble.free();

	close();
	return 0;
}
