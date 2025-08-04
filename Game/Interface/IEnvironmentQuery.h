#pragma once

#include "Math/Vector2F.h"

// 플레이어가 이동할 수 있는지 확인할 때 사용할 인터페이스.
class IEnvironmentQuery
{
public:
	// 이동 동선에서 가장 멀리 있는 위치를 반환
	virtual Vector2F FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection) = 0;

	virtual void SetGameClear(const Vector2F& PlayerPosition) = 0;

	virtual void SetGameOver() = 0;
};