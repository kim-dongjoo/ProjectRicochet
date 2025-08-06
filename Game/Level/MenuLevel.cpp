#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

#include <iostream>
#include <fstream>
#include <string>

MenuLevel::MenuLevel()
{
	ReadASCIIArtFile("TitleImage.txt");

	// �޴� ������ �߰�
	items.emplace_back(new MenuItem("Start Game", []() {  Game::GetGame().ToggledMenu(); }));

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

	std::cout << "==[Top Skater]==\n\n";

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

void MenuLevel::ChangeMenuItemText(int ItemIndex, const char* ItemText)
{
	if (items[ItemIndex]->menuText != ItemText)
	{
		SafeDeleteArray(items[ItemIndex]->menuText);

		size_t length = strlen(ItemText);
		items[ItemIndex]->menuText = new char[length + 1];
		strcpy_s(items[ItemIndex]->menuText, length + 1, ItemText);
	}
}

void MenuLevel::ReadASCIIArtFile(const char* filename)
{
		//// ���� �ּ� ��� �ϼ�
		//char filepath[256] = {};
		//sprintf_s(filepath, 256, "../Contents/%s", filename);

		//FILE* file = nullptr;
		//fopen_s(&file, filepath, "rt");

		//// ���� ó��
		//if (file == nullptr)
		//{
		//	std::cout << "�ƽ�Ű ��Ʈ ���� �б� ���� (" << filename << ")" << std::endl;
		//	__debugbreak();
		//	return;
		//}

		std::ifstream file("../Contents/TitleImage.txt");
		std::string line;

		SHORT PositionY = 0;

		if (file.is_open()) {
			while (std::getline(file, line)) {
				Utils::SetConsolePosition({ 5, PositionY });
				std::cout << line << std::endl; // �� ���� �ֿܼ� ���
				PositionY++;
			}
			file.close();

			Utils::SetConsolePosition({ 0, 0 });
		}
		else {
			std::cerr << "Error: Could not open file." << std::endl;
		}

	}