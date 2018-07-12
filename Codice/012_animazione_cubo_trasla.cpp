#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

float xPos {};
float step = 0.01f;

int startTime {};

// funzione che crea le animazioni tenendo traccia
// della posizione degli oggetti
void animation()
{
  if(glutGet(GLUT_ELAPSED_TIME) - startTime > 50) {
    startTime = glutGet(GLUT_ELAPSED_TIME);

    xPos += step;

    if(xPos >= 0.5f) {
      step = -step;
    }

    else if(xPos < -0.4f) {
      step = -step;
    }

    glutPostRedisplay();
  }
}

void renderScene()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  glutIdleFunc(animation);
  glTranslatef(xPos, 0.0f, 0.0f);

  glRectf(-0.2f, -0.2f, 0.2f, 0.2f);

  glPopMatrix();

  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("cube animation");

  glutDisplayFunc(renderScene);

  glutMainLoop();
}
