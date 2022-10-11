#include <cstdio>
#include <chrono>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

	defaultRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

	Sprite amogus, godot;

	if (!amogus.loadFromFile("res/sus.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
	}

	if (!godot.loadFromFile("res/icon.png", defaultRenderer)) {
		printf("Failed to load sprite texture!\n");
	}

	//delta time
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double _delta = 0;

	SDL_Rect SpriteRect;
	SpriteRect.x = 64;
	SpriteRect.y = 64;

	//keep window
	SDL_Event event;
	bool quit = false;
	int offset = 128;
	bool returning = false;
	bool run = true;
	// main game loop
	while (run) 
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) run = false;

		//calculate delta
		{
			last = now;
			now = SDL_GetPerformanceCounter();
			_delta = static_cast<double>((now - last) * 1000) / static_cast<double>(SDL_GetPerformanceFrequency());
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
		amogus.render(256, 128 + offset, defaultRenderer); //adding offset simulates movement
		godot.render(64, 64, defaultRenderer);

		//Updates screen after render
		SDL_RenderPresent(defaultRenderer);
	}
	
	// Clean up before closing
	godot.free();
	amogus.free();
	close();

	return 0;
}

