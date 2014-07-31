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
using namespace std;

void Cube::draw()
{
	float vertices[] = {
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0 // BOTTOM
        
    };

    float colors[] = {
        97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97
    };
    
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();
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
    glPopMatrix();
}