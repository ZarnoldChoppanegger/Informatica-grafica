#include <iostream>
#include <string>
#include <GL/glut.h>

// Per tastiera
void processNormalKeys(unsigned char key, int x, int y)
{
  // premi esc per terminare
  if( key == 27 )
    exit (0);
}

void mouse(int button, int state, int x, int y)
{
  std::string b {};
  std::string left = "left";
  std::string middle = "middle";
  std::string right = "right";
  std::string s {};
  std::string press = "pressed";
  std::string rel = "released";

  switch( button )
    {
    case GLUT_LEFT_BUTTON:
      {
        b = left;
        break;
      }

    case GLUT_MIDDLE_BUTTON:
      {
        b = middle;
        break;
      }

    case GLUT_RIGHT_BUTTON:
      {
        b = right;
        break;
      } 
    }

  switch( state ) {

  case GLUT_DOWN :
    {
      s = press;
      break;
    }

  case GLUT_UP :
    {
      s = rel;
      break;
    }
  }

  std::cout << b << " mouse button " << s
            << " in " << x << " , " << y << '\n';
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(600, 400);

  glutCreateWindow("keyboard and mouse");

  glutKeyboardFunc(processNormalKeys);
  glutMouseFunc(mouse);

  glutMainLoop();

  return 0;
}
