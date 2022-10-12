#pragma once
#include <string>

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	Vector2D(const Vector2D& v);
	~Vector2D();
	
	bool operator==(const Vector2D &v);
	bool operator!=(const Vector2D &v);
	Vector2D operator+(const Vector2D &v);
	Vector2D operator-(const Vector2D &v);
	void operator+=(const Vector2D &v);
	void operator-=(const Vector2D &v);
	Vector2D operator*(int f);
	Vector2D operator/(int f);
	void operator*=(int f);
	void operator/=(int f);

	float length() const;
	void normalize();

	static float dotProduct(const Vector2D& v1, const Vector2D& v2);
	static float angleBetween(const Vector2D& v1, const Vector2D& v2);

	int x, y;
};