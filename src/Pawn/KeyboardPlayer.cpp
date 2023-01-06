#include "KeyboardPlayer.h"

KeyboardPlayer::KeyboardPlayer(Sprite* sprite, const Vector2D& pos, CollisionBody* collider) 
	: Character(sprite, pos, collider) {}

void KeyboardPlayer::move(double deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
	velocity.x = static_cast<float>(keyboard[SDL_SCANCODE_D] - keyboard[SDL_SCANCODE_A]);
	velocity.y = static_cast<float>(keyboard[SDL_SCANCODE_S] - keyboard[SDL_SCANCODE_W]);
	velocity.normalize();
	velocity *= speed * deltaTime;
	position += velocity;
}