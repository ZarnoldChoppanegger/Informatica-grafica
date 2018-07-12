#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <chrono>
#include <iostream>

int rot_y {};
int rot_x {};
int rot_magnitude {1};

int old_x {};
int old_y {};

auto current_time = std::chrono::system_clock::now();
auto start_time = current_time;
std::chrono::duration<double, std::milli> delta_animation_time { (1 / 60) * 1000 };

// To manage mouse input
bool get_info {false};

void render()
{
  glClearDepth (0.5);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // // set up view and camera
  // const float w = glutGet (GLUT_WINDOW_WIDTH);
  // const float h = glutGet (GLUT_WINDOW_HEIGHT);

  // glViewport (0, 0, w, h);

  // glMatrixMode (GL_PROJECTION);
  // glLoadIdentity ();
  // gluPerspective (60.0, w / h, 1.0, 100.0);
  // gluLookAt (0.0, 3.0, 3.0,
  //            0.0, -1.0, 0.0,
  //            0.0, 1.0, 0.0);

  // // from here only manipulations on objects
  // glMatrixMode (GL_MODELVIEW);

  glPushMatrix ();
  glLoadIdentity ();
  glRotatef (rot_y, 0.0, 1.0, 0.0);
  glRotatef (rot_x, 1.0, 0.0, 0.0);
  glutWireCube (1.0);

  glTranslatef (0.5, 0.0, -20.0);
  glutWireSphere(1.0, 100, 100);

  glPopMatrix ();

  glutSwapBuffers();
}

void reshapeWindow (int w, int h)
{
  // Try to see how ortho works
  glViewport (0, 0, w, h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (-2.0, 2.0,
           -2.0, 2.0,
           -1.5, 20);
  // gluPerspective (60.0, h / w, 1.0, 100.0);
  // gluLookAt (0.0, 0.0, 5.0,
  //            0.0, 0.0, 0.0,
  //            0.0, 1.0, 0.0);
  glMatrixMode (GL_MODELVIEW);
}
void getMouseActions(int k , int s, int x, int y)
{
  current_time = std::chrono::system_clock::now();

  if ( k == GLUT_LEFT_BUTTON &&
       s == GLUT_DOWN &&
       (current_time - start_time) > delta_animation_time) {

    get_info = true;
    old_x = x;
    old_y = y;
    start_time = current_time;
  }

  else {
    get_info = false;
  }
}

void getMousePosition (int x, int y)
{
  if (get_info == true) {

    // Manage movements on x axis
    if (x - old_x > 0) {
      rot_y = (++rot_y * rot_magnitude) % 365;
    }

    else if (x - old_x < 0) {
      rot_y = (--rot_y * rot_magnitude) % 365;
    }

    // reset variable
    old_x = x;

    // Manage movements on y axis
    if (y - old_y > 0) {
      rot_x = (++rot_x * rot_magnitude) % 365;
    }

    else if (y - old_y < 0) {
      rot_x = (--rot_x * rot_magnitude) % 365;
    }

    old_y = y;

    glutPostRedisplay();
  }
}

int main (int argc, char** argv)
{
  glutInit (&argc, argv);
  glutInitWindowPosition (600, 400);
  glutInitWindowSize (600, 400);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glEnable (GL_DEPTH_TEST);

  glutCreateWindow ("Cubo ruotante");

  glutDisplayFunc (render);
  glutMouseFunc (getMouseActions);  
  glutMotionFunc (getMousePosition);
  glutReshapeFunc (reshapeWindow);
  // glutIdleFunc (rotationAnimation);

  glutMainLoop ();
}
