#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void redraw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLE_STRIP);

  glColor3f(0.25f, 0.45f, 0.8f);
  glVertex2f(0.0f, 0.0f);
  glColor3f(0.75f, 0.25f, 0.1f);
  glVertex2f(0.5f, 0.5f);
  glColor3f(0.1f, 0.85f, 0.4f);
  glVertex2f(0.5f, 0.0f);
  glColor3f(1.0f, 1.0f, 1.0f);

  glEnd();

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(0.0f, 0.0f);
  glutInitWindowSize(600, 400);
  glutInitDisplayMode(GLUT_SINGLE);

  glutCreateWindow("triangles");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
