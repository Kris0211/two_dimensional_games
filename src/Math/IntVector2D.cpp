#include "IntVector2D.h"
#include <cmath>
#include <stdexcept>

IntVector2D::IntVector2D() : x(0), y(0) {}

IntVector2D::IntVector2D(const int x, const int y) : x(x), y(y) {}

IntVector2D::IntVector2D(const IntVector2D &v) : x(v.x), y(v.y) {}

bool IntVector2D::operator==(const IntVector2D &v) const
{
	return x == v.x && y == v.y;
}

bool IntVector2D::operator!=(const IntVector2D &v) const
{
	return x != v.x || y != v.y;
}

IntVector2D IntVector2D::operator+(const IntVector2D &v) const
{
	return { x + v.x, y + v.y };
}

IntVector2D IntVector2D::operator-(const IntVector2D &v) const
{
	return { x - v.x, y - v.y };
}

void IntVector2D::operator+=(const IntVector2D &v)
{
	this->x += v.x;
	this->y += v.y;
}

void IntVector2D::operator-=(const IntVector2D &v)
{
	this->x -= v.x;
	this->y -= v.y;
}

IntVector2D IntVector2D::operator*(const int f) const
{
	return { x * f, y * f };
}

IntVector2D IntVector2D::operator/(int f) const
{
	if (f != 0)
	{
		f = 1 / f;
		return { x * f, y * f };
	}
	throw std::runtime_error("Math error: Cannot divide by zero\n");
}

void IntVector2D::operator*=(const int f)
{
	x *= f;
	y *= f;
}

void IntVector2D::operator/=(int f)
{
	if (f != 0)
	{
		f = 1 / f;
		x *= f;
		y *= f;
	}
	else throw std::runtime_error("Math error: Cannot divide by zero\n");
}

float IntVector2D::length() const
{
	return static_cast<float>(sqrt(
		this->x * this->x +
		this->y * this->y));
}

void IntVector2D::normalize()
{
	const float n = this->length();
	if (n != 0.0f) {
		this->x /= n;
		this->y /= n;
	}
}

IntVector2D IntVector2D::normal() const
{
	const float n = this->length();
	IntVector2D vec = *this;
	if (n != 0.0f) vec /= n;
	return vec;
}

IntVector2D IntVector2D::clamp(const IntVector2D &v, const IntVector2D &min, const IntVector2D &max)
{
	IntVector2D vec = v;
	if (v.x < min.x) vec.x = min.x;
	else if (v.x > max.x) vec.x = max.x;

	if (v.y < min.y) vec.y = min.y;
	else if (v.y > max.y) vec.y = max.y;

	return vec;
}

float IntVector2D::dotProduct(const IntVector2D &v1, const IntVector2D &v2)
{
	IntVector2D vec;
	vec.x = v1.x * v2.x;
	vec.y = v1.y * v2.y;
	return static_cast<float>(vec.x + vec.y);
}

float IntVector2D::angleBetween(const IntVector2D &v1, const IntVector2D &v2)
{
	return acos(dotProduct(v1, v2) / (v1.length() * v2.length()));
}
