#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
#include <GL/freeglut.h>
#endif
#include <iostream>
#include <cmath>
using namespace std;

float angle = 0.0;

typedef struct {
    float x;
    float y;
    float z;
} vec3f;

vec3f pos;

void init (void) 
{
/*  select clearing (background) color       */
    glClearColor (0.0, 0.0, 0.0, 0.0);
	

/*  initialize viewing values  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable (GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
   // glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    gluPerspective(45.0, 1000/700, 1.0, 100.0);
    vec3f c;
    c.x = 0;
    c.y = 2;
    c.z = 1;
    pos = c;
    
}

void specialKeys(int key, int x, int y)
{
   vec3f c;
   switch (key) {
       case GLUT_KEY_LEFT : 
            angle -= M_PI/180; 
            pos.x = 0.5 * sin(angle);
            pos.z = 0.5 * cos(angle);
            break;
       case GLUT_KEY_RIGHT : 
            angle += M_PI/180; 
            pos.x = 0.5 * sin(angle);
            pos.z = 0.5 * cos(angle);
            break;
        case GLUT_KEY_UP:
            angle += M_PI/180; 
            pos.y = 2 * sin(angle);
            pos.z = 2 * cos(angle);
            break;
        case GLUT_KEY_DOWN:
            angle -= M_PI/180; 
            pos.y = 2 * sin(angle);
            pos.z = 2 * cos(angle);
            break;
   }
   glutPostRedisplay();
}

void keyFunc(unsigned char key, int x, int y)
{

}

void display(void)
{
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   gluLookAt(pos.x, pos.y, pos.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


   float vertexes[] = {
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, // BOTTOM
        1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, // RIGHT
        1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, // FRONT
        0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, // LEFT
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0 // BOTTOM
        
   };

   float colors[] = {
        97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255
   };
    
    
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_CURRENT_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertexes);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_QUADS, 0, 20);

    glPopMatrix();
    glPopAttrib();

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
    glutKeyboardFunc(keyFunc);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
