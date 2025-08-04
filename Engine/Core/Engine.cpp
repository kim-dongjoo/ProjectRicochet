#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

// ��������
// �ܼ� �Է� ó��(Ű����)
//

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
		case CTRL_CLOSE_EVENT:
		//Engine�� �޸� ����
		Engine::GetEngine().CleanUp();
		return false;


	}

	return false;

}

Engine::Engine()
{
	instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	//�ܼ� Ŀ�� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// �ܼ� â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

	// ���� ���� �ε�
	LoadEngineSettings();
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���ļ� ��������
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������ ����Ʈ
	float targetFrameRate = settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// Ÿ�� �� ������ ����
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// ���� ���� ���� Ȯ��
		if (isQuit)
			break;

		// ������ �ð� ���
		// (���� �ð� - ���� �ð�) / ���ļ�
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;
		QueryPerformanceCounter(&currentTime);

		input.ProcessInput();

		// ������ 60 ���Ϸ� ����
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			input.SavePreviousKeyStates();
		}
	}

	// �ؽ�Ʈ ���� �ٽ� ������� ����

	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// ���� ����
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	isQuit = true;
}

Engine& Engine::GetEngine()
{
	return *instance;
}

//void Engine::ProcessInput()
//{
//	// Ű �Է� Ȯ��
//	for (int idx = 0; idx < 255; ++idx)
//	{
//		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
//	}
//
//	// ESC Ű ���� Ȯ��
//	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
//	//	Quit();
//}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout
	//<< "DeltaTime : " << deltaTime
	//<< ", FPS : " << (1.0f/deltaTime)
	//<< "\n";

	// ���� ������Ʈ
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	// if (GetKeyDown(VK_ESCAPE)) { Quit(); }
}

void Engine::Render()
{
	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	/*SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	);*/

	if (mainLevel)
	{
		mainLevel->Render();
	}
}

void Engine::LoadEngineSettings()
{
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");

	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings. \n";
		__debugbreak();
		return;
	}

	// �ε�

	// FP(File Position) �����͸� ���� �ڷ� �ű��
	fseek(file, 0, SEEK_END);

	// �� ��ġ ���ϱ�
	size_t fileSize = ftell(file);

	// �ٽ� ù ��ġ�� �ǵ�����
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// ���� �б�
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// �Ľ�(Parcing, ���� �ؼ�->�ʿ��� ������ ��� ����)
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	// ���� �м�
	while (token != nullptr)
	{
		// Ű/�� �и�
		char header[16] = { };
		sscanf_s(token, "%s", header, 16);

		// ��� ���ڿ� ��
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// �� ���� �� �и�
		token = strtok_s(nullptr, "\n", &context);

	}

	SafeDeleteArray(buffer);

	// ���� �ݱ�
	fclose(file);



}
