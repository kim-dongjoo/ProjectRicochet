#include "Vector2F.h"
#include <iostream>

// 전역 변수 초기화
Vector2F Vector2F::Zero = Vector2F(0.0f, 0.0f);
Vector2F Vector2F::One = Vector2F(1.0f, 1.0f);
Vector2F Vector2F::Up = Vector2F(0.0f, 1.0f);
Vector2F Vector2F::Right = Vector2F(1.0f, 0.0f);

Vector2F::Vector2F(float x, float y) : x(x), y(y)
{
}

Vector2F::~Vector2F()
{
    if (value == nullptr)
        return;

    delete[] value;
}

Vector2F Vector2F::operator+(const Vector2F& other) const
{
    return Vector2F(x + other.x, y + other.y);
}

Vector2F Vector2F::operator-(const Vector2F& other) const
{
    return Vector2F(x - other.x, y - other.y);
}

bool Vector2F::operator==(const Vector2F & other) const
{
    return x == other.x && y == other.y;
}

const char* Vector2F::ToString()
{
    if (value != nullptr)
        delete[] value;

    value = new char[1024];

    sprintf_s(value, 1024, "(%f,%f)", x, y);
    return value;
}

// 평행하지만 같은 위치는 아닌 두 위치가 입력된다고 가정.
EDirection Vector2F::GetDirection(const Vector2F& StartPosition, const Vector2F& EndPosition)
{
    float DiffX = EndPosition.x - StartPosition.x;
    float DiffY = EndPosition.y - StartPosition.y;

    if (DiffX > 0.0f && DiffY == 0.0f)
        return EDirection::RIGHT;
    else if (DiffX < 0.0f && DiffY == 0.0f)
        return EDirection::LEFT;
    else if (DiffX == 0.0f && DiffY > 0.0f)
        return EDirection::DOWN;
    else if (DiffX == 0.0f && DiffY < 0.0f)
        return EDirection::UP;

    return EDirection::None;
}