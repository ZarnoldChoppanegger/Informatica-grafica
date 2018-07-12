#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void redraw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 1.0f, 1.0f);

  glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

  // glFlush();
  // swap the buffers (that's for double bufferring)
  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 400);

  // enable double buffering
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("rectangle");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
