#pragma once

#include "Level/Level.h"
#include <vector>
#include <Actor/Actor.h>

struct MenuItem
{
	typedef void (*OnSelected)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}

	~MenuItem()
	{
		SafeDeleteArray(menuText);
	}

	// �޴� �ؽ�Ʈ
	char* menuText = nullptr;

	// �޴� ���� �� ������ ����
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void BeginPlay() override;
	virtual void Render() override;

	// BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void ChangeMenuItemText(int ItemIndex, const char* ItemText);

private:
	void ReadASCIIArtFile(const char* filename);

private:
	// BeginPlay�� ȣ�� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ���õ� �������� �ε���
	int currentIndex = 0;

	// ������ ���� ����
	Color selectedColor = Color::Green;

	// ������ ���� �ȵ��� �� ����
	Color DeselectedColor = Color::White;

	// ������ �迭
	std::vector<MenuItem*> items;

	// �޴� ������ ��
	int length = 0;

};