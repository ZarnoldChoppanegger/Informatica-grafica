#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>

bool bEdgeFlag = true;

auto polygonMode = GL_FILL;

// Angoli che indicano di quanto deve ruotare l'oggetto
float xRot {};
float yRot {};

enum Mode {
  SHOW_EDGE,
  HIDE_EDGE,
  FILL_MODE,
  LINE_MODE,
  POINT_MODE
};

void processMenu(int mode)
{
  switch( mode ) {
  case SHOW_EDGE:
    bEdgeFlag = true;
    break;

  case HIDE_EDGE:
    bEdgeFlag = false;
    break;

  case FILL_MODE:
    polygonMode = GL_FILL;
    break;

  case LINE_MODE:
    polygonMode = GL_LINE;
    break;

  case POINT_MODE:
    polygonMode = GL_POINT;
    break;
  }

  glutPostRedisplay();
}

void renderScene()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);

  glEdgeFlag(bEdgeFlag);
  glVertex2f(-0.2f, 0.0f);
  glVertex2f(0.2f, 0.0f);
  glVertex2f(0.0f, 0.6f);

  glEnd();

  glPopMatrix();

  glutSwapBuffers();
}

void specialKeys(int k, int x, int y)
{
  switch(k) {
  case GLUT_KEY_UP:
    xRot -= 5.0f;
    xRot = std::fmod(xRot, 365.0f);
    break;

  case GLUT_KEY_DOWN:
    xRot += 5.0f;
    xRot = std::fmod(xRot, 365.0f);
    break;


  case GLUT_KEY_RIGHT:
    yRot += 5.0f;
    yRot = std::fmod(yRot, 365.0f);
    break;


  case GLUT_KEY_LEFT:
    yRot -= 5.0f;
    yRot = std::fmod(yRot, 365.0f);
    break;
  }

  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 400);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("menu");

  int nMainMenu {};
  int nEdgeMenu {};
  int nDrawMenu {};

  nEdgeMenu = glutCreateMenu(processMenu);
  glutAddMenuEntry("ON", Mode::SHOW_EDGE);
  glutAddMenuEntry("OFF", Mode::HIDE_EDGE);

  nDrawMenu = glutCreateMenu(processMenu);
  glutAddMenuEntry("FILL", Mode::FILL_MODE);
  glutAddMenuEntry("LINE", Mode::LINE_MODE);
  glutAddMenuEntry("POINT", Mode::POINT_MODE);

  nMainMenu = glutCreateMenu(processMenu);
  glutAddSubMenu("Edges", nEdgeMenu);
  glutAddSubMenu("Drawing Type", nDrawMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutSpecialFunc(specialKeys);
  glutDisplayFunc(renderScene);

  glutMainLoop();

  return 0;
}
