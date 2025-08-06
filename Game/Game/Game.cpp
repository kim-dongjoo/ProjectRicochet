#include "Game.h"
#include "Level/MenuLevel.h"
// #include "Level/SokobanLevel.h"
#include "Level/RicochetLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	// ���� ���� �߰�
	// AddLevel(new RicochetLevel());
	// AddLevel(new MenuLevel());

	menuLevel = new MenuLevel();
	backLevel = new RicochetLevel();

	AddLevel(menuLevel);

	// �޴� ���� ����
	//menuLevel = new MenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggledMenu()
{
	// ȭ�� ����
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

	// ��� ó��
	showMenu = !showMenu;

}

void Game::CleanUp()
{
	if (showMenu)
	{
		// ���� ���� ����
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