#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);
	
	Vector2D operator+(const Vector2D &v) const;
	Vector2D operator-(const Vector2D &v) const;
	void operator+=(const Vector2D &v);
	void operator-=(const Vector2D &v);
	Vector2D operator*(float f) const;
	Vector2D operator/(float f) const;
	void operator*=(float f);
	void operator/=(float f);

	float length() const;
	void normalize();

	static float dotProduct(const Vector2D& v1, const Vector2D& v2);
	static float angleBetween(const Vector2D& v1, const Vector2D& v2);

	float x, y;
};
