#pragma once

#include "Engine.h"

class MenuLevel;
class RicochetLevel;

class Game : public Engine
{
public:
	Game();
	~Game();

	// 메뉴 전환 함수
	void ToggledMenu();

	virtual void CleanUp() override;

	static Game& GetGame();

	// 게임 오버 후 메뉴 다시 여는 함수
	void OpenMainMenuLevel();

	void OpenNextLevel();

	const int GetMapLevel();

private:

	// 메뉴 레벨
	MenuLevel* menuLevel = nullptr;

	// 게임 레벨(RicochetLevel) 저장용 포인터
	RicochetLevel* backLevel = nullptr;

	// 현재 메뉴를 보여주고 있는지를 나타냄
	bool showMenu = true;

	// 게임 맵 레벨
	int MapLevel = 1;

	static Game* instance;
};