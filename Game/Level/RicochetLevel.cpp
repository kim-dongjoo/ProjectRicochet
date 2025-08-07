#include "RicochetLevel.h"
#include "Game/Game.h"
#include "Math/Vector2F.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/MovingWall.h"
#include "Actor/Ground.h"
#include "Actor/Trap.h"
#include "Actor/Goal.h"
#include "Utils/Utils.h"

#include <cmath>
#include <iostream>

RicochetLevel::RicochetLevel()
{
	int mapLevel = Game::GetGame().GetMapLevel();

	char filename[20] = { };

	sprintf_s(filename, 20, "Stage%d.txt", mapLevel);

	 ReadMapFile(filename);

	// ReadMapFile("Stage1.txt");
}

void RicochetLevel::Tick(float DeltaTime)
{
	if (isGameClear || isGameOver)
		return;

	super::Tick(DeltaTime);
}

void RicochetLevel::BeginPlay()
{
	super::BeginPlay();
}

void RicochetLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 12, 23 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Clear! ====";

		LoadNextMap();
	}

	if (isGameOver)
	{
		Utils::SetConsolePosition({ 12, 23 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Over! ====";

		ReturnToMainMenu();
	}

}

void RicochetLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ���� (" << filename << ")" << std::endl;
		__debugbreak();
		return;
	}

	// �Ľ�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	// memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[fileSize] = '\0';

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize. \n";
	}

	// �迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	// ���ڿ� ���̰�
	int size = (int)readSize;

	// x, y ��ǥ
	Vector2F position = { 0.0f, 0.0f };

	// ���� �迭 ��ȸ
	while (index < size)
	{
		// �� ���� Ȯ��
		char mapCharacter = buffer[index++];

		// ���� ���� ó��
		if (mapCharacter == '\n')
		{
			position.y += 1.0f;
			position.x = 0.0f;

			// �׽�Ʈ �ڵ�
			std::cout << std::endl;
			continue;
		}

		switch (mapCharacter)
		{
		case '#':
			SpawnActor(new Wall(position));
			break;
		case '.':
			SpawnActor(new Ground(position));
			break;
		case 'S':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			SpawnActor(new Player(position));
			break;
		case 'X':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			SpawnActor(new Trap(position));
			break;
		case '(':
			PatrolStartPosition = position;
			SpawnActor(new Ground(position));
			break;
		case ')':
			PatrolEndPosition = position;
			SpawnActor(new Ground(position));

			// MovingWall ����
			SpawnActor(new MovingWall(PatrolStartPosition, PatrolEndPosition, Vector2F::GetDirection(PatrolStartPosition, PatrolEndPosition)));
			break;
		case 'G':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			SpawnActor(new Goal(position));
			GoalPosition = position;
			break;
		}

		// x ��ǥ ���� ó��
		position.x += 1.0f;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);

}

