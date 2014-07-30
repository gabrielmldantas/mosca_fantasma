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

Manager::Manager()
{
    _fovy = 60;
	container = new Cube;
	camera = new Camera(Vector3(0, 1, -0.00759104), Vector3(0, 0, 0), Vector3(0, 0.00986202, -1));
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
}

void Manager::show()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_fovy, 1000/700, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->look();

    container->draw();

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
    switch (key) {
        case GLUT_KEY_LEFT : 
            camera->rotateLeft(M_PI/180);
            break;
        case GLUT_KEY_RIGHT : 
            camera->rotateRight(M_PI/180);
            break;
        case GLUT_KEY_UP:
            camera->rotateUp(M_PI/180);
            break;
        case GLUT_KEY_DOWN:
            camera->rotateDown(M_PI/180);
            break;
   }
   glutPostRedisplay();
}

void Manager::keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'w')
        _fovy -= 1;
	else if (key == 's')
        _fovy += 1;
    cout  << _fovy << endl;
	glutPostRedisplay();
}
