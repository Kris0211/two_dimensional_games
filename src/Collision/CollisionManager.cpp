#include "CollisionManager.h"


void CollisionManager::handleCollisions()
{
	for (CollisionBody* collider : colliders)
	{
		if (collider->isRigid())
		{
			collider->collide(true, false);
		}
	}
}

void CollisionManager::addCollider(CollisionBody* collisionBody)
{
	colliders.push_back(collisionBody);
}

void CollisionManager::removeCollider(CollisionBody* collisionBody)
{
	colliders.erase(std::remove(colliders.begin(), colliders.end(), collisionBody), 
		colliders.end());
}

std::vector<CollisionBody*> CollisionManager::colliders;
