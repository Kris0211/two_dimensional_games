#pragma once
class CollisionBody
{
public:
	virtual void collide(bool separation, bool reflection) = 0;
};

