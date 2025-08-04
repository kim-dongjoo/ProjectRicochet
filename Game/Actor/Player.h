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

private:
	// �ӷ�. �ʴ� �� ĭ�� �̵��ϴ���
	float MoveSpeed = 3.0f;

	// �̵� ����
	EDirection MoveDirection;

	// �̵� ������
	bool IsMoving = false;

	int MoveCount = 5;

	// ȯ�� ���� �������̽�
	class IEnvironmentQuery* EQInterface = nullptr;
};