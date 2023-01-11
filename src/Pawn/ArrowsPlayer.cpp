#include "ArrowsPlayer.h"

ArrowsPlayer::ArrowsPlayer(Sprite* sprite, const Vector2D& pos, CollisionBody* collider)
	: Character(sprite, pos, collider) { charName = "Player2"; }

void ArrowsPlayer::move(double deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
	velocity.x = static_cast<float>(keyboard[SDL_SCANCODE_RIGHT] - keyboard[SDL_SCANCODE_LEFT]);
	velocity.y = gravity;
	velocity.normalize();
	velocity *= speed * static_cast<float>(deltaTime);
	position += velocity;
}