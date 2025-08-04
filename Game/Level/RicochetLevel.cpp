#include "RicochetLevel.h"
#include "Math/Vector2.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Goal.h"
#include "Utils/Utils.h"
#include <cmath>

#include <iostream>

RicochetLevel::RicochetLevel()
{
	ReadMapFile("Stage1.txt");
}

void RicochetLevel::Tick(float DeltaTime)
{
	if (isGameClear || isGameOver)
		return;

	super::Tick(DeltaTime);
}

void RicochetLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 12, 23 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Clear! ====";
	}

	if (isGameOver)
	{
		Utils::SetConsolePosition({ 12, 23 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Over! ====";
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
		case 'R':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			SpawnActor(new Player(position));
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

Vector2F RicochetLevel::FindReachablePosition(const Vector2F& FromPosition, const Vector2F& ToPosition, EDirection MoveDirection)
{
	Vector2F NextPosition = { floor(FromPosition.x), floor(FromPosition.y) };

	if (MoveDirection == EDirection::RIGHT)
	{
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

void RicochetLevel::SetGameClear(const Vector2F& PlayerPosition)
{
	if (PlayerPosition == GoalPosition)
		isGameClear = true;
}

void RicochetLevel::SetGameOver()
{
	isGameOver = true;
}