#include "mathutil.h"
#include <cmath>

Vector3::Vector3() 
	: _x(0), _y(0), _z(0) {}

Vector3::Vector3(float x, float y, float z)
	: _x(x), _y(y), _z(z) {}

float Vector3::x() const
{
	return _x;
}

float Vector3::y() const
{
	return _y;
}

float Vector3::z() const
{
	return _z;
}

void Vector3::setX(float x)
{
	_x = x;
}

void Vector3::setY(float y)
{
	_y = y;
}

void Vector3::setZ(float z)
{
	_z = z;
}

float Vector3::length()
{
	return sqrt(_x * _x + _y * _y + _z * _z);
}

float Vector3::scalar(Vector3 rhs)
{
	return _x * rhs.x() + _y * rhs.y() + _z * rhs.z();
}

Vector3 operator*(Vector3 lhs, float num)
{
	Vector3 v(lhs.x() * num, lhs.y() * num, lhs.z() * num);
	return v;
}

Vector3 operator^(Vector3 lhs, Vector3 rhs)
{
	return Vector3(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
		lhs.z() * rhs.x() - lhs.x() * rhs.z(),
		lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

Vector3 operator+(Vector3 lhs, Vector3 rhs)
{
	return Vector3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}
Vector3 operator-(Vector3 lhs, Vector3 rhs)
{
	return Vector3(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}
bool operator==(Vector3 lhs, Vector3 rhs)
{
	return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}