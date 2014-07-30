#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	float x() const;
	float y() const;
	float z() const;
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float length();
	float scalar(Vector3 rhs);
    void print();
private:
	float _x;
	float _y;
	float _z;
};

Vector3 operator*(Vector3 lhs, float num);
Vector3 operator^(Vector3 lhs, Vector3 rhs);
Vector3 operator+(Vector3 lhs, Vector3 rhs);
Vector3 operator-(Vector3 lhs, Vector3 rhs);
bool operator==(Vector3 lhs, Vector3 rhs);

Vector3 normalize(Vector3 vec);

float *rotationX(float angle);
float *rotationY(float angle);
float *rotationZ(float angle);
float *rotationAroundAxis(Vector3 axis, float angle);
Vector3 rotate(float *rotationMatrix, Vector3 vector);

float *translationByAxis(Vector3 axis);
Vector3 translate(float *translationMatrix, Vector3 vector);

#endif
