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

#endif