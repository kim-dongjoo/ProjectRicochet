#pragma once

#include "Engine.h"

class Level;

class Game : public Engine
{
public:
	Game();
	~Game();

	// �޴� ��ȯ �Լ�
	void ToggledMenu();

	virtual void CleanUp() override;

	static Game& GetGame();

private:

	// �޴� ����
	Level* menuLevel = nullptr;

	Level* backLevel = nullptr;

	// ���� �޴��� �����ְ� �ִ����� ��Ÿ��
	bool showMenu = false;

	static Game* instance;

};