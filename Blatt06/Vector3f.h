#pragma once
class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f &other);
	~Vector3f();

	Vector3f operator+(const Vector3f& other) const;
	Vector3f operator-(const Vector3f& other) const;
	Vector3f operator-() const;
	Vector3f operator*(const float scalar) const;
	Vector3f operator/(const float scalar) const;

	Vector3f& operator+=(const Vector3f& other);
	Vector3f& operator-=(const Vector3f& other);
	Vector3f& operator*=(const float scalar);
	Vector3f& operator/=(const float scalar);

	Vector3f cross(Vector3f other);
	void normalize();

	static const Vector3f Zero;

	float x, y, z;
};

inline Vector3f Vector3f::operator+(const Vector3f& vector) const
{
	return Vector3f(x + vector.x, y + vector.y, z + vector.z);
}

inline Vector3f Vector3f::operator-(const Vector3f& vector) const
{
	return Vector3f(x - vector.x, y - vector.y, z - vector.z);
}

inline Vector3f Vector3f::operator-() const
{
	return Vector3f(-x, -y, -z);
}

inline Vector3f Vector3f::operator*(const float scalar) const
{
	return Vector3f(x * scalar, y * scalar, z * scalar);
}

inline Vector3f Vector3f::operator/(const float scalar) const
{
	return Vector3f(x / scalar, y / scalar, z / scalar);
}
