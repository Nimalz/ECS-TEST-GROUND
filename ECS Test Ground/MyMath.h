#pragma once

class Vec2
{
public:
	Vec2()
		: x(0.0f), y(0.0f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2 operator-() const;
	Vec2 operator*(const float mul) const;
	Vec2& operator*=(const float mul);
	Vec2 operator+(const Vec2& v);
	Vec2& operator+=(const Vec2& v);
	Vec2 operator-(const Vec2& v);
	Vec2& operator-=(const Vec2& v);


public:
	float x, y;
};
