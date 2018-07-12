// Esempio da http:/www.glprogramming.com/red/chapter03.html

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display()
{
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3f (1.0, 1.0, 1.0);

  // Replaces the current matrix with the identity matrix
  glLoadIdentity ();

  // Viewing transformation (where to place the camera).
  // Creates a viewing matrix derived from an eye point, a reference
  // point indicating the center of the scene, and an UP vector.
  gluLookAt (0.0, 0.0, 2.5, /* eye point */
             0.0, 0.0, 0.0, /* reference point */
             0.0, 1.0, 0.0); /* direction of the UP vector */

  // The current matrix is multiplied by this scale matrix,
  // and the product replaces the current matrix as if
  // `glMultMatrix()` were called with the following matrix
  glScalef (1.0, 2.0, 1.0);

  glutWireCube ( 1.0 );

  glTranslatef (0.0, 0.0, -20.0);

  glutWireCube ( 1.0 );

  glutSwapBuffers ();
}

// Projection transformation (like choosing a lens for a camera).
void reshape (int w, int h)
{
  // Specifies the affine transformation of x and y from
  // normalized device coordinates to window coordinates.
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);

  // Specifies which matrix stack is the target for subsequent matrix operations.
  // In this case the target is the projection matrix.
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glFrustum (-1.0, 1.0, /* left and right vertical clipping planes*/
             -1.0, 1.0, /* bottom and tom horizontal clipping*/
             1.5, 120.0); /* distances to the near and far depth clipping planes*/
  glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition (500, 500);
  glutInitWindowSize (600, 400);
  glutCreateWindow ("Transformed Cude");

  init();

  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return 0;
}
