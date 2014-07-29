#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

float posCameraX,posCameraY,posCameraZ;
float angle = 0.0;

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);
	

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    gluPerspective(45.0, 1000/700, 1.0, 5000.0);

    posCameraX = 0.0;
   posCameraY = 2.0;
   posCameraZ = 0.1;
}

void specialKeys(int key, int x, int y)
{
   float angulo = 2*M_PI/180;
   cout << "X " << posCameraX << endl;
   cout << "Z " << posCameraZ << endl;
   switch (key) {
       case GLUT_KEY_LEFT : 
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;
       case GLUT_KEY_RIGHT : 
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);                      
            break;
        case GLUT_KEY_UP:
          posCameraY -= 0.1;
          break;

        case GLUT_KEY_DOWN:
          posCameraY += 0.1;
   }
   glutPostRedisplay();
}

void display(void)
{
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   gluLookAt(posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //glRotatef(180, 0.0f, 1.0f, 0.0f); 
   // glRotatef(angle, 0.0f, 1.0f, 0.0f); 

   float vertexes[] = {
        0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1,
        1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1,
        0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0,
        0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1
   };

   float colors[] = {
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
        0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
        1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
        1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0
   };
    
    
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertexes);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

    glPopMatrix();
    //angle += 0.1;
    //cout << angle << endl;
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1000, 700); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutDisplayFunc(display); 
    glutSpecialFunc(specialKeys);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
