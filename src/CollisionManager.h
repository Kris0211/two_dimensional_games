#pragma once

#include <vector>
#include "CollisionBody.h"

class CollisionManager
{
public:
	static void handleCollisions();
	static void addCollider(CollisionBody* collisionBody);
	static void removeCollider(CollisionBody* collisionBody);

	static std::vector<CollisionBody*> colliders;
};

