#pragma once

#include "Actor/Actor.h"

class MovingWall : public Actor
{
	RTTI_DECLARATIONS(MovingWall, Actor)

public:
	MovingWall(const Vector2F& StartPosition, const Vector2F& EndPosition, EDirection MoveDirection);

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	const float GetMoveSpeed();

private:
	EDirection MoveDirection = EDirection::None;

	float MoveSpeed = 3.0f;

	Vector2F PatrolStartPosition;
	Vector2F PatrolEndPosition;
	EDirection StartDirection;
};