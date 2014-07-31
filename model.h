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
	void draw();
};

class Room : public Model
{
public:
	Room(float area, int multiplierX, int multiplierZ);
	~Room();
	void draw();
    void addModel(Model *model);
private:
	float _area;
	int _multiplierX;
	int _multiplierZ;
	float *_vertices;
    std::vector<Model*> _modelsInRoom;
};

class ObjModel : public Model
{
public:
    ObjModel(float *vertices, int *faces, int numberOfVertices);
    ~ObjModel();
    void draw();
    int numberOfVertices();
private:
    float *_vertices;
    int *_faces;
    int _numberOfVertices;
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