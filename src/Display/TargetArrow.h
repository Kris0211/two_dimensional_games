#pragma once
#include "../Pawn/ArrowsPlayer.h"
#include "../Pawn/KeyboardPlayer.h"
#include "../Pawn/Target.h"

class Camera;
class Sprite;

class TargetArrow
{
public:

	TargetArrow(Sprite* sprite, Target* target) : sprite(sprite), target(target) {}

	void render(SDL_Renderer* renderer, SDL_Window* window, const Camera &cam);

private:
	Sprite* sprite;
	Target* target;

};