#include "TargetArrow.h"

#include "../Camera/Camera.h"
#include "Sprite.h"

#define PI 3.1415

void TargetArrow::render(SDL_Renderer* renderer, SDL_Window* window, const Camera &cam)
{
	int windowSizeX, windowSizeY;
	SDL_GetWindowSize(window, &windowSizeX, &windowSizeY);
	
	if (target->position.x > (cam.getX() - windowSizeX) * cam.getZoom() || target->position.x < (cam.getX() + windowSizeX) * cam.getZoom()
		|| target->position.y >(cam.getY() - windowSizeY) * cam.getZoom() || target->position.y < (cam.getY() + windowSizeY) * cam.getZoom())
	{
		double angle = Vector2D::angleBetween((target->position - cam.getPosition()), Vector2D(0, -1)) * 180 / PI;
		sprite->render(windowSizeX * 0.5, windowSizeY * 0.5, 1.0f, angle - 90, renderer);
	}

}