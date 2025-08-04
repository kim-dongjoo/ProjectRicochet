#pragma once

#include "Level/Level.h"
#include "Interface/IEnvironmentQuery.h"


class RicochetLevel : public Level, public IEnvironmentQuery
{
	RTTI_DECLARATIONS(RicochetLevel, Level)

public:
	RicochetLevel();

	virtual void Tick(float DeltaTime) override;
	virtual void Render() override;

	// IEnvironmentQuery��(��) ���� ��ӵ�
	virtual Vector2F FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection) override;

	// IEnvironmentQuery��(��) ���� ��ӵ�
	virtual void SetGameClear(const Vector2F& PlayerPosition) override;

	// IEnvironmentQuery��(��) ���� ��ӵ�
	virtual void SetGameOver() override;

private:
	void ReadMapFile(const char* filename);

private:
	// ���� Ŭ���� ���� Ȯ�� ����
	bool isGameClear = false;

	// ���� ���� ���� Ȯ�� ����
	bool isGameOver = false;

	// �� ��ġ
	Vector2F GoalPosition;
};