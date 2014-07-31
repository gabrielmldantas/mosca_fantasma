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

    if (argc < 2)
    {
        cout << "Informe o arquivo contendo a descrição das salas" << endl;
        return 1;
    }
    
    string s(argv[1]);
    Manager m(s);
    return 0;
}
