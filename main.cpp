#include <cstdio>
#include <chrono>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

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

	SDL_Surface* loadedSurface = SDL_LoadBMP(pathTo.c_str());
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
	SDL_Texture* texture = nullptr;

	// load image
	SDL_Surface* loadedSurface = IMG_Load(pathTo.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s!\nSDL_image Error: %s\n", pathTo.c_str(), IMG_GetError());
	}

	// create texture
	texture = SDL_CreateTextureFromSurface(defaultRenderer, loadedSurface);
	if (texture == nullptr) {
		printf("Unable to create texture from %s!\nSDL Error: %s\n", pathTo.c_str(), SDL_GetError());
	}

	// free surface since it is no longer needed
	SDL_FreeSurface(loadedSurface);

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

	bg = SDL_GetWindowSurface(window);
	SDL_FillRect(bg, 0, SDL_MapRGB(bg->format, 0x48, 0x72, 0x8C));
	SDL_UpdateWindowSurface(window);

	return true;
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
	srand(time(nullptr));  // NOLINT(clang-diagnostic-shorten-64-to-32)
	
	if (!init())
	{
		printf("Initialization failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Rect SpriteRect;
	SpriteRect.x = 64;
	SpriteRect.y = 64;

	SDL_Texture* amogus = loadTexture("res/sus.png");
	if (amogus == nullptr)
	{
		printf("Failed to load texture image!\n");
		return 3;
	}

	SDL_Texture* godot = loadTexture("res/icon.png");
	if (godot == nullptr)
	{
		printf("Failed to load texture image!\n");
		return 3;
	}

	//delta time
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	double _delta = 0;

	//keep window
	SDL_Event event;
	bool quit = false;
	while (!quit) {

		last = now;
		now = SDL_GetPerformanceCounter();
		_delta = static_cast<double>((now - last) * 1000) / static_cast<double>(SDL_GetPerformanceFrequency());

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			SDL_RenderClear(defaultRenderer); //Clears the screen
			SDL_RenderCopy(defaultRenderer, amogus, 0, 0); //Renders textures to sceen
			SDL_RenderCopy(defaultRenderer, godot, 0, 0);
			SDL_RenderPresent(defaultRenderer); //Updates screen after render
		}
	}

	SDL_DestroyTexture(godot);
	godot = nullptr;
	SDL_DestroyTexture(amogus);
	godot = nullptr;

	close();

	return 0;
}
