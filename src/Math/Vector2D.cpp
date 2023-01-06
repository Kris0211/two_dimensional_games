#include "Vector2D.h"
#include <cmath>
#include <stdexcept>

Vector2D::Vector2D() : x(0), y(0){}

Vector2D::Vector2D(const float x, const float y) : x(x), y(y) {}

Vector2D::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

bool Vector2D::operator==(const Vector2D &v)
{
	return x == v.x && y == v.y;
}

bool Vector2D::operator!=(const Vector2D &v)
{
	return x != v.x || y != v.y;
}

Vector2D Vector2D::operator+(const Vector2D &v) const
{
	return {x + v.x, y + v.y};
}

Vector2D Vector2D::operator-(const Vector2D &v) const
{
	return {x - v.x, y - v.y};
}

void Vector2D::operator+=(const Vector2D &v)
{
	this->x += v.x;
	this->y += v.y;
}

void Vector2D::operator-=(const Vector2D &v)
{
	this->x -= v.x;
	this->y -= v.y;
}

Vector2D Vector2D::operator*(const float f) const
{
	return {x * f, y * f};
}

Vector2D Vector2D::operator/(float f) const
{
	if (f != 0.0f)
	{
		f = 1 / f;
		return {x * f, y * f};
	}
	else throw std::runtime_error("Math error: Cannot divide by zero\n");
}

void Vector2D::operator*=(const float f)
{
	x *= f;
	y *= f;
}

void Vector2D::operator/=(float f)
{
	if (f != 0.0f)
	{
		f = 1 / f;
		x *= f;
		y *= f;
	}
	else throw std::runtime_error("Math error: Cannot divide by zero\n");
}

float Vector2D::length() const
{
	return sqrt(
		(this->x * this->x) +
		(this->y * this->y));
}

void Vector2D::normalize()
{
	const float n = this->length();
	if (n != 0.0f) {
		this->x /= n;
		this->y /= n;
	}
}

Vector2D Vector2D::normal() const
{
	const float n = this->length();
	Vector2D vec = *this;
	if (n != 0.0f) vec /= n;
	return vec;
}

Vector2D Vector2D::clamp(const Vector2D &v, const Vector2D &min, const Vector2D &max)
{
	Vector2D vec = v;
	if (v.x < min.x) vec.x = min.x;
	else if (v.x > max.x) vec.x = max.x;

	if (v.y < min.y) vec.y = min.y;
	else if (v.y > max.y) vec.y = max.y;

	return vec;
}

float Vector2D::dotProduct(const Vector2D &v1, const Vector2D &v2)
{
	Vector2D vec;
	vec.x = v1.x * v2.x;
	vec.y = v1.y * v2.y;
	return vec.x + vec.y;
}

float Vector2D::angleBetween(const Vector2D &v1, const Vector2D &v2)
{
	return acos(dotProduct(v1, v2) / (v1.length() * v2.length()));
}
