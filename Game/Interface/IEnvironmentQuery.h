#pragma once

#include "Math/Vector2F.h"

// �÷��̾ �̵��� �� �ִ��� Ȯ���� �� ����� �������̽�.
class IEnvironmentQuery
{
public:
	// �̵� �������� ���� �ָ� �ִ� ��ġ�� ��ȯ
	virtual Vector2F FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection) = 0;

	virtual void SetGameClear(const Vector2F& PlayerPosition) = 0;

	virtual void SetGameOver() = 0;
};