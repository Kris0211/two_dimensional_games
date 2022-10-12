#include <cstdio>
#include <chrono>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "AnimSprite.h"
#include "PlayerCharacter.h"
#include "Sprite.h"
#include "Vector2D.h"

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

	window = SDL_CreateWindow("Zadanie 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void updateSpritePosition(SDL_Rect& rect, int x, int y)
{
	rect.x = x;
	rect.y = y;
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

	Sprite amogus;
	Sprite godot;
	Sprite qwadrat;
	Sprite cirkle;

	AnimSprite glider;

	PlayerCharacter player1(&qwadrat, Vector2D(80, 60));
	PlayerCharacter player2(&cirkle, Vector2D(400, 300));

	if (!amogus.loadFromFile("res/sus.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!godot.loadFromFile("res/icon.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!qwadrat.loadFromFile("res/red.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	if (!cirkle.loadFromFile("res/rednt.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
		return -2;
	}

	constexpr int GLIDER_FRAME_SIZE = 48;
	constexpr int GLIDER_FRAME_COUNT = 4;
	if (!glider.loadFromFile("res/glider.png", defaultRenderer, GLIDER_FRAME_SIZE, GLIDER_FRAME_COUNT))
	{
		printf("Failed to load animated sprite texture!\n");
		return -3;
	}

	// Delta time
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime;

	// Animation variables
	int offset = 128;
	bool returning = false;
	Uint64 gliderFrames = 0;

	SDL_Event event;
	bool run = true;

	// Main game loop
	while (run) 
	{
		//keep window
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) run = false;

		//calculate delta
		{
			Uint64 last = now;
			now = SDL_GetPerformanceCounter();
			deltaTime = static_cast<double>((now - last) * 1000) / static_cast<double>(SDL_GetPerformanceFrequency());
		}

		// change sprite offset to simulate movement
		if (offset >= 128)
		{
			returning = true;
		}
		else if (offset <= 0)
		{
			returning = false;
		}
		offset += returning ? -1 : 1;

		//Background color
		SDL_SetRenderDrawColor(defaultRenderer, 0x48, 0x72, 0x8C, 0xFF);
		SDL_RenderClear(defaultRenderer);

		//Render sprites
		constexpr int GLIDER_ANIM_SPEED_DELAY = 30;
		//amogus.render(256, 128 + offset, defaultRenderer); //adding offset simulates movement
		//godot.render(320, 480, defaultRenderer);
		//glider.render(256 - offset * 2, 256 - offset * 2, static_cast<int>((++gliderFrames / GLIDER_ANIM_SPEED_DELAY) % GLIDER_FRAME_COUNT), defaultRenderer);

		player1.render(defaultRenderer);
		player2.render(defaultRenderer);

		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	glider.free();
	godot.free();
	amogus.free();
	close();

	return 0;
}
