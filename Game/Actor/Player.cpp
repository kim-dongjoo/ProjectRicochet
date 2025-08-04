#include "Player.h"
#include "Engine.h"
#include "Game//Game.h"
#include "Input.h"
#include "Utils/Utils.h"
#include "Level/RicochetLevel.h"
#include "Interface/IEnvironmentQuery.h"

#include <iostream>

Player::Player(const Vector2F& position) : Actor('R', Color::Red, position), MoveDirection(EDirection::None)
{
	SetRenderSortingOrder(3);
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// 인터페이스 얻어오기
	if (GetOwner())
	{
		EQInterface = dynamic_cast<IEnvironmentQuery*>(GetOwner());

		if (!EQInterface)
		{
			std::cout << "Can not cast owner level to IEnvironmentQuery. \n";
		}
	}
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if(!MoveCount && MoveDirection == EDirection::None)
		EQInterface->SetGameOver();

	if (Input::GetInput().GetKeyDown(VK_ESCAPE))
	{
		// Engine::GetEngine().Quit();
		// QuitGame();

		Game::GetGame().ToggledMenu();
		return;
	}

	// 입력 처리 
	float MoveDistance = MoveSpeed * deltaTime * 5;

	// ===================================================================
	// IsMoving = true
	// 전 프레임에서 이동 중이었다면 계속 이동을 시도한다.
	// 이동 중이므로 입력을 받지 않는다.
	// 이동 쿼리를 실패하면 IsMoving을 false로 만든다.
	// ===================================================================
	// IsMoving = false
	// 전 프레임에서 이동 중이 아니었다면 입력을 받을 수 있다.
	// ===================================================================
	// 이동 속도 계산을 위해 플레이어는 별도의 실수형 위치 변수와 함수를 가진다.
	// ===================================================================
	if (IsMoving)
	{
		if (MoveDirection == EDirection::RIGHT)
		{
			Vector2F TargetPosition = Vector2F((GetPosition().x + MoveDistance), GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::RIGHT);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			if(TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// 쿼리에서 충돌이 있었다면 정지 상태로 변경
			if (!(TargetPosition == ResultPosition))
			{
				// 목표 위치와 쿼리 결과 위치가 같지 않거나 위치 변화가 없다면 벽에 막힌 것이므로 이동 플래그를 정지로 변경
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::LEFT)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x - MoveDistance, GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::LEFT);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// 쿼리에서 충돌이 있었다면 정지 상태로 변경
			if (!(TargetPosition == ResultPosition))
			{
				// 목표 위치와 쿼리 결과 위치가 같지 않거나 위치 변화가 없다면 벽에 막힌 것이므로 이동 플래그를 정지로 변경
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::UP)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y - MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::UP);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// 쿼리에서 충돌이 있었다면 정지 상태로 변경
			if (!(TargetPosition == ResultPosition))
			{
				// 목표 위치와 쿼리 결과 위치가 같지 않거나 위치 변화가 없다면 벽에 막힌 것이므로 이동 플래그를 정지로 변경
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::DOWN)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y + MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::DOWN);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// 쿼리에서 충돌이 있었다면 정지 상태로 변경
			if (!(TargetPosition == ResultPosition))
			{
				// 목표 위치와 쿼리 결과 위치가 같지 않거나 위치 변화가 없다면 벽에 막힌 것이므로 이동 플래그를 정지로 변경
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
	}
	else
	{
		// 이동 입력이 있다면 받고 이동 쿼리를 시도한다.

		if (Input::GetInput().GetKeyDown(VK_RIGHT))
		{
			Vector2F TargetPosition = Vector2F((GetPosition().x + MoveDistance), GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::RIGHT);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			// 이동 플래그를 이동 중으로 변경
			if (TargetPosition == ResultPosition)
			{
				SetPosition(TargetPosition);
				MoveDirection = EDirection::RIGHT;
				IsMoving = true;
			}
				
			// 쿼리에서 충돌이 있었다면
			if (!(TargetPosition == ResultPosition))
			{
				SetPosition(ResultPosition);
			}

			MoveCount--;
			return;
		}

		if (Input::GetInput().GetKeyDown(VK_LEFT))
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x - MoveDistance, GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::LEFT);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			// 이동 플래그를 이동 중으로 변경
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::LEFT;
				IsMoving = true;
			}

			// 쿼리에서 충돌이 있었다면
			if (!(TargetPosition == ResultPosition))
			{
				SetPosition(ResultPosition);
			}

			MoveCount--;
			return;
		}

		if (Input::GetInput().GetKeyDown(VK_UP))
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y - MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::UP);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			// 이동 플래그를 이동 중으로 변경
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::UP;
				IsMoving = true;
			}

			// 쿼리에서 충돌이 있었다면
			if (!(TargetPosition == ResultPosition))
			{
				SetPosition(ResultPosition);
			}

			MoveCount--;
			return;
		}

		if (Input::GetInput().GetKeyDown(VK_DOWN))
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y + MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::DOWN);

			// 쿼리에서 충돌이 없었다면 원래 목표 위치로 이동한다.
			// 이동 플래그를 이동 중으로 변경
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::DOWN;
				IsMoving = true;
			}

			// 쿼리에서 충돌이 있었다면
			if (!(TargetPosition == ResultPosition))
			{
				SetPosition(ResultPosition);
			}

			MoveCount--;
			return;
		}
	}

	EQInterface->SetGameClear(GetPosition());
}

void Player::Render()
{
	super::Render();

	Utils::SetConsolePosition({ 0, 25 });
	Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

	std::cout << "남은 이동 횟수: " << MoveCount;
}