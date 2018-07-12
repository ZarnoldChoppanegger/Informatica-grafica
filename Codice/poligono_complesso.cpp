#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void redraw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // Controls the interpolation of polygons.
  // In this case polygons that are fron and back facing
  // are represented only by lines
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // bool bEdgeFlag = false;

  glBegin(GL_TRIANGLES);

  glEdgeFlag(false);
  glVertex2f(-0.2f, 0.0f);
  glEdgeFlag(true);
  glVertex2f(0.2f, 0.0f);
  glVertex2f(0.0f, 0.4f);

  glVertex2f(-0.2f, 0.0f);
  glVertex2f(-0.6f, -0.2f);
  glEdgeFlag(false);
  glVertex2f(-0.2f, -0.4f);
  glEdgeFlag(true);
  glVertex2f(-0.2f, -0.4f);
  glVertex2f(0.0f, -0.8f);
  glEdgeFlag(false);
  glVertex2f(0.2f, -0.4f);

  glEdgeFlag(true);
  glVertex2f(0.2f, -0.4f);
  glVertex2f(0.6f, -0.2f);
  glEdgeFlag(false);
  glVertex2f(0.2f, 0.0f);


  // glVertex2f(-0.2f, 0.0f);
  // glVertex2f(-0.2f, -0.4f);
  // glVertex2f(0.2f, 0.0f);

  glEnd();

  glutSwapBuffers();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 400);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("poligono complesso");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
