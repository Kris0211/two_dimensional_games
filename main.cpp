#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Surface* object = nullptr;
SDL_Surface* godot = nullptr;

bool printError()
{
	printf("SDL Error: %s\n", SDL_GetError());
	return false;
}

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = printError();
	}
	else
	{
		window = SDL_CreateWindow("Zadanie 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window != NULL)
		{
			surface = SDL_GetWindowSurface(window);
		}
		else
		{
			success = printError();
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	object = SDL_LoadBMP("res/sus.bmp");
	godot = SDL_LoadBMP("res/icon.bmp");
	if (object == nullptr || godot == nullptr)
	{
		success = printError();
	}

	return success;
}

void close()
{
	SDL_FreeSurface(godot);
	godot = nullptr;

	SDL_FreeSurface(object);
	object = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char* argv[])
{
	int retCode = 0;

	if (init())
	{
		if (loadMedia())
		{
			SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, 0x48, 0x72, 0x8C));

			SDL_BlitSurface(object, 0, surface, 0);

			SDL_UpdateWindowSurface(window);

			SDL_Event event;
			bool quit = false;
			while (!quit) {
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
		else
		{
			printf("Failed to load media.");
			retCode = 21;
		}
	}
	else
	{
		printf("Initialization failed.\n");
		retCode = -1;
	}

	close();

	return retCode;
}
