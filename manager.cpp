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
    if (input.length() > 0)
    {
        RoomLoader loader;
        roomSpec = loader.load(input);
    }
    _fovy = 45;
    _eye = Vector3(0, 0, -2);
    _lookAt = Vector3(0, 0, 1);
    _up = Vector3(0, 1, 0);
	container = new Cube;
	camera = new Camera(_eye, _lookAt, _up);
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

	show();
	glutMainLoop();
}

Manager::~Manager()
{
	delete container;
	delete camera;
    delete roomSpec;
}

void Manager::show()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, 1000/700, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->look();

    container->draw();

    for (int i = 0; i < roomSpec->numberOfRooms(); i++)
    {
        float area = 1.0/roomSpec->numberOfRooms();
        Room *r = new Room(area, i % ((int) round(sqrt(area))), i / round(sqrt(area)));
        r->draw();
        delete r;
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
        camera->up(0.01);
    else if (key == GLUT_KEY_DOWN)
        camera->down(0.01);
    glutPostRedisplay();
}

void Manager::keyboardFunc(unsigned char key, int x, int y)
{
    if (key == 'r')
        camera->updateCoordinates(_eye, _lookAt, _up);
    else if (key == 'w')
        camera->forward(0.01);
    else if (key == 's')
        camera->backward(0.01);
    else if (key == 'a')
        camera->panLeft(0.01);
    else if (key == 'd')
        camera->panRight(0.01);
	glutPostRedisplay();
}
