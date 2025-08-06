#pragma once

#include "Math/Vector2F.h"

// �÷��̾ �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�.
class IEnvironmentQuery
{
public:
	// �̵� �������� ���� �ָ� �ִ� ��ġ�� ��ȯ
	virtual Vector2F FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection, float DeltaTime) = 0;

	virtual bool SetGameClear(const Vector2F& PlayerPosition) = 0;

	virtual void SetGameOver() = 0;

	virtual bool IsOnTrap(const Vector2F& PlayerPosition) = 0;
};