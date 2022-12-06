#include <cstdio>
#include <chrono>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>

#include "src/AnimSprite.h"
#include "src/Ball.h"
#include "src/MultiplayerCamera.h"
#include "src/PlayerCharacter.h"
#include "src/Sprite.h"
#include "src/TileSet.h"
#include "src/Vector2D.h"

constexpr int TILE_SIZE = 64;
constexpr int TILEMAP_WIDTH = 42;
constexpr int TILEMAP_HEIGHT = 21;
const int TOTAL_TILES = TILEMAP_WIDTH * TILEMAP_HEIGHT;
constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 900;

SDL_Window* window = nullptr;
SDL_Surface* bg = nullptr;
SDL_Renderer* defaultRenderer = nullptr;

/**
 * \brief Loads and optimizes a surface
 * \param pathTo Path to an image file
 * \return Ready to use optimized surface
 */
SDL_Surface* loadSurface(std::string pathTo)
{
	SDL_Surface* optimizedSurface = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(pathTo.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", pathTo.c_str(), SDL_GetError());
		return nullptr;
	}

	optimizedSurface = SDL_ConvertSurface(loadedSurface, bg->format, 0);
	if (optimizedSurface == nullptr)
	{
		printf("Unable to optimize image %s! SDL Error: %s\n", pathTo.c_str(), SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

/**
 * \brief Loads a texture from a file
 * \param pathTo Path to the file with texture
 * \return Loaded SDL_Texture ready to use
 */
SDL_Texture* loadTexture(std::string pathTo)
{
	// load image
	SDL_Texture* texture = IMG_LoadTexture(defaultRenderer, pathTo.c_str());
	if (texture == nullptr) {
		printf("Unable to create texture from %s!\nSDL Error: %s\n", pathTo.c_str(), SDL_GetError());
	}
	
	return texture;
}

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

	Sprite amogus;
	Sprite saul;
	Sprite saulball;
	Sprite godot;
	Sprite thevoid;
	Sprite walter;
	Sprite qwadrat;
	Sprite cirkle;
	Sprite froge;

	if (!amogus.loadFromFile("res/img/amogi.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!saul.loadFromFile("res/img/saul.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!saulball.loadFromFile("res/img/saul_but_ball.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cirkle.loadFromFile("res/img/rednt.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!thevoid.loadFromFile("res/img/void.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!walter.loadFromFile("res/img/walter.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!froge.loadFromFile("res/img/froggo.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!godot.loadFromFile("res/img/icon.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}
	/*
	const std::vector<Sprite*> sprites = { &saul };

	std::vector<Ball*> balls;

	Vector2D why[8]{Vector2D(-4, -3), Vector2D(-4, 0), Vector2D(-4, 3),
		Vector2D(0, -3), Vector2D(0, 3),
		Vector2D(4, -3), Vector2D(4, 0), Vector2D(4, 3) 
	};

	srand(time(nullptr));

	for (int i = 0; i < 16; i++) 
	{
		int vecx, vecy;
		do {
			 vecx = (rand() % 2) - 2;
			 vecy = (rand() % 2) - 2;
		} while (vecx == 0 || vecy == 0);
		Vector2D velctor(vecx, vecy);
		balls.push_back(new Ball(defaultRenderer, sprites[i % sprites.size()], Vector2D(400, 300), velctor));
	}
	*/
	
	PlayerCharacter player1(&saul, Vector2D(400.0, 300.0));
	PlayerCharacter player2(&saulball, Vector2D(500.0, 300.0));

	std::vector<Sprite*> spritemap = { &thevoid, &godot, &walter, &walter };

	TileSet tilemap(spritemap, "res/lvl/level1.lvl", TILEMAP_WIDTH, TILEMAP_HEIGHT);

	player1.setMovementSpeed(2.0f);
	player2.setMovementSpeed(2.0f);

	/*
	AnimSprite glider;
	
	constexpr int GLIDER_FRAME_SIZE = 48;
	constexpr int GLIDER_FRAME_COUNT = 4;
	if (!glider.loadFromFile("res/img/glider.png", defaultRenderer, GLIDER_FRAME_SIZE, GLIDER_FRAME_COUNT))
	{
		printf("Failed to load animated sprite texture!\n");
		return -3;
	}
	*/

	// Animation variables
	//int offset = 128;
	//bool returning = false;
	//Uint64 gliderFrames = 0;

	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;
	
	MultiplayerCamera cam(&player1, &player2, window);

	// Collision variables
	bool separation = true;
	bool reflection = true;

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
		{	/*
			if (event.type == SDL_KEYDOWN)
			{
				printf("%s PRESSED\n", SDL_GetScancodeName(event.key.keysym.scancode));
			}
			if (event.type == SDL_KEYUP)
			{
				printf("%s RELEASED\n", SDL_GetScancodeName(event.key.keysym.scancode));
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				printf("Mouse position: [x:%d] [y:%d]\n", x, y);
			}
			*/
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_1)
				{
					separation = !separation;
					if (separation)
					{
						printf("Separation enabled\n");
					}
					else
					{
						printf("Separation disabled\n");
					}
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					reflection = !reflection;
					if (reflection)
					{
						printf("Reflection enabled\n");
					}
					else
					{
						printf("Reflection disabled\n");
					}
				}

			}
			// Close game on quit
			if (event.type == SDL_QUIT) run = false;
		}

		player1.move(deltaTime, false);
		player2.move(deltaTime, true);
		cam.run(deltaTime);

		//Change sprite offset to simulate movement
		/*if (offset >= 128)
		{
			returning = true;
		}
		else if (offset <= 0)
		{
			returning = false;
		}
		offset += returning ? -1 : 1;*/

		//RENDERING
		//Background color
		SDL_SetRenderDrawColor(defaultRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(defaultRenderer);

		// Render tilemap
		tilemap.render(defaultRenderer, cam);
		 
		//Render sprites
		//constexpr int GLIDER_ANIM_SPEED_DELAY = 30;
		//amogus.render(256, 128 + offset, defaultRenderer); //adding offset simulates movement
		//godot.render(320, 480, defaultRenderer);
		//glider.render(256 - offset * 2, 256 - offset * 2, static_cast<int>((++gliderFrames / GLIDER_ANIM_SPEED_DELAY) % GLIDER_FRAME_COUNT), defaultRenderer);

		player1.render(defaultRenderer, cam);
		player2.render(defaultRenderer, cam);

		// Render balls
		/*{
			for (Ball* ball : balls)
			{
				ball->move(deltaTime);
			}

			for (Ball* ball : balls)
			{
				ball->touch(balls, separation, reflection);
			}

			for (Ball* ball : balls)
			{
				ball->render();
			}
		}*/
		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	cam.free();
	player2.free();
	player1.free();
	saul.free();
	walter.free();
	//glider.free();
	godot.free();
	amogus.free();
	tilemap.free(); 
	close();

	return 0;
}
