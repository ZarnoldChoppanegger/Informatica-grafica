#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void render ()
{
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix ();
  glTranslatef (0.0, 0.0, -5.0);
  glutWireCube (1.0);
  glPopMatrix();

  glutSwapBuffers ();
}

// This function is called every time the window is resized.
// This allows the viewport to be also resized, thus keeping
// the aspect ratio of the viewing volume.
void reshape (int w, int h)
{
  const float ratio = (float) w / (float) h;

  glMatrixMode (GL_PROJECTION);
  gluPerspective (60.0, ratio, 1.0, 100.0);
  glViewport (0, 0, w, h);
  gluLookAt (0.0, 0.0, 5.0,
             0.0, 0.0, 0.0,
             0.0, 1.0, 0.0);
  glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitWindowPosition (500, 500);
  glutInitWindowSize (600, 400);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow ("Viewport");

  glutDisplayFunc (render);
  glutReshapeFunc (reshape);

  glutMainLoop();
}
