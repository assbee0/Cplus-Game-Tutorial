//! @file Math.cpp

#include	<Math/Math.h>

namespace Dungeon
{
	Vector2::Vector2() :
		x(0.0f),
		y(0.0f)
	{

	}

	Vector2::Vector2(float X, float Y) :
		x(X),
		y(Y)
	{

	}

	const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
	const Vector2 Vector2::X = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::Y = Vector2(0.0f, 1.0f);
	const Vector2 Vector2::NX = Vector2(-1.0f, 0.0f);
	const Vector2 Vector2::NY = Vector2(0.0f, -1.0f);


	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	bool operator==(const Vector2& a, const Vector2& b)
	{
		return (a.x == b.x && a.y == b.y);
	}

}