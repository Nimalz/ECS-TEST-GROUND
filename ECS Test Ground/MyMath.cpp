#include "MyMath.h"

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator*(const float mul) const
{
	return Vec2(mul * x, mul * y);
}

Vec2& Vec2::operator*=(const float mul)
{
	x *= mul;
	y *= mul;

	return *this;
}

Vec2 Vec2::operator+(const Vec2& v)
{
	return Vec2(x + v.x,y + v.y);
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

Vec2 Vec2::operator-(const Vec2& v)
{
	return Vec2(x - v.x,y - v.y);
}

Vec2& Vec2::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}