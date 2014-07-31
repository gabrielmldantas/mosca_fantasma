#include "model.h"
#include "glutil.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif
#ifndef __APPLE__
#include <GL/gl.h>
#endif
#include <cmath>
#include <iostream>
#include "fileutil.h"
using namespace std;

void Floor::draw()
{
	float vertices[] = {
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0 // BOTTOM
        
    };

    float colors[] = {
        97, 97, 97, 97, 97, 97, 97, 97, 97
    };
    
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

Room::Room(float area, int multiplierX, int multiplierZ)
    : _area(area), _multiplierX(multiplierX), _multiplierZ(multiplierZ)
{
    _vertices = new float[48];
}

Room::~Room()
{
    delete[] _vertices;
}

void Room::draw()
{
    float base[] = {
        1, 0, 0, 1, 0, 1, 1, 0.2, 1, 1, 0.2, 0, // RIGHT
        1, 0, 1, 0, 0, 1, 0, 0.2, 1, 1, 0.2, 1, // FRONT
        0, 0, 1, 0, 0, 0, 0, 0.2, 0, 0, 0.2, 1, // LEFT
        1,0, 0, 0, 0, 0, 0, 0.2, 0, 1, 0.2, 0 // BACK
    };
    int c = 0;
    for (int i = 0; i < 48; i++)
    {
        c++;
        if (c != 2)
        {
            _vertices[i] = base[i] * sqrt(_area);
        }
        else
        {
            _vertices[i] = base[i];
            c = -1;
        }
    }

    float colors[] = {
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0,
        0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0,
        100, 0, 255, 100, 0, 255, 100, 0, 255, 100, 0, 255
    };

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, _vertices);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glTranslatef(sqrt(_area) * _multiplierX, 0, sqrt(_area) * _multiplierZ);
    glTranslatef(0.05 * _multiplierX, 0, 0.05 * _multiplierZ);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    for (int i = 0; i < _modelsInRoom.size(); i++)
    {
        _modelsInRoom[i]->draw();
    }
    
    glPopMatrix();
}

void Room::addModel(Model *model)
{
    _modelsInRoom.push_back(model);
}

ObjModel::ObjModel(float *vertices, int *faces, int numberOfVertices)
    : _vertices(vertices), _faces(faces), _numberOfVertices(numberOfVertices)
{}

ObjModel::~ObjModel()
{
    delete[] _vertices;
    delete[] _faces;
}

void ObjModel::draw()
{
    glPushMatrix();
    glDrawElements(GL_TRIANGLES, _numberOfVertices() / 3, GL_UNSIGNED_INT, _faces);
    glTranslatef(-0.5, -0.5, -0.5);
    //glScalef(0.25, 0.25, 0.25);
    glPopMatrix();
}

int ObjModel::numberOfVertices()
{
    return _numberOfVertices;
}

Suzanne::Suzanne()
{
    ObjLoader loader;
    string s("suzanne.obj");
    _model = loader.load(s);
}

Suzanne::~Suzanne() {}

void Suzanne::draw()
{
    _model->draw();
}
