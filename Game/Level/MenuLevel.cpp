#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

#include <iostream>

MenuLevel::MenuLevel()
{
	// �޴� ������ �߰�
	items.emplace_back(new MenuItem("Resume Game", []() {  Game::GetGame().ToggledMenu(); }));

	items.emplace_back(new MenuItem("Quit Game", []() { Game::GetGame().Quit(); }));

	// ������ �� �̸� ����
	length = static_cast<int>(items.size());

}

MenuLevel::~MenuLevel()
{
	for (MenuItem* item : items)
	{
		SafeDelete(item);
	}

	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �Է� ó��
	if (Input::GetInput().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::GetInput().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1 ) % length;;
	}
	if (Input::GetInput().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� �����ϰ� �ִ� �Լ�
		items[currentIndex]->onSelected();

	}

	if (Input::GetInput().GetKeyDown(VK_ESCAPE))
	{
		// TODO : Game �� ��� �޴� ��� �߰� �� ȣ���ؾ���
		Game::GetGame().ToggledMenu();

		// �޴� �ε��� �ʱ�ȭ
		currentIndex = 0;
	}


}

void MenuLevel::Render()
{
	super::Render();

	// ����&��ǥ ����
	Utils::SetConsolePosition({ 0, 0 });
	Utils::SetConsoleTextColor(static_cast<WORD>(DeselectedColor));

	std::cout << "SokobanGame\n\n";

	// �޴� ������ ������
	for (int idx = 0; idx < length; idx++)
	{
		// ������ ���� Ȯ��
		Color textColor =
			(idx == currentIndex) ? selectedColor : DeselectedColor;

		// ���� ����
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// �޴� �ؽ�Ʈ ���
		std::cout << items[idx]->menuText << "\n";

	}
}