Vector2F RicochetLevel::FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection, float DeltaTime)
{
	Vector2F NextPosition = { floor(FromPosition.x), floor(FromPosition.y) };

	Player* player = nullptr;
	MovingWall* movingWall = nullptr;

	for (Actor* const actor : actors)
	{
		if (actor->As<MovingWall>())
			movingWall = actor->As<MovingWall>();

		if (actor->As<Player>())
			player = actor->As<Player>();
	}

	if (MoveDirection == EDirection::RIGHT)
	{
		// �̵� �� �浹 üũ
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().y == FromPosition.y)
		{
			// �ͳθ� ��ȭ�� ���� ��ǥ�� �ƴ� 0-1.0f�ǹ����� AABB üũ
			if (!(movingWall->GetPosition().x + movingWall->GetMoveSpeed() * DeltaTime < FromPosition.x || movingWall->GetPosition().x > ToPosition.x))
			{
				player->SetMoveDirection(EDirection::LEFT);
				return FromPosition;
			}
		}

		NextPosition.x += 1.0f;

		// �浹 üũ
		while (NextPosition.x <= floor(ToPosition.x))
		{
			for (Actor* const actor : actors)
			{
				// �浹
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.x -= 1.0f;
					return NextPosition;
				}
			}

			NextPosition.x += 1.0f;
		}

		// �浹���� �ʾҴٸ� ���� ������ ���� �״�� ��ȯ.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::LEFT)
	{
		// �̵� �� �浹 üũ
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().y == FromPosition.y)
		{
			// �ͳθ� ��ȭ�� ���� ��ǥ�� �ƴ� 0-1.0f�ǹ����� AABB üũ
			if (!(movingWall->GetPosition().x + movingWall->GetMoveSpeed() * DeltaTime < ToPosition.x || movingWall->GetPosition().x > FromPosition.x))
			{
				player->SetMoveDirection(EDirection::RIGHT);
				return FromPosition;
			}
		}

		NextPosition.x -= 1.0f;

		// �浹 üũ
		while (NextPosition.x >= floor(ToPosition.x))
		{
			for (Actor* const actor : actors)
			{
				// �浹
				if ((actor->GetPosition() == NextPosition) && actor->As<Wall>())
				{
					NextPosition.x += 1.0f;
					return NextPosition;
				}
			}

			NextPosition.x -= 1.0f;
		}

		// �浹���� �ʾҴٸ� ���� ������ ���� �״�� ��ȯ.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::UP)
	{
		// �̵� �� �浹 üũ
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().x == FromPosition.x)
		{
			// �ͳθ� ��ȭ�� ���� ��ǥ�� �ƴ� 0-1.0f�ǹ����� AABB üũ
			if (!(movingWall->GetPosition().y + movingWall->GetMoveSpeed() * DeltaTime < ToPosition.y || movingWall->GetPosition().y  > FromPosition.y))
			{
				player->SetMoveDirection(EDirection::DOWN);
				return FromPosition;
			}
		}

		NextPosition.y -= 1.0f;

		// �浹 üũ
		while (NextPosition.y >= floor(ToPosition.y))
		{
			for (Actor* const actor : actors)
			{
				// �浹
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.y += 1.0f;
					return NextPosition;
				}
			}

			NextPosition.y -= 1.0f;
		}

		// �浹���� �ʾҴٸ� ���� ������ ���� �״�� ��ȯ.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::DOWN)
	{
		// �̵� �� �浹 üũ
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().x == FromPosition.x)
		{
			// �ͳθ� ��ȭ�� ���� ��ǥ�� �ƴ� 0-1.0f�ǹ����� AABB üũ
			if (!(movingWall->GetPosition().y > ToPosition.y || movingWall->GetPosition().y + movingWall->GetMoveSpeed() * DeltaTime < FromPosition.y))
			{
				player->SetMoveDirection(EDirection::UP);
				return FromPosition;
			}
		}

		NextPosition.y += 1.0f;

		// �浹 üũ
		while (NextPosition.y <= floor(ToPosition.y))
		{
			for (Actor* const actor : actors)
			{
				// �浹
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.y -= 1.0f;
					return NextPosition;
				}
			}

			NextPosition.y += 1.0f;
		}

		// �浹���� �ʾҴٸ� ���� ������ ���� �״�� ��ȯ.
		return ToPosition;
	}

	return	FromPosition;
}

bool RicochetLevel::SetGameClear(const Vector2F& PlayerPosition)
{
	if (PlayerPosition == GoalPosition)
	{
		isGameClear = true;
		return true;
	}

	return false;
}

void RicochetLevel::SetGameOver()
{
	isGameOver = true;
}

bool RicochetLevel::IsOnTrap(const Vector2F& PlayerPosition)
{
	for (Actor* const actor : actors)
	{
		// �浹
		if (actor->GetPosition() == PlayerPosition && actor->As<Trap>())
		{
			return true;
		}
	}

	return false;
}

void RicochetLevel::ReturnToMainMenu()
{
	clock_t start = clock();

	while(true)
	{
		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ

		if (time >= 2.0f)
			break;
	}

	Game::GetGame().OpenMainMenuLevel();
}

void RicochetLevel::LoadNextMap()
{
	clock_t start = clock();

	while (true)
	{
		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ

		if (time >= 2.0f)
			break;
	}

	Game::GetGame().OpenNextLevel();
}