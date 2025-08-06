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

	//============== IEnvironmentQuery을(를) 통해 상속됨======================
	virtual Vector2F FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection) override;
	virtual bool SetGameClear(const Vector2F& PlayerPosition) override;
	virtual void SetGameOver() override;
	virtual bool IsOnTrap(const Vector2F& PlayerPosition) override;
	// =================================================================

private:
	void ReadMapFile(const char* filename);

private:
	// 게임 클리어 여부 확인 변수
	bool isGameClear = false;

	// 게임 오버 여부 확인 변수
	bool isGameOver = false;

	// 골 위치
	Vector2F GoalPosition;

	Vector2F PatrolStartPosition;
	Vector2F PatrolEndPosition;
};