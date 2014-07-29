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

vec3f toPolar(vec3f vec)
{
    vec3f p;
    p.x = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    p.y = atan(p.y / p.x);
    p.z = atan(sqrt(pow(vec.x, 2) + pow(vec.y, 2))/ vec.z);
    return p;
}

vec3f toCartesian(vec3f vec)
{
    vec3f c;
    c.x = vec.x * sin(vec.z) * cos(vec.y);
    c.y = vec.x * sin(vec.z) * sin(vec.y);
    c.z = vec.x * cos(vec.z);
    return c;
}

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
    vec3f c;
    c.x = 0;
    c.y = 2;
    c.z = 0.1;
    pos = c;
    
}

void specialKeys(int key, int x, int y)
{
   angle += M_PI/4; 
   vec3f c;
   switch (key) {
       case GLUT_KEY_LEFT : 
            pos.x = 2 * sin(angle);
            pos.z = 2 * cos(angle);
            break;
       case GLUT_KEY_RIGHT : 
            break;
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
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
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255
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
    glutKeyboardFunc(keyFunc);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
