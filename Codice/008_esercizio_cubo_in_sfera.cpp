#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>

const float pi = std::acos(-1);
const float radius = 1.0f;

void redraw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);
  glutSolidCube(std::sin(pi / 4) * radius * 2.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
  glutWireSphere(radius, 100, 100);

  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 600);

  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glEnable(GL_DEPTH_TEST);

  glutCreateWindow("cubo in sfera");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
