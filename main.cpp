#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
#include <GL/freeglut.h>
#endif
#include "manager.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1000, 700); 
    glutInitWindowPosition (100, 100);

    string input;
    if (argc > 1)
    	input = string(argv[1]);
    Manager m(input);
    return 0;
}
