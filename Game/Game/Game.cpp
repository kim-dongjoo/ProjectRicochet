#include "Game.h"
#include "Level/MenuLevel.h"
// #include "Level/SokobanLevel.h"
#include "Level/RicochetLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{

	instance = this;

	// ���� ���� �߰�
	// AddLevel(new SokobanLevel());
	AddLevel(new RicochetLevel());

	// �޴� ���� ����
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggledMenu()
{
	// ȭ�� ����
	system("cls");

	// ��� ó��
	showMenu = !showMenu;

	if (showMenu)
	{
		// ���� ������ �ڷ� �б�
		backLevel = mainLevel;

		// �޴� ������ ���� ������ ����
		mainLevel = menuLevel;
	}
	else
	{
		// ���� ������ ���� ������ ����
		mainLevel = backLevel;

	}

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