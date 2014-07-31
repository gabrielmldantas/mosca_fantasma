#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "model.h"
#include "camera.h"
#include <string>
#include "fileutil.h"
#include <vector>

class Manager
{
public:
	Manager(std::string input);
	~Manager();
	void show();
	void specialKeys(int key, int x, int y);
	void keyboardFunc(unsigned char key, int x, int y);
private:
	Floor *_floor;
	Camera *_camera;
    float _fovy;
    Vector3 _eye;
    Vector3 _lookAt;
    Vector3 _up;
    RoomSpec *_roomSpec;
    std::vector<Room*> _rooms;
	void registerCallbacks();
    void loadRooms(std::string input);
};

#endif