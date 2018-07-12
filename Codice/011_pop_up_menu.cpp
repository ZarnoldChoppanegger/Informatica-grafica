#include <cmath>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// Rotation amounts
float xRot = 0.0f;
float yRot = 0.0f;

// Flags for effects
enum Mode {
  MODE_SOLID,
  MODE_LINE,
  MODE_POINT
};

Mode mode {};

bool bEdgeFlag = true;

void ProcessMenu(int value)
{
  switch (value)
    {
    case MODE_SOLID:
      mode = MODE_SOLID;
      break;

    case MODE_LINE:
      mode = MODE_LINE;
      break;

    case MODE_POINT:
      mode = MODE_POINT;
      break;

    case 3:
      bEdgeFlag = true;
      break;

    case 4:
      bEdgeFlag = false;
      break;
    }

  // Alla prossima iterazione del mainloop, la funzione registrata
  // con glutDisplayFunct(), viene invocata in modo da aggiornare la scena.
  // Questo viene usato per le animazioni.
  glutPostRedisplay();
}

void RenderScene()
{
  glClear(GL_COLOR_BUFFER_BIT);

  if(mode == MODE_LINE)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  if(mode == MODE_POINT)
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  if(mode == MODE_SOLID)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // OpenGL per tenere traccia delle posizioni e stati degli oggetti usa matrici.
  // Queste sono memorizzate in uno stack ed inserendole o rimuovendole dallo stack,
  // si aggiorna la posizione degli oggetti
  glPushMatrix();
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  glBegin(GL_TRIANGLES);

  glEdgeFlag(bEdgeFlag);
  glVertex2f(-0.2f, 0.0f);
  glEdgeFlag(true);
  glVertex2f(0.2f, 0.0f);
  glVertex2f(0.0f, 0.6f);
  glVertex2f(-0.2f, 0.0f);
  glVertex2f(0.0f, -0.6f);
  glEdgeFlag(bEdgeFlag);
  glVertex2f(0.2f, 0.0f);

  glEnd();

  glutSolidTeapot(0.4f);

  glPopMatrix();

  glutSwapBuffers();
}

void SetupRC()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
}

void SpecialKeys(int key, int x, int y)
{
  if( key == GLUT_KEY_UP )
    xRot -= 5.0f;

  if( key == GLUT_KEY_DOWN )
    xRot += 5.0f;

  if( key == GLUT_KEY_RIGHT )
    yRot += 5.0f;

  if( key == GLUT_KEY_LEFT )
    yRot -= 5.0f;

  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  int nModeMenu {};
  int nEdgeMenu {};
  int nMainMenu {};

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("Solid and Outlined");

  // Creo i menu della scena
  nModeMenu = glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("Solid", 0);
  glutAddMenuEntry("Outline", 1);
  glutAddMenuEntry("Points", 2);

  nEdgeMenu = glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("On", 3);
  glutAddMenuEntry("Off", 4);

  nMainMenu = glutCreateMenu(ProcessMenu);
  glutAddSubMenu("Mode", nModeMenu);
  glutAddSubMenu("Edges", nEdgeMenu);

  // Se premo tasto destro apro menu
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // per gestire caratteri speciali della tastiera
  glutSpecialFunc(SpecialKeys);
  glutDisplayFunc(RenderScene);

  SetupRC();

  glutMainLoop();

  return 0;
}


