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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, 800/600, 1.0, 100.0);
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
    glutKeyboardFunc(::keyboardFuncCallback);
    glutSpecialFunc(::specialKeysCallback);
}

void Manager::specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        _camera->up(0.01);
    else if (key == GLUT_KEY_DOWN)
        _camera->down(0.01);
    else if (key == GLUT_KEY_LEFT)
        _camera->rotateLeft(2*M_PI/180);
    else if (key == GLUT_KEY_RIGHT)
        _camera->rotateRight(2*M_PI/180);
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
    RoomLoader loader;
    _roomSpec = loader.load(input);
    float area = 0.25;
    float totalArea = _roomSpec->numberOfRooms() * (sqrt(area + 0.05));
    float lateralFloor = sqrt(totalArea);
    for (int i = 0; i < _roomSpec->numberOfRooms(); i++)
    {
        Room *r = new Room(area, lateralFloor, i % 2, i / 2);
        for (int j = 0; j < _roomSpec->numberOfObjectsOfFirstTypeInRoom(i+1); j++)
        {
            //Suzanne *suzanne = new Suzanne;
            r->addModel(new ObjModel(1));
        }
        for (int j = 0; j < _roomSpec->numberOfObjectsOfSecondTypeInRoom(i+1); j++)
        {
            r->addModel(new ObjModel(2));
        }
        _rooms.push_back(r);
    }
    _floor = new Floor(totalArea);
}
