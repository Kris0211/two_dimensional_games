#pragma once
#pragma once

class IntVector2D
{
public:
	IntVector2D();
	IntVector2D(int x, int y);
	IntVector2D(const IntVector2D &v);

	bool operator==(const IntVector2D &v) const;
	bool operator!=(const IntVector2D &v) const;

	IntVector2D operator+(const IntVector2D &v) const;
	IntVector2D operator-(const IntVector2D &v) const;
	void operator+=(const IntVector2D &v);
	void operator-=(const IntVector2D &v);
	IntVector2D operator*(int f) const;
	IntVector2D operator/(int f) const;
	void operator*=(int f);
	void operator/=(int f);

	float length() const;
	void normalize();
	IntVector2D normal() const;

	static float dotProduct(const IntVector2D &v1, const IntVector2D &v2);
	static float angleBetween(const IntVector2D &v1, const IntVector2D &v2);
	static IntVector2D clamp(const IntVector2D &v, const IntVector2D& min, const IntVector2D &max);

	int x, y;
};
