#include "manager.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
#include <GL/freeglut.h>
#endif
#include "mathutil.h"
#include <cmath>
#include <iostream>
#include "fileutil.h"
using namespace std;

Manager *currentInstance;
void displayCallback()
{
	if (currentInstance)
	{
		currentInstance->show();
	}
}

void specialKeysCallback(int key, int x, int y)
{
	if (currentInstance)
	{
		currentInstance->specialKeys(key, x, y);
	}
}

void keyboardFuncCallback(unsigned char key, int x, int y)
{
	if (currentInstance)
	{
		currentInstance->keyboardFunc(key, x, y);
	}
}

Manager::Manager(string input)
{
    _fovy = 45;
    _eye = Vector3(0, 0, -2);
    _lookAt = Vector3(0, 0, 1);
    _up = Vector3(0, 1, 0);
	
	_camera = new Camera(_eye, _lookAt, _up);
    ::currentInstance = this;
    glutCreateWindow("Mosca Fantasma");
	registerCallbacks();
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    loadRooms(input);
    
	show();
	glutMainLoop();
}

Manager::~Manager()
{
	delete _floor;
	delete _camera;
    delete _roomSpec;
    for (int i = 0; i < _rooms.size(); i++)
    {
        delete _rooms[i];
    }
}

void Manager::show()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, 1000/700, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _camera->look();

    _floor->draw();
    
    for (int i = 0; i < _rooms.size(); i++)
    {
        _rooms[i]->draw();
    }
    
    glutSwapBuffers();
}

void Manager::registerCallbacks()
{
	glutDisplayFunc(::displayCallback); 
    glutIdleFunc(::displayCallback);
    glutKeyboardFunc(::keyboardFuncCallback);
    glutSpecialFunc(::specialKeysCallback);
}

void Manager::specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        _camera->up(0.01);
    else if (key == GLUT_KEY_DOWN)
        _camera->down(0.01);
    glutPostRedisplay();
}

void Manager::keyboardFunc(unsigned char key, int x, int y)
{
    if (key == 'r')
        _camera->updateCoordinates(_eye, _lookAt, _up);
    else if (key == 'w')
        _camera->forward(0.01);
    else if (key == 's')
        _camera->backward(0.01);
    else if (key == 'a')
        _camera->panLeft(0.01);
    else if (key == 'd')
        _camera->panRight(0.01);
	glutPostRedisplay();
}

void Manager::loadRooms(string input)
{
    _floor = new Floor;
    RoomLoader loader;
    _roomSpec = loader.load(input);
    for (int i = 0; i < _roomSpec->numberOfRooms(); i++)
    {
        float area = 1.0/_roomSpec->numberOfRooms();
        Room *r = new Room(area, i % ((int) round(sqrt(area))), i / round(sqrt(area)));
        for (int j = 0; j < _roomSpec->numberOfObjectsOfFirstTypeInRoom(i+1); j++)
        {
            Suzanne *suzanne = new Suzanne;
            r->addModel(suzanne);
        }
        _rooms.push_back(r);
    }
}
