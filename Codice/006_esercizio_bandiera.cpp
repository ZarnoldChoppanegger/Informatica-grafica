#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>

void bandiera()
{
  glShadeModel(GL_FLAT);

  glBegin(GL_QUAD_STRIP);

  // Parte verde della bandiera
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex2f(-0.5f, 0.75f);
  glVertex2f(-0.5f, 0.25f);
  glVertex2f(-0.17f, 0.75f);
  glVertex2f(-0.17f, 0.25f);

  // Parte bianca
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex2f(0.17f, 0.75f);
  glVertex2f(0.17f, 0.25f);

  // Parte rossa
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex2f(0.5f, 0.75f);
  glVertex2f(0.5f, 0.25f);

  glEnd();
}

void cerchio()
{
  glBegin(GL_TRIANGLE_FAN);

  glColor3f(0.0f, 1.0f, 0.0f);
  // vertice centrale
  glVertex2f(0.0f, -0.5f);

  // si calcolano i punti intorno
  const float pi = std::acos(-1);
  const float radius = 0.35f;
  float x {};
  float y {};
  int steps = 10000;
  float k = (2.0f * pi) / steps;

  float start = 0.0f;

  for(int i = 0; i <= steps; ++i) {
    x = std::cos(start) * radius;
    y = std::sin(start) * radius;

    start += k;

    glVertex2f(x, y - 0.5f);
  }

  glEnd();
}

void redraw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  bandiera();
  cerchio();

  glutSwapBuffers();
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 400);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("esercizio bandiera");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
