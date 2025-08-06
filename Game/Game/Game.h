#pragma once

#include "Engine.h"

class MenuLevel;
class RicochetLevel;

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
	MenuLevel* menuLevel = nullptr;

	// ���� ����(RicochetLevel) ����� ������
	RicochetLevel* backLevel = nullptr;

	// ���� �޴��� �����ְ� �ִ����� ��Ÿ��
	bool showMenu = true;

	static Game* instance;

};