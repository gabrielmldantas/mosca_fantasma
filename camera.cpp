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
    _eye = _eye + _lookAt * amount;
    _lookAt = _lookAt + _lookAt * amount;
}

void Camera::backward(float amount)
{
    _eye = _eye + _lookAt * -amount;
    _lookAt = _lookAt + _lookAt * -amount;
}

void Camera::panLeft(float amount)
{
    Vector3 right = normalize((_eye - _lookAt) ^ _up);
    _eye = _eye + right * amount;
}

void Camera::panRight(float amount)
{
    Vector3 right = normalize((_eye - _lookAt) ^ _up);
    _eye = _eye + right * -amount;   
}

void Camera::up(float amount)
{
    _eye = _eye + _up * amount;
}

void Camera::down(float amount)
{
    _eye = _eye + _up * -amount;
}