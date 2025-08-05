#pragma once

#include "Actor/Actor.h"

class Trap : public Actor
{
	RTTI_DECLARATIONS(Trap, Actor)

public:
	Trap(const Vector2F& Position);
	~Trap();

private:

};