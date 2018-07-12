#include <GL/glut>
#include <GL/glu>
#include <GL/gl>

void redraw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_LINES);

  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.5f, 0.5f);

  glColor3f(0.23f, 0.75f, 0.5f);
  glVertex3f(0.5f, 0.5f, -0.3f);
  glVertex4f(-0.5,0.4,0.7,3.0);

  glEnd();

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 400);
  glutInitDisplayMode(GLUT_SINGLE);

  glutCreateWindow("lines");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
