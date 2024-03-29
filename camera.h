#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "mathutil.h"

class Camera
{
public:
	Camera(Vector3 eye, Vector3 lookAt, Vector3 up);
	~Camera();
    void forward(float amount);
    void backward(float amount);
    void panLeft(float amount);
    void panRight(float amount);
    void up(float amount);
    void down(float amount);
    void rotateLeft(float angle);
    void rotateRight(float angle);
	void look();
    void updateCoordinates(Vector3 eye, Vector3 lookAt, Vector3 up);
private:
	Vector3 _eye;
	Vector3 _lookAt;
	Vector3 _up;
};

#endif
