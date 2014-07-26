#ifdef __APPLE__
#include <GLUT/glut.h>
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
// Accept fragment if it closer to the camera than the former one
glDepthFunc(GL_LESS);
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    gluPerspective(90.0, 1.0, 1.0, 100.0);

    posCameraX = 2.0;
   posCameraY = 1.0;
   posCameraZ = 2.0;
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
          break;
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
    
    
/*  clear all pixels  */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*  draw polygon (rectangle) with corners at
 *  (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
    glBegin(GL_TRIANGLE_STRIP);

     /// FRONT
        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        
        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(5.0, 0.0, 0.0);

        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(0.0, 5.0, 0.0);

        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(5.0, 5.0, 0.0);


///RIGHT
       	glColor3f (0.0, 1.0, 0.0);
        glVertex3f(5.0, 0.0, 0.0);

		glColor3f (0.0, 1.0, 0.0);
        glVertex3f(5.0, 0.0, 5.0);

        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(5.0, 5.0, 0.0);

        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(5.0, 5.0, 5.0);


    /// BACK
        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(5.0, 0.0, 5.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(0.0, 0.0, 5.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(5.0, 5.0, 5.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(0.0, 5.0, 5.0);


// LEFT

        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 5.0);

        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);

        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 5.0, 5.0);

        glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.0, 5.0, 0.0);


/// BOTTOM

        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 5.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(5.0, 0.0, 5.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);

        glColor3f (1.0, 1.0, 1.0);
        glVertex3f(5.0, 0.0, 0.0);

/// TOP

        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 5.0, 0.0);

        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(5.0, 5.0, 0.0);

        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(0.0, 5.0, 5.0);

        glColor3f (1.0, 0.0, 0.0);
        glVertex3f(5.0, 5.0, 5.0);
       
    glEnd();

    //angle += 0.5;
    //cout << angle << endl;
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutDisplayFunc(display); 
    glutSpecialFunc(specialKeys);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
