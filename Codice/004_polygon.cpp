#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

void redraw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Specifica il tipo di tecnica di shading da utlizzare.
  // Accetta i valori GL_FLAT e GL_SMOOTH (di default)
  // glShadeModel(GL_FLAT);

  glBegin(GL_POLYGON);

  glColor3f(0.8f, 0.2f, 0.5f);
  glVertex2f(-0.5f, -0.5f);
  glColor3f(0.3f, 0.7f, 0.6f);
  glVertex2f(0.0f, 0.5f);
  glColor3f(0.5f, 0.4f, 0.1f);
  glVertex2f(0.5f, -0.5f);

  glEnd();

  glFlush();
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(600, 400);

  glutInitDisplayMode(GLUT_SINGLE);

  glutCreateWindow("polygon");

  glutDisplayFunc(redraw);

  glutMainLoop();
}
