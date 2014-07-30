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
    _eye = rotated;
    
    right = normalize(normalize(_eye - _lookAt) ^ _up);
    _up = normalize(right ^ direction);

    delete[] rotationUp;
    delete[] rotationRight;
}

void Camera::look()
{
	gluLookAt(_eye.x(), _eye.y(), _eye.z(), _lookAt.x(), _lookAt.y(), _lookAt.z(), _up.x(), _up.y(), _up.z());
}

void Camera::updateCoordinates(Vector3 eye, Vector3 lookAt, Vector3 up)
{
    _eye = eye;
    _lookAt = lookAt;
    _up = up;
}

void Camera::forward(float amount)
{
    
}

void Camera::backward(float amount)
{
   _lookAt.setZ(_lookAt.z() - sin(M_PI/180) * amount);
}

void Camera::panLeft(float amount)
{
    _eye.setX(_eye.x() - amount);
}

float Camera::panRight(float amount)
{
    _eye.setX(_eye.x() + amount);
}