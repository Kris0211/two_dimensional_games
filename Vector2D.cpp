#include "Vector2D.h"
#include <cmath>
#include <stdexcept>

Vector2D::Vector2D() : x(0), y(0){}

Vector2D::Vector2D(int x, int y) : x(x), y(y) {}

Vector2D::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

Vector2D::~Vector2D() {}

bool Vector2D::operator==(const Vector2D& v)
{
	return this->x == v.x && this->y == v.y;
}

bool Vector2D::operator!=(const Vector2D& v)
{
	return this->x != v.x || this->y != v.y;
}

Vector2D Vector2D::operator+(const Vector2D &v)
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(const Vector2D &v)
{
	return Vector2D(x - v.x, y - v.y);
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

Vector2D Vector2D::operator*(int f)
{
	return Vector2D(x * f, y * f);
}

Vector2D Vector2D::operator/(int f)
{
	if (f != 0.0f)
	{
		f = 1 / f;
		return Vector2D(x * f, y * f);
	}
	else
	{
		throw std::runtime_error("Math erorr: Cannot divide by zero\n");
	}
}

void Vector2D::operator*=(int f)
{
	x *= f;
	y *= f;
}

void Vector2D::operator/=(int f)
{
	if (f != 0.0f)
	{
		f = 1 / f;
		x *= f;
		y *= f;
	}
	else
	{
		throw std::runtime_error("Math erorr: Cannot divide by zero\n");
	}
}

float Vector2D::length() const
{
	return (float)sqrt(
		(this->x * this->x) +
		(this->y * this->y));
}

void Vector2D::normalize()
{
	float n = this->length();
	if (n != 0) {
		this->x /= n;
		this->y /= n;
	}
	else throw std::runtime_error("Math erorr: Cannot divide by zero\n");
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
	return acos(Vector2D::dotProduct(v1, v2) / (v1.length() * v2.length()));
}
