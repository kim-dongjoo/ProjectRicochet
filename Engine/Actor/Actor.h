#pragma once

#include "Core.h"
#include "../Math/Vector2.h"
#include "Math/Vector2F.h"
#include "RTTI.h"
#include <Windows.h>

// ��ġ
// �׸���
// ������ �̺�Ʈ �Լ� ȣ��(BeginPlay/Tick/Draw)

// ����
enum class Color : int
{
	Blue =	1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue,
	Intensity = 8
};

class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	// Actor(const char image = ' ', Color color = Color::White, const Vector2& position = Vector2::Zero);
	Actor(const char image = ' ', Color color = Color::White, const Vector2F& position = Vector2F::Zero);
	virtual ~Actor();

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�
	//void SetPosition(const Vector2& newPosition);
	//Vector2 GetPosition() const;
	void SetPosition(const Vector2F& newPosition);
	Vector2F GetPosition() const;

	// Render Sorting Order ����
	void SetRenderSortingOrder(unsigned int renderSortingOrder);

	// ���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// ���� ���� ��û �Լ�
	void QuitGame();

protected:
	// Tick �Լ��� ��������
	bool bCanEverTick = true;

private:
	// Vector2 position;
	Vector2F position;

	// �׸� ��
	char image = ' ';

	// ����
	Color color ;

	// BeginPlay�� ȣ�� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ���� ����
	unsigned int renderSortingOrder = 0;

	// ���� ����(���ʽ�)
	Level* owner = nullptr;

};

