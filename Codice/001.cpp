#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// ###--Callback function--###
void redraw() {

  // Specify the rgba values used by glClear()
  // to clear the color buffers.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Sets the selected buffers to the previosly
  // defined values
  glClear(GL_COLOR_BUFFER_BIT);

  // With glEnd() they delimit the vertices that
  // define a prmitive or a group of like primitives.
  // glBegin() accepts a single argument that specifies
  // which of ten ways the vertices are interpreted
  glBegin(GL_POINTS);

  // Command used to define the coordinates of a point
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.5f, 0.5f);

  // End of vertices definition
  glEnd();

  // Empties all buffers, causing all issued commands to
  // be executed as quickly as they are accepted by the
  // actual rendering engine
  glFlush();
}

int main(int argc, char** argv)
{
  // ###--Initialization--###
  // Initialize the GLUT library and negotiate a
  // session with the window system.
  glutInit(&argc, argv);

  // Windows created by `glutCreateWindow()` will be requested
  // to be created with the current initial window position and size
  glutInitWindowPosition(100, 200);
  glutInitWindowSize(320, 200);

  // sets the GLUT display mode bit masks (similar to OpenGL buffers)
  glutInitDisplayMode(GLUT_SINGLE);

  // ###--Create one or more windows--### 
  glutCreateWindow("esempio 1");

  // ###--Register callback functions and their related events--###
  // Sets the display callback for the current window.
  glutDisplayFunc(redraw);

  // ###--Start the main loop--###
  // Enters the GLUT event processing loop. Once called, this routine
  // will never return. It will call as necessary any callbacks that
  // have been registered.
  glutMainLoop();
}
