#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

// ���� ���� ����ü
struct EngineSettings
{
	// �ܼ� ȭ�� ���� ũ��
	int width = 0;

	// �ܼ� ȭ�� ���� ũ��
	int height = 0;

	// Ÿ�� ������ �ӵ�
	float framerate = 0.0f;
};

class Level;

class Engine_API Engine
{

public:
	// ������
	Engine();

	// �Ҹ���
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void AddLevel(Level* newLevel);



	// �޸� ��ü �Լ�
	virtual void CleanUp();

	// ���� ���� �Լ�
	void Quit();

	// �̱��� ���� �Լ�
	static Engine& GetEngine();

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

	// ���� ���� �ε� �Լ�
	void LoadEngineSettings();

protected:
	// ���� ���� �÷���
	bool isQuit = false;

	// ���� ����
	Level* mainLevel = nullptr;

	// �Է� ������
	Input input;

	// ���� ����
	EngineSettings settings;

	// �̱��� ����
	static Engine* instance;

};

