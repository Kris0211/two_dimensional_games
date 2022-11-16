#include <cstdio>
#include <chrono>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>

#include "AnimSprite.h"
#include "Ball.h"
#include "Camera.h"
#include "MultiplayerCamera.h"
#include "PlayerCharacter.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Vector2D.h"

constexpr int TILE_SIZE = 64;
constexpr int TILEMAP_WIDTH = 42;
constexpr int TILEMAP_HEIGHT = 21;
const int TOTAL_TILES = TILEMAP_WIDTH * TILEMAP_HEIGHT;
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

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
	srand(time(NULL));

	if (!init())
	{
		printf("Initialization failed: %s\n", SDL_GetError());
		return -1;
	}

	Sprite zbysiu;
	if (!zbysiu.loadFromFile("res/img/dramat.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	Sprite saul;
	if (!saul.loadFromFile("res/img/saul_but_ball.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	Sprite mpostol;
	if (!mpostol.loadFromFile("res/img/postolball.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	//Ball stonogaball(defaultRenderer, &zbysiu, Vector2D(0, 0));
	//Ball goodmanball(defaultRenderer, &saul, Vector2D(0, 0));

	Ball* balls[8];

	Vector2D why[8] { Vector2D(-2, -1.5), Vector2D(-2, 0), Vector2D(-2, 1.5),
		Vector2D(0, -1.5), Vector2D(0, 1.5),
		Vector2D(2, -1.5), Vector2D(2, 0), Vector2D(2, 1.5) 
	};

	for (int i = 0; i < 8; i++) 
	{
		balls[i] = new Ball(defaultRenderer, &mpostol, Vector2D(400, 300), why[i]);
	}

	/*
	Sprite amogus;
	Sprite godot;
	Sprite saul;
	Sprite thevoid;
	Sprite walter;
	Sprite qwadrat;
	Sprite cirkle;
	Sprite froge;

	AnimSprite glider;

	PlayerCharacter player1(&froge, Vector2D(400.0, 300.0));
	PlayerCharacter player2(&amogus, Vector2D(500.0, 300.0));

	std::vector<Sprite*> spritemap = { &thevoid, &godot, &walter, &walter };

	TileSet tilemap(spritemap, "res/lvl/level1.lvl", TILEMAP_WIDTH, TILEMAP_HEIGHT);

	player1.setMovementSpeed(4.0);
	player2.setMovementSpeed(1.5);

	if (!amogus.loadFromFile("res/img/amogi.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!godot.loadFromFile("res/img/icon.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!qwadrat.loadFromFile("res/img/red.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cirkle.loadFromFile("res/img/rednt.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!saul.loadFromFile("res/img/saul.png", defaultRenderer)) {
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

	constexpr int GLIDER_FRAME_SIZE = 48;
	constexpr int GLIDER_FRAME_COUNT = 4;
	if (!glider.loadFromFile("res/img/glider.png", defaultRenderer, GLIDER_FRAME_SIZE, GLIDER_FRAME_COUNT))
	{
		printf("Failed to load animated sprite texture!\n");
		return -3;
	}
	*/
	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;

	// Animation variables
	//int offset = 128;
	//bool returning = false;
	//Uint64 gliderFrames = 0;

	//Camera cam(&player1, window);
	//MultiplayerCamera cam(&player1, &player2, window);

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
			// Close game on quit
			if (event.type == SDL_QUIT) run = false;
		}

		//player1.move(deltaTime);
		//cam.run(deltaTime);
		//player2.smoothMove(deltaTime);

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
		//tilemap.render(defaultRenderer, cam);
		 
		//Render sprites
		//constexpr int GLIDER_ANIM_SPEED_DELAY = 30;
		//amogus.render(256, 128 + offset, defaultRenderer); //adding offset simulates movement
		//godot.render(320, 480, defaultRenderer);
		//glider.render(256 - offset * 2, 256 - offset * 2, static_cast<int>((++gliderFrames / GLIDER_ANIM_SPEED_DELAY) % GLIDER_FRAME_COUNT), defaultRenderer);

		//player1.render(defaultRenderer, cam);
		//player2.render(defaultRenderer, cam);

		for (Ball* ball : balls)
			ball->move();

		//stonogaball.move();
		//goodmanball.move();

		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	/*
	cam.free();
	player2.free();
	player1.free();
	saul.free();
	walter.free();
	glider.free();
	godot.free();
	amogus.free();
	tilemap.free();
	*/
	close();

	return 0;
}
