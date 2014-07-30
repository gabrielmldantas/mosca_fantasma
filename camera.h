#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "mathutil.h"

class Camera
{
public:
	Camera(Vector3 eye, Vector3 lookAt, Vector3 up);
	~Camera();
	void rotateLeft(float angle);
	void rotateRight(float angle);
    void rotateUp(float angle);
    void rotateDown(float angle);
	void look();
private:
	Vector3 _eye;
	Vector3 _lookAt;
	Vector3 _up;
	void rotate(float yaw, float pitch);
};

#endif
