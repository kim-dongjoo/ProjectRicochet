#include "Input.h"
#include <Windows.h>

// static ���� ����
Input* Input::instance = nullptr;

Input::Input()
{
	// �̱��� ������ ���� instance ���� ����
	instance = this;
}

void Input::ProcessInput()
{
	// Ű �Է� Ȯ��
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
	}
}

void Input::SavePreviousKeyStates()
{
	// ���� �������� �Է��� ���
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].previousKeyDown = keyStates[idx].isKeyDown;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Input::GetKeyDown(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Input::GetKeyUp(int keyCode)
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}

Input& Input::GetInput()
{
	return *instance;
}