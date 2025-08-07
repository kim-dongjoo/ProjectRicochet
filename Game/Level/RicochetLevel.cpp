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
	// 최종 애셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// 예외 처리
	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패 (" << filename << ")" << std::endl;
		__debugbreak();
		return;
	}

	// 파싱
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	// memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[fileSize] = '\0';

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize. \n";
	}

	// 배열 순회를 위한 인덱스 변수
	int index = 0;

	// 문자열 길이값
	int size = (int)readSize;

	// x, y 좌표
	Vector2F position = { 0.0f, 0.0f };

	// 문자 배열 순회
	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index++];

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			position.y += 1.0f;
			position.x = 0.0f;

			// 테스트 코드
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
			// 땅도 같이 생성
			SpawnActor(new Ground(position));
			SpawnActor(new Player(position));
			break;
		case 'X':
			// 땅도 같이 생성
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

			// MovingWall 생성
			SpawnActor(new MovingWall(PatrolStartPosition, PatrolEndPosition, Vector2F::GetDirection(PatrolStartPosition, PatrolEndPosition)));
			break;
		case 'G':
			// 땅도 같이 생성
			SpawnActor(new Ground(position));
			SpawnActor(new Goal(position));
			GoalPosition = position;
			break;
		}

		// x 좌표 증가 처리
		position.x += 1.0f;
	}

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
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
		// 이동 벽 충돌 체크
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().y == FromPosition.y)
		{
			// 터널링 완화를 위해 좌표가 아닌 0-1.0f의범위로 AABB 체크
			if (!(movingWall->GetPosition().x + movingWall->GetMoveSpeed() * DeltaTime < FromPosition.x || movingWall->GetPosition().x > ToPosition.x))
			{
				player->SetMoveDirection(EDirection::LEFT);
				return FromPosition;
			}
		}

		NextPosition.x += 1.0f;

		// 충돌 체크
		while (NextPosition.x <= floor(ToPosition.x))
		{
			for (Actor* const actor : actors)
			{
				// 충돌
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.x -= 1.0f;
					return NextPosition;
				}
			}

			NextPosition.x += 1.0f;
		}

		// 충돌하지 않았다면 원래 목적지 값을 그대로 반환.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::LEFT)
	{
		// 이동 벽 충돌 체크
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().y == FromPosition.y)
		{
			// 터널링 완화를 위해 좌표가 아닌 0-1.0f의범위로 AABB 체크
			if (!(movingWall->GetPosition().x + movingWall->GetMoveSpeed() * DeltaTime < ToPosition.x || movingWall->GetPosition().x > FromPosition.x))
			{
				player->SetMoveDirection(EDirection::RIGHT);
				return FromPosition;
			}
		}

		NextPosition.x -= 1.0f;

		// 충돌 체크
		while (NextPosition.x >= floor(ToPosition.x))
		{
			for (Actor* const actor : actors)
			{
				// 충돌
				if ((actor->GetPosition() == NextPosition) && actor->As<Wall>())
				{
					NextPosition.x += 1.0f;
					return NextPosition;
				}
			}

			NextPosition.x -= 1.0f;
		}

		// 충돌하지 않았다면 원래 목적지 값을 그대로 반환.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::UP)
	{
		// 이동 벽 충돌 체크
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().x == FromPosition.x)
		{
			// 터널링 완화를 위해 좌표가 아닌 0-1.0f의범위로 AABB 체크
			if (!(movingWall->GetPosition().y + movingWall->GetMoveSpeed() * DeltaTime < ToPosition.y || movingWall->GetPosition().y  > FromPosition.y))
			{
				player->SetMoveDirection(EDirection::DOWN);
				return FromPosition;
			}
		}

		NextPosition.y -= 1.0f;

		// 충돌 체크
		while (NextPosition.y >= floor(ToPosition.y))
		{
			for (Actor* const actor : actors)
			{
				// 충돌
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.y += 1.0f;
					return NextPosition;
				}
			}

			NextPosition.y -= 1.0f;
		}

		// 충돌하지 않았다면 원래 목적지 값을 그대로 반환.
		return ToPosition;
	}
	else if (MoveDirection == EDirection::DOWN)
	{
		// 이동 벽 충돌 체크
		if (!player->GetIsBounced() && movingWall && movingWall->GetPosition().x == FromPosition.x)
		{
			// 터널링 완화를 위해 좌표가 아닌 0-1.0f의범위로 AABB 체크
			if (!(movingWall->GetPosition().y > ToPosition.y || movingWall->GetPosition().y + movingWall->GetMoveSpeed() * DeltaTime < FromPosition.y))
			{
				player->SetMoveDirection(EDirection::UP);
				return FromPosition;
			}
		}

		NextPosition.y += 1.0f;

		// 충돌 체크
		while (NextPosition.y <= floor(ToPosition.y))
		{
			for (Actor* const actor : actors)
			{
				// 충돌
				if (actor->GetPosition() == NextPosition && actor->As<Wall>())
				{
					NextPosition.y -= 1.0f;
					return NextPosition;
				}
			}

			NextPosition.y += 1.0f;
		}

		// 충돌하지 않았다면 원래 목적지 값을 그대로 반환.
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
		// 충돌
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
		double time = double(end - start) / CLOCKS_PER_SEC; //초단위 변환

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
		double time = double(end - start) / CLOCKS_PER_SEC; //초단위 변환

		if (time >= 2.0f)
			break;
	}

	Game::GetGame().OpenNextLevel();
}