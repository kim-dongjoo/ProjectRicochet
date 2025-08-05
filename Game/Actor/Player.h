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

private:
	// �ӷ�. �ʴ� �� ĭ�� �̵��ϴ���
	float MoveSpeed = 3.0f;

	// �̵� ����
	EDirection MoveDirection;

	// �̵� ������
	bool IsMoving = false;

	int MoveCount = 100;

	// ȯ�� ���� �������̽�
	class IEnvironmentQuery* EQInterface = nullptr;
};