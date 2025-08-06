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

	// 메뉴 아이템 추가
	items.emplace_back(new MenuItem("Start Game", []() {  Game::GetGame().ToggledMenu(); }));

	items.emplace_back(new MenuItem("Quit Game", []() { Game::GetGame().Quit(); }));

	// 아이템 수 미리 저장
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

	// 입력 처리
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
		// 메뉴 아이템이 저장하고 있는 함수
		items[currentIndex]->onSelected();

	}

	if (Input::GetInput().GetKeyDown(VK_ESCAPE))
	{
		// TODO : Game 에 토글 메뉴 기능 추가 후 호출해야함
		Game::GetGame().ToggledMenu();

		// 메뉴 인덱스 초기화
		currentIndex = 0;
	}
}

void MenuLevel::Render()
{
	super::Render();

	// 색상&좌표 정리
	Utils::SetConsolePosition({ 0, 0 });
	Utils::SetConsoleTextColor(static_cast<WORD>(DeselectedColor));

	std::cout << "==[Top Skater]==\n\n";

	// 메뉴 아이템 렌더링
	for (int idx = 0; idx < length; idx++)
	{
		// 아이템 색상 확인
		Color textColor =
			(idx == currentIndex) ? selectedColor : DeselectedColor;

		// 색상 설정
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// 메뉴 텍스트 출력
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
		//// 최종 애셋 경로 완성
		//char filepath[256] = {};
		//sprintf_s(filepath, 256, "../Contents/%s", filename);

		//FILE* file = nullptr;
		//fopen_s(&file, filepath, "rt");

		//// 예외 처리
		//if (file == nullptr)
		//{
		//	std::cout << "아스키 아트 파일 읽기 실패 (" << filename << ")" << std::endl;
		//	__debugbreak();
		//	return;
		//}

		std::ifstream file("../Contents/TitleImage.txt");
		std::string line;

		SHORT PositionY = 0;

		if (file.is_open()) {
			while (std::getline(file, line)) {
				Utils::SetConsolePosition({ 5, PositionY });
				std::cout << line << std::endl; // 각 줄을 콘솔에 출력
				PositionY++;
			}
			file.close();

			Utils::SetConsolePosition({ 0, 0 });
		}
		else {
			std::cerr << "Error: Could not open file." << std::endl;
		}

	}