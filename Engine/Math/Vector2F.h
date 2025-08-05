#pragma once

#include "Core.h"

enum class EDirection : short
{
	None = 1,
	RIGHT = 2,
	LEFT = 3,
	UP = 4,
	DOWN = 5
};

class Engine_API Vector2F
{
public:
	Vector2F(float x = 0.0f, float y = 0.0f);
	~Vector2F();

	Vector2F operator+(const Vector2F& other) const;
	Vector2F operator-(const Vector2F& other) const;
	bool operator==(const Vector2F& other) const;

	// 문자열로 출력
	const char* ToString();

	static Vector2F Zero;
	static Vector2F One;
	static Vector2F Up;
	static Vector2F Right;

	static EDirection GetDirection(const Vector2F& StartPosition, const Vector2F& EndPosition);
public:
	// X/Y 좌표
	float x = 0;
	float y = 0;

private:
	// 문자열 변수
	char* value = nullptr;

};