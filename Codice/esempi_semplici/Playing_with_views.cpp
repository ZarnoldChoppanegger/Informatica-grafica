#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int year {};

void render ()
{
  const float w = glutGet (GLUT_WINDOW_WIDTH);
  const float h = glutGet (GLUT_WINDOW_HEIGHT);

  glClear (GL_COLOR_BUFFER_BIT);

  glViewport (0, 0, w, h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (60.0, w/h, 1.0, 20.0); 
  glMatrixMode (GL_MODELVIEW);

  gluLookAt (0.0, 0.0, 5.0,
             0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

  glutWireCube (1.0);

  glPushMatrix (); 
  glRotatef(45, 0.0, 0.0, 1.0); 
  glTranslatef (5.0, 0.0, 0.0);
  glutWireCube (0.5);
  glPopMatrix ();

  glutSwapBuffers ();
}

void reshape (int w, int h)
{
  if (h == 0)
    h = 1;

  float ratio = 1.0 * w / h;

  glMatrixMode (GL_PROJECTION);
  
  glLoadIdentity ();

  glViewport (0, 0, w, h);

  gluPerspective (45, ratio, 1, 1000);

  glMatrixMode (GL_MODELVIEW);

  // glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  // glMatrixMode (GL_PROJECTION);
  // glLoadIdentity ();
  // glFrustum (-1.0, 1.0,
  //              -1.0, 1.0,
  //             1.5, 20.0);
  // glMatrixMode (GL_MODELVIEW);
}

  void keyboard( unsigned char k ,int x, int y)
  {
    switch (k) {
      // w
    case 119 :
      // move up
      break;
      // d
    case 100 :
      // move right
      break;
      // s
    case 115 :
      // move down
      break;
      // a
    case 97 :
      // move left
      break;
    }

    glutPostRedisplay();
  }

  void specialKeys(int k , int x, int y)
  {
    switch (k) {

    case GLUT_KEY_UP :
      // look up
      break;
    case GLUT_KEY_RIGHT :
      // look right
      break;
    case GLUT_KEY_DOWN :
    // look down
    break;
  case GLUT_KEY_LEFT :
    // look left
    break;
  }

  glutPostRedisplay();
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitWindowPosition (500, 500);
  glutInitWindowSize (600, 400);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow ("Views");

  glutDisplayFunc (render);
  // glutReshapeFunc (reshape);

  glutMainLoop();

  return 0;
}
