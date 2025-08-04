#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Utils/Utils.h"
#include "Engine.h"

Actor::Actor(const char image, Color color, const Vector2F& position) : image(image), color(color), position(position)
{
}

Actor::~Actor()
{
}

// 
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Render()
{
	// Win32 API
	// Ŀ�� ��ġ �̵�.
	// static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� ��ġ �� ����
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	// Ŀ�� �̵�
	// SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	// ����
	Utils::SetConsoleTextColor((WORD)color);

	// �׸���
	std::cout << image;
	
}

void Actor::SetPosition(const Vector2F& newPosition)
{
	// static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//COORD coord;
	//coord.X = (short)position.x;
	//coord.Y = (short)position.y;

	//Utils::SetConsolePosition(coord);

	//std::cout << ' ';

	position = newPosition;
}

Vector2F Actor::GetPosition() const
{
	return position;
}

void Actor::SetRenderSortingOrder(unsigned int renderSortingOrder)
{
	this->renderSortingOrder = renderSortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::QuitGame()
{
	Engine::GetEngine().Quit();
}
