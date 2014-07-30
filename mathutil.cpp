#include "mathutil.h"
#include <cmath>
#include <iostream>
using namespace std;

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

void Vector3::print()
{
    cout << "X: " << _x << ", Y: " << _y << ", Z: " << _z << endl;
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

Vector3 normalize(Vector3 vec)
{
    float length = vec.length();
    Vector3 normalized(vec.x() / length, vec.y() / length, vec.z() / length);
    return normalized;
}

float *rotationX(float angle)
{
    float *matrix = new float[9];
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = cos(angle);
    matrix[5] = -sin(angle);
    matrix[6] = 0;
    matrix[7] = sin(angle);
    matrix[8] = cos(angle);
    return matrix;
}

float *rotationY(float angle)
{
    float *matrix = new float[9];
    matrix[0] = cos(angle);
    matrix[1] = 0;
    matrix[2] = sin(angle);
    matrix[3] = 0;
    matrix[4] = 1;
    matrix[5] = 0;
    matrix[6] = -sin(angle);
    matrix[7] = 0;
    matrix[8] = cos(angle);
    return matrix;
}

float *rotationZ(float angle)
{
    float *matrix = new float[9];
    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[2] = 0;
    matrix[3] = sin(angle);
    matrix[4] = cos(angle);
    matrix[5] = 0;
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 1;
    return matrix;
}

float *rotationAroundAxis(Vector3 axis, float angle)
{
    float *matrix = new float[9];
    matrix[0] = cos(angle) + axis.x() * axis.x() * (1 - cos(angle));
    matrix[1] = axis.x() * axis.y() * (1 - cos(angle)) - axis.z() * sin(angle);
    matrix[2] = axis.x() * axis.z() * (1 - cos(angle)) + axis.y() * sin(angle);
    matrix[3] = axis.y() * axis.x() * (1 - cos(angle)) + axis.z() * sin(angle);
    matrix[4] = cos(angle) + axis.y() * axis.y() * (1 - cos(angle));
    matrix[5] = axis.y() * axis.z() * (1 - cos(angle)) - axis.x() * sin(angle);
    matrix[6] = axis.z() * axis.x() * (1 - cos(angle)) - axis.y() * sin(angle);
    matrix[7] = axis.z() * axis.y() * (1 - cos(angle)) + axis.x() * sin(angle);
    matrix[8] = cos(angle) + axis.z() * axis.z() * (1 - cos(angle));
    return matrix;
}

Vector3 rotate(float *rotationMatrix, Vector3 vector)
{
    Vector3 rotated;
    rotated.setX(rotationMatrix[0] * vector.x() + rotationMatrix[1] * vector.y() + rotationMatrix[2] * vector.z());
    rotated.setY(rotationMatrix[3] * vector.x() + rotationMatrix[4] * vector.y() + rotationMatrix[5] * vector.z());
    rotated.setZ(rotationMatrix[6] * vector.x() + rotationMatrix[7] * vector.y() + rotationMatrix[8] * vector.z());
    return rotated;
}

float *translationByAxis(Vector3 axis)
{
    float *matrix = new float[16];
    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = axis.x();;
    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = axis.y();
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = 1;
    matrix[11] = axis.z();
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
    return matrix;
}
Vector3 translate(float *translationMatrix, Vector3 vector)
{
    Vector3 translated;
    translated.setX(translationMatrix[0] * vector.x() + translationMatrix[1] * vector.y() + translationMatrix[2] * vector.z() + translationMatrix[3]);
    translated.setX(translationMatrix[4] * vector.x() + translationMatrix[5] * vector.y() + translationMatrix[6] * vector.z() + translationMatrix[7]);
    translated.setX(translationMatrix[8] * vector.x() + translationMatrix[9] * vector.y() + translationMatrix[10] * vector.z() + translationMatrix[11]);
    return translated;
}
