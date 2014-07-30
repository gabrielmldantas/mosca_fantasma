#include "camera.h"
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#endif
#ifndef __APPLE__
#include <GL/glu.h>
#endif

Camera::Camera(Vector3 eye, Vector3 lookAt, Vector3 up)
	: _eye(eye), _lookAt(lookAt), _up(up), _horizontalAngle(0)
{}

Camera::~Camera()
{}

void Camera::rotateLeft(float angle)
{
	_horizontalAngle -= angle;
	horizontalRotation(_horizontalAngle);
}

void Camera::rotateRight(float angle)
{
	_horizontalAngle += angle;
	horizontalRotation(_horizontalAngle);
}

void Camera::zoomIn(float amount)
{
	zoom(-amount);
}

void Camera::zoomOut(float amount)
{
	zoom(amount);
}

void Camera::horizontalRotation(float angle)
{
	_eye.setX(0.5 * sin(angle));
    _eye.setZ(0.5 * cos(angle));
}

void Camera::zoom(float amount)
{
	_eye.setY(_eye.y() + amount);
}

void Camera::look()
{
	gluLookAt(_eye.x(), _eye.y(), _eye.z(), _lookAt.x(), _lookAt.y(), _lookAt.z(), _up.x(), _up.y(), _up.z());
}