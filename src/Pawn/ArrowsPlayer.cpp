#include "ArrowsPlayer.h"

ArrowsPlayer::ArrowsPlayer(Sprite* sprite, const Vector2D& pos, CollisionBody* collider)
	: Character(sprite, pos, collider) {}

void ArrowsPlayer::move(double deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
	velocity.x = static_cast<float>(keyboard[SDL_SCANCODE_RIGHT] - keyboard[SDL_SCANCODE_LEFT]);
	velocity.y = static_cast<float>(keyboard[SDL_SCANCODE_DOWN] - keyboard[SDL_SCANCODE_UP]);
	velocity.normalize();
	velocity *= speed * deltaTime;
	position += velocity;
}