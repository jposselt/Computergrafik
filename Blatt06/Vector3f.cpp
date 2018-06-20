#include <math.h>

#include "Vector3f.h"

Vector3f::Vector3f()
	: x(0), y(0), z(0)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3f::Vector3f(const Vector3f & other)
	: x(other.x), y(other.y), z(other.z)
{
}

Vector3f::~Vector3f()
{
}

Vector3f& Vector3f::operator+=(const Vector3f & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3f& Vector3f::operator-=(const Vector3f & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3f& Vector3f::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3f& Vector3f::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3f Vector3f::cross(Vector3f other)
{
	return Vector3f(
		y*other.z - z*other.y,
		z*other.x - x * other.z,
		x*other.y - y * other.x
	);
}

void Vector3f::normalize()
{
	float length = sqrt(x*x + y * y + z * z);
	if (length == 0) {
		return;
	}
	this->operator/=(length);
}

const Vector3f Vector3f::Zero = Vector3f(0, 0, 0);