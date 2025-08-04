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

	// �������̽� ������
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

	// �Է� ó�� 
	float MoveDistance = MoveSpeed * deltaTime * 5;

	// ===================================================================
	// IsMoving = true
	// �� �����ӿ��� �̵� ���̾��ٸ� ��� �̵��� �õ��Ѵ�.
	// �̵� ���̹Ƿ� �Է��� ���� �ʴ´�.
	// �̵� ������ �����ϸ� IsMoving�� false�� �����.
	// ===================================================================
	// IsMoving = false
	// �� �����ӿ��� �̵� ���� �ƴϾ��ٸ� �Է��� ���� �� �ִ�.
	// ===================================================================
	// �̵� �ӵ� ����� ���� �÷��̾�� ������ �Ǽ��� ��ġ ������ �Լ��� ������.
	// ===================================================================
	if (IsMoving)
	{
		if (MoveDirection == EDirection::RIGHT)
		{
			Vector2F TargetPosition = Vector2F((GetPosition().x + MoveDistance), GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::RIGHT);

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			if(TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// �������� �浹�� �־��ٸ� ���� ���·� ����
			if (!(TargetPosition == ResultPosition))
			{
				// ��ǥ ��ġ�� ���� ��� ��ġ�� ���� �ʰų� ��ġ ��ȭ�� ���ٸ� ���� ���� ���̹Ƿ� �̵� �÷��׸� ������ ����
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::LEFT)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x - MoveDistance, GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::LEFT);

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// �������� �浹�� �־��ٸ� ���� ���·� ����
			if (!(TargetPosition == ResultPosition))
			{
				// ��ǥ ��ġ�� ���� ��� ��ġ�� ���� �ʰų� ��ġ ��ȭ�� ���ٸ� ���� ���� ���̹Ƿ� �̵� �÷��׸� ������ ����
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::UP)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y - MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::UP);

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// �������� �浹�� �־��ٸ� ���� ���·� ����
			if (!(TargetPosition == ResultPosition))
			{
				// ��ǥ ��ġ�� ���� ��� ��ġ�� ���� �ʰų� ��ġ ��ȭ�� ���ٸ� ���� ���� ���̹Ƿ� �̵� �÷��׸� ������ ����
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
		else if (MoveDirection == EDirection::DOWN)
		{
			Vector2F TargetPosition = Vector2F(GetPosition().x, GetPosition().y + MoveDistance);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::DOWN);

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			if (TargetPosition == ResultPosition)
				SetPosition(ResultPosition);

			// �������� �浹�� �־��ٸ� ���� ���·� ����
			if (!(TargetPosition == ResultPosition))
			{
				// ��ǥ ��ġ�� ���� ��� ��ġ�� ���� �ʰų� ��ġ ��ȭ�� ���ٸ� ���� ���� ���̹Ƿ� �̵� �÷��׸� ������ ����
				SetPosition(ResultPosition);
				MoveDirection = EDirection::None;
				IsMoving = false;
			}
		}
	}
	else
	{
		// �̵� �Է��� �ִٸ� �ް� �̵� ������ �õ��Ѵ�.

		if (Input::GetInput().GetKeyDown(VK_RIGHT))
		{
			Vector2F TargetPosition = Vector2F((GetPosition().x + MoveDistance), GetPosition().y);
			Vector2F ResultPosition = EQInterface->FindReachablePosition(GetPosition(), TargetPosition, EDirection::RIGHT);

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			// �̵� �÷��׸� �̵� ������ ����
			if (TargetPosition == ResultPosition)
			{
				SetPosition(TargetPosition);
				MoveDirection = EDirection::RIGHT;
				IsMoving = true;
			}
				
			// �������� �浹�� �־��ٸ�
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

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			// �̵� �÷��׸� �̵� ������ ����
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::LEFT;
				IsMoving = true;
			}

			// �������� �浹�� �־��ٸ�
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

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			// �̵� �÷��׸� �̵� ������ ����
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::UP;
				IsMoving = true;
			}

			// �������� �浹�� �־��ٸ�
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

			// �������� �浹�� �����ٸ� ���� ��ǥ ��ġ�� �̵��Ѵ�.
			// �̵� �÷��׸� �̵� ������ ����
			if (TargetPosition == ResultPosition)
			{
				SetPosition(ResultPosition);
				MoveDirection = EDirection::DOWN;
				IsMoving = true;
			}

			// �������� �浹�� �־��ٸ�
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

	std::cout << "���� �̵� Ƚ��: " << MoveCount;
}