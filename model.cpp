#include "model.h"
#include "glutil.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
#include <GL/glut.h>
#endif
#include <cmath>
#include <iostream>
#include "fileutil.h"
using namespace std;

Floor::Floor(float totalArea)
    : _totalArea(totalArea)
{
    float base_vertices[] = {
        1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0
    };
    _vertices = new float[12];
    _lateral = sqrt(totalArea);
    for (int i = 0; i < 12; i++)
    {
        _vertices[i] = base_vertices[i] * _lateral;
    }
    /*JpegReader r;
    string s("floor.jpg");
    _colors = r.load(s, &_imageWidth, &_imageHeight);*/
}

Floor::~Floor()
{
    delete[] _vertices;
    /*for (int i = 0; i < _imageWidth; i++)
    {
        for (int j = 0; j < _imageHeight; j++)
        {
            delete[] _colors[i][j];
        }
        delete[] _colors[i];
    }
    delete[] _colors;*/
}

void Floor::draw()
{
    float colors[] = {
        97, 97, 97, 97, 97, 97, 97, 97, 97
    };
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, _vertices);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

Room::Room(float area, float lateralFloor, int multiplierX, int multiplierZ)
    : _area(area), _lateralFloor(lateralFloor), _multiplierX(multiplierX), _multiplierZ(multiplierZ)
{
    _vertices = new float[48];
    float base[] = {
        1, 0, 0, 1, 0, 1, 1, 0.2, 1, 1, 0.2, 0, // RIGHT
        1, 0, 1, 0, 0, 1, 0, 0.2, 1, 1, 0.2, 1, // FRONT
        0, 0, 1, 0, 0, 0, 0, 0.2, 0, 0, 0.2, 1, // LEFT
        1,0, 0, 0, 0, 0, 0, 0.2, 0, 1, 0.2, 0 // BACK
    };

    int c = 0;
    _lateral = sqrt(_area);
    for (int i = 0; i < 48; i++)
    {
        c++;
        if (c != 2)
        {
            _vertices[i] = base[i] * _lateral;
        }
        else
        {
            _vertices[i] = base[i];
            c = -1;
        }
    }
}

Room::~Room()
{
    delete[] _vertices;
}

void Room::draw()
{
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
    glTranslatef(_lateral * _multiplierX, 0, _lateral * _multiplierZ);
    glTranslatef(0.05 * _multiplierX, 0, 0.05 * _multiplierZ);
    glDrawArrays(GL_QUADS, 0, 16);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    for (int i = 0; i < _modelsInRoom.size(); i++)
    {
        Vector3 position(i % 3 + 0.05, 0.05, i / 3 + 0.05);
        _modelsInRoom[i]->setPosition(position);
        _modelsInRoom[i]->draw();
    }
    
    glPopMatrix();
}

void Room::addModel(ObjModel *model)
{
    _modelsInRoom.push_back(model);
}

ObjModel::ObjModel(float *vertices, int *faces, int numberOfVertices)
    : _vertices(vertices), _faces(faces), _numberOfVertices(numberOfVertices)
{}

ObjModel::ObjModel(int type)
    : _type(type)
{}

ObjModel::~ObjModel()
{
    delete[] _vertices;
    delete[] _faces;
}

void ObjModel::draw()
{
    glPushMatrix();
    glTranslatef(_position.x(), _position.y(), _position.z());
    //glDrawElements(GL_TRIANGLES, _numberOfVertices / 3, GL_UNSIGNED_INT, _faces);
    
    //glScalef(0.25, 0.25, 0.25);
    glColor3f(0, 0, 1);
    if (_type == 1)
        glutSolidTeapot(0.05);
    else
        glutSolidCube(0.05);
    glPopMatrix();
}

int ObjModel::numberOfVertices()
{
    return _numberOfVertices;
}

void ObjModel::setPosition(Vector3 position)
{
    _position = position;
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
