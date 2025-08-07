#pragma once

#include "Actor/Actor.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(const Vector2F& position);

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

	void SetMoveDirection(EDirection MoveDirection);

	bool GetIsBounced() const;

private:
	// 속력. 초당 몇 칸을 이동하는지
	float MoveSpeed = 3.0f;

	// 이동 방향
	EDirection MoveDirection;

	// 이동 중인지
	bool IsMoving = false;

	// 튕겼는지
	bool IsBounced = false;

	int MoveCount = 25;

	// 환경 쿼리 인터페이스
	class IEnvironmentQuery* EQInterface = nullptr;
};