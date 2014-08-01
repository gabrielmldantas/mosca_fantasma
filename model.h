#ifndef __MODEL_H__
#define __MODEL_H__
#include "mathutil.h"
#include <vector>

class Model
{
public:
	Model() {};
	virtual ~Model() {};
	virtual void draw() = 0;
};

class Floor : public Model
{
public:
	Floor(float totalArea);
	~Floor();
	void draw();
private:
	int ***_colors;
	int _imageWidth;
	int _imageHeight;
	float _totalArea;
	float *_vertices;
	float _lateral;
};

class ObjModel;

class Room : public Model
{
public:
	Room(float area, float lateralFloor, int multiplierX, int multiplierZ);
	~Room();
	void draw();
    void addModel(ObjModel *model);
private:
	float _area;
	float _lateral;
	int _multiplierX;
	int _multiplierZ;
	float *_vertices;
	float _lateralFloor;
    std::vector<ObjModel*> _modelsInRoom;
};

class ObjModel : public Model
{
public:
    ObjModel(float *vertices, int *faces, int numberOfVertices);
    ObjModel(int type);
    ~ObjModel();
    void draw();
    void setPosition(Vector3 position);
    int numberOfVertices();
private:
    float *_vertices;
    int *_faces;
    int _numberOfVertices;
    int _type;
    Vector3 _position;
};

class Suzanne : public Model
{
public:
    Suzanne();
    ~Suzanne();
    void draw();
private:
    ObjModel *_model;
};

#endif