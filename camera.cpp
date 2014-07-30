#include "camera.h"
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#endif
#ifndef __APPLE__
#include <GL/glu.h>
#endif
#include <iostream>
using namespace std;

Camera::Camera(Vector3 eye, Vector3 lookAt, Vector3 up)
	: _eye(eye), _lookAt(lookAt), _up(up)
{}

Camera::~Camera()
{}

void Camera::rotateLeft(float angle)
{
	rotate(-angle, 0);
}

void Camera::rotateRight(float angle)
{
	rotate(angle, 0);
}

void Camera::rotateUp(float angle)
{
    rotate(0, angle);
}

void Camera::rotateDown(float angle)
{
    rotate(0, -angle);
}

void Camera::rotate(float yaw, float pitch)
{
    Vector3 direction = normalize(_eye - _lookAt);
    Vector3 right = normalize(direction ^ _up);
    float *rotationUp = rotationAroundAxis(_up, yaw);
    float *rotationRight = rotationAroundAxis(right, pitch);
    
    Vector3 rotated = ::rotate(rotationUp, direction);
    rotated = ::rotate(rotationRight, rotated);
    
    rotated = rotated + _lookAt;
    _eye.print();
    _eye = rotated;
    _eye.print();
    
    float *translationMatrix = translationByAxis(Vector3(0, 1, 1));
    //_eye = translate(translationMatrix, _eye);
    
    right = normalize(normalize(_eye - _lookAt) ^ _up);
    _up = normalize(right ^ direction);
    cout << "UP ";
    _up.print();

    delete[] rotationUp;
    delete[] rotationRight;
    delete[] translationMatrix;
}

void Camera::look()
{
	gluLookAt(_eye.x(), _eye.y(), _eye.z(), _lookAt.x(), _lookAt.y(), _lookAt.z(), _up.x(), _up.y(), _up.z());
}
