#pragma once

#include "Actor/Actor.h"

class Goal : public Actor
{
	RTTI_DECLARATIONS(Goal, Actor)

public:
	Goal(const Vector2F& position);
};