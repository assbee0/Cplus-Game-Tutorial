//! @file Math.h

#ifndef __Dungeon_Math__
#define __Dungeon_Math__

namespace Dungeon
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2();
		Vector2(float X, float Y);

		static const Vector2 Zero;		//!<	(0 , 0)
		static const Vector2 One;		//!<	(1 , 1)
		static const Vector2 X;			//!<	(1 , 0)
		static const Vector2 Y;			//!<	(0 , 1)
		static const Vector2 NX;		//!<	(-1, 0)
		static const Vector2 NY;		//!<	(0 ,-1)

		//! 向量加法
		friend Vector2 operator+(const Vector2& a, const Vector2& b);
		//! 向量减法
		friend Vector2 operator-(const Vector2& a, const Vector2& b);
		//! 向量乘法（均为向量，对应元素相乘）
		friend Vector2 operator*(const Vector2& a, const Vector2& b);
		//! 向量乘法（向量与标量相乘）
		friend Vector2 operator*(const Vector2& vec, float scalar);
		//! 向量乘法（标量与向量相乘）
		friend Vector2 operator*(float scalar, const Vector2& vec);
		//! 向量相等
		friend bool operator==(const Vector2& a, const Vector2& b);
	};
}

#endif	// __Dungeon_Math__