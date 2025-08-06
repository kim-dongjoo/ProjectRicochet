#include "Game.h"
#include "Level/MenuLevel.h"
// #include "Level/SokobanLevel.h"
#include "Level/RicochetLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// 메인 레벨 추가
	// AddLevel(new RicochetLevel());
	// AddLevel(new MenuLevel());

	menuLevel = new MenuLevel();
	backLevel = new RicochetLevel();

	AddLevel(menuLevel);

	// 메뉴 레벨 생성
	//menuLevel = new MenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggledMenu()
{
	// 화면 정리
	system("cls");

	if (showMenu)
	{
		mainLevel = backLevel;
	}
	else
	{
		menuLevel->ChangeMenuItemText(0, "Resume Game");
		mainLevel = menuLevel;
	}

	// 토글 처리
	showMenu = !showMenu;

}

void Game::CleanUp()
{
	if (showMenu)
	{
		// 게임 레벨 제거
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	
	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::GetGame()
{
	return *instance;
}