#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "model.h"
#include "camera.h"

class Manager
{
public:
	Manager();
	~Manager();
	void show();
	void specialKeys(int key, int x, int y);
	void keyboardFunc(unsigned char key, int x, int y);
private:
	Model *container;
	Camera *camera;
    float _fovy;
    Vector3 _eye;
    Vector3 _lookAt;
    Vector3 _up;
	void registerCallbacks();
};

#endif