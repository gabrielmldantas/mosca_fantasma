#include "fileutil.h"
#include <sstream>
#include <istream>
#include <fstream>
#include <iostream>
using namespace std;

RoomSpec::RoomSpec(int numberOfRooms)
	: _numberOfRooms(numberOfRooms)
{
	_objects = new int**[numberOfRooms];
	for (int i = 0; i < numberOfRooms; i++)
	{
		_objects[i] = new int*[2];
		_objects[i][0] = new int[2];
		_objects[i][1] = new int[2];
	}
}
RoomSpec::~RoomSpec()
{
	for (int i = 0; i < _numberOfRooms; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			delete[] _objects[i][j];
		}
		delete[] _objects[i];
	}
	delete[] _objects;
}

int RoomSpec::numberOfRooms()
{
	return _numberOfRooms;
}

int RoomSpec::numberOfObjectsOfFirstTypeInRoom(int roomNumber)
{
	return _objects[roomNumber - 1][0][0];
}

int RoomSpec::numberOfObjectsOfSecondTypeInRoom(int roomNumber)
{
	return _objects[roomNumber - 1][1][0];
}

void RoomSpec::setAverageObjectsOfFirstTypeInRoom(int roomNumber, int avg)
{
	_objects[roomNumber - 1][0][0] = avg;
}

void RoomSpec::setAverageObjectsOfSecondTypeInRoom(int roomNumber, int avg)
{
	_objects[roomNumber - 1][1][0] = avg;	
}

void RoomSpec::setDeviationObjectsOfFirstTypeInRoom(int roomNumber, int dev)
{
	_objects[roomNumber - 1][0][1] = dev;
}

void RoomSpec::setDeviationObjectsOfSecondTypeInRoom(int roomNumber, int dev)
{
	_objects[roomNumber - 1][1][1] = dev;
}

vector<string> split(string str, char delimiter)
{
	vector<string> vec;
	stringstream ss(str);
	string i;
	while (getline(ss, i, delimiter))
	{
		vec.push_back(i);
	}
	return vec;
}

RoomLoader::RoomLoader() {}
RoomLoader::~RoomLoader() {}

RoomSpec *RoomLoader::load(string filePath)
{
	filebuf file;
	file.open(filePath, ios::in);
	istream is(&file);
	string s;
	getline(is, s);
	int numberOfRooms = stoi(s);
	RoomSpec *spec = new RoomSpec(numberOfRooms);
	for (int i = 0; i < numberOfRooms; i++)
	{
		getline(is, s);
		vector<string> elements = split(s, ' ');
		spec->setAverageObjectsOfFirstTypeInRoom(i + 1, stoi(elements[2]));
		spec->setDeviationObjectsOfFirstTypeInRoom(i + 1, stoi(elements[3]));
		spec->setAverageObjectsOfSecondTypeInRoom(i + 1, stoi(elements[5]));
		spec->setDeviationObjectsOfSecondTypeInRoom(i + 1, stoi(elements[6]));
	}
	file.close();
	return spec;
}

ObjLoader::ObjLoader()
{}

ObjLoader::~ObjLoader()
{}

ObjModel *ObjLoader::load(string filePath)
{
    filebuf file;
    file.open(filePath, ios::in);
    istream is(&file);
    string line;
    vector<float> vertices;
    vector<int> faces;
    while (getline(is, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            istringstream ss(line.substr(2));
            float v;
            for (int i = 0; i < 3; i++)
            {
                ss >> v;
                vertices.push_back(v);
            }
            //vertices.push_back(1.0);
        }
        else if (line.substr(0, 2) == "f ")
        {
            istringstream ss(line.substr(2));
            int f;
            for (int i = 0; i < 3; i++)
            {
                ss >> f;
                faces.push_back(f);
            }
        }
    }
    
    float *vertices_array = new float[vertices.size()];
    int *faces_array = new int[faces.size()];
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices_array[i] = vertices[i];
        faces_array[i] = faces[i];
    }
    ObjModel *model = new ObjModel(vertices_array, faces_array, vertices.size());
    return model;
}