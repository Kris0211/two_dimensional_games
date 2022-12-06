#include "Vector2D.h"
#include <cmath>
#include <stdexcept>

Vector2D::Vector2D() : x(0), y(0){}

Vector2D::Vector2D(const float x, const float y) : x(x), y(y) {}

Vector2D::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

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

float Vector2D::dotProduct(const Vector2D& v1, const Vector2D& v2)
{
	Vector2D vect;
	vect.x = v1.x * v2.x;
	vect.y = v1.y * v2.y;
	return vect.x + vect.y;
}

float Vector2D::angleBetween(const Vector2D& v1, const Vector2D& v2)
{
	return acos(dotProduct(v1, v2) / (v1.length() * v2.length()));
}
