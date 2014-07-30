#include "model.h"
#include "glutil.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif
#ifndef __APPLE__
#include <GL/gl.h>
#endif

void Cube::draw()
{
	float vertices[] = {
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, // BOTTOM
        1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, // RIGHT
        1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, // FRONT
        0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, // LEFT
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0 // BACK
        
    };

    float colors[] = {
        97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255,
        0, 132, 255, 0, 132, 255, 0, 132, 255, 0, 132, 255
    };
    
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glDrawArrays(GL_QUADS, 0, 20);
    glPopMatrix();
}
