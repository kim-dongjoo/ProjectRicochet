#pragma once

#include "Core.h"

class Engine_API Input
{
	// freend ����
	friend class Engine;


	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ���
		bool isKeyDown = false;
		// ���� �����ӿ� Ű�� ���ȴ���
		bool previousKeyDown = false;
	};

public:
	Input();

	// Ű Ȯ�� �Լ�
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);



	static Input& GetInput();

private:
	void ProcessInput();
	void SavePreviousKeyStates();

private:
	// Ű �Է� ���� ���� ����
	KeyState keyStates[255];

	static Input* instance;
};
