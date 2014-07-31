#ifndef __FILE_UTIL__H__
#define __FILE_UTIL__H__

#include <string>
#include <vector>
#include "model.h"

class RoomSpec
{
public:
	RoomSpec(int numberOfRooms);
	~RoomSpec();
	int numberOfRooms();
	int numberOfObjectsOfFirstTypeInRoom(int roomNumber);
	int numberOfObjectsOfSecondTypeInRoom(int roomNumber);
	void setAverageObjectsOfFirstTypeInRoom(int roomNumber, int avg);
	void setAverageObjectsOfSecondTypeInRoom(int roomNumber, int avg);
	void setDeviationObjectsOfFirstTypeInRoom(int roomNumber, int avg);
	void setDeviationObjectsOfSecondTypeInRoom(int roomNumber, int avg);
private:
	int _numberOfRooms;
	int ***_objects;
};

class RoomLoader
{
public:
	RoomLoader();
	~RoomLoader();
	RoomSpec *load(std::string filePath);
};

std::vector<std::string> split(std::string str, char delimiter);

class ObjLoader
{
public:
    ObjLoader();
    ~ObjLoader();
    ObjModel *load(std::string filePath);
};

#endif