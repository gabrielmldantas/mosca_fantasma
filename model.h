#ifndef __MODEL_H__
#define __MODEL_H__
#include "mathutil.h"

class Model
{
public:
	Model() {};
	virtual ~Model() {};

	virtual void draw() = 0;
};

class Cube : public Model
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
private:
	float _area;
	int _multiplierX;
	int _multiplierZ;
	float *_vertices;
};

#endif