#include "MovingWall.h"
#include <algorithm>

MovingWall::MovingWall(const Vector2F& StartPosition, const Vector2F& EndPosition, EDirection MoveDirection)
	: Actor('E', Color::Red, StartPosition)
	, MoveDirection(MoveDirection)
	, StartDirection(MoveDirection)
	, PatrolStartPosition(StartPosition)
	, PatrolEndPosition(EndPosition)
{
	SetRenderSortingOrder(3);
}

void MovingWall::BeginPlay()
{
}

void MovingWall::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	float MoveDistance = MoveSpeed * deltaTime;

	if (MoveDirection == EDirection::RIGHT)
	{
		Vector2F ResultPosition;

		if (MoveDirection == StartDirection) // StartPosition -> EndPosition
		{
			// min 함수로 도착 지점을 넘어가지 않도록
			ResultPosition = Vector2F(min(GetPosition().x + MoveDistance, PatrolEndPosition.x), GetPosition().y);
			if (ResultPosition == PatrolEndPosition)
				MoveDirection = EDirection::LEFT;
		}
		else // // EndPosition -> StartPosition
		{
			// min 함수로 시작 지점을 넘어가지 않도록
			ResultPosition = Vector2F(min(GetPosition().x + MoveDistance, PatrolStartPosition.x), GetPosition().y);
			if (ResultPosition == PatrolStartPosition)
				MoveDirection = EDirection::LEFT;
		}

		SetPosition(ResultPosition);
	}
	else if(MoveDirection == EDirection::LEFT)
	{
		Vector2F ResultPosition;

		if (MoveDirection == StartDirection) // StartPosition -> EndPosition
		{
			// max 함수로 도착 지점을 넘어가지 않도록
			ResultPosition = Vector2F(max(GetPosition().x - MoveDistance, PatrolEndPosition.x), GetPosition().y);
			if (ResultPosition == PatrolEndPosition)
				MoveDirection = EDirection::RIGHT;
		}
		else // // EndPosition -> StartPosition
		{
			// max 함수로 시작 지점을 넘어가지 않도록
			ResultPosition = Vector2F(max(GetPosition().x - MoveDistance, PatrolStartPosition.x), GetPosition().y);
			if (ResultPosition == PatrolStartPosition)
				MoveDirection = EDirection::RIGHT;
		}

		SetPosition(ResultPosition);
	}
	else if (MoveDirection == EDirection::UP)
	{
		Vector2F ResultPosition;

		if (MoveDirection == StartDirection) // StartPosition -> EndPosition
		{
			// max 함수로 도착 지점을 넘어가지 않도록
			ResultPosition = Vector2F(GetPosition().x, max(GetPosition().y - MoveDistance, PatrolEndPosition.y));
			if (ResultPosition == PatrolEndPosition)
				MoveDirection = EDirection::DOWN;
		}
		else // // EndPosition -> StartPosition
		{
			// max 함수로 시작 지점을 넘어가지 않도록
			ResultPosition = Vector2F(GetPosition().x, max(GetPosition().y - MoveDistance, PatrolStartPosition.y));
			if (ResultPosition == PatrolStartPosition)
				MoveDirection = EDirection::DOWN;
		}

		SetPosition(ResultPosition);
	}
	else if (MoveDirection == EDirection::DOWN)
	{
		Vector2F ResultPosition;

		if (MoveDirection == StartDirection) // StartPosition -> EndPosition
		{
			// min 함수로 도착 지점을 넘어가지 않도록
			ResultPosition = Vector2F(GetPosition().x, min(GetPosition().y + MoveDistance, PatrolEndPosition.y));
			if (ResultPosition == PatrolEndPosition)
				MoveDirection = EDirection::UP;
		}
		else // // EndPosition -> StartPosition
		{
			// min 함수로 시작 지점을 넘어가지 않도록
			ResultPosition = Vector2F(GetPosition().x, min(GetPosition().y + MoveDistance, PatrolStartPosition.y));
			if (ResultPosition == PatrolStartPosition)
				MoveDirection = EDirection::UP;
		}

		SetPosition(ResultPosition);
	}

}