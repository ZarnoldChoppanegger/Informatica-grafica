#include <iostream>
#include <GL/glut.h>

void reshape(int w, int h)
{
  std::cout << "event: reshaped to " 
            << " w= " << w << " h= " << h << '\n';
}

void expose()
{
  std::cout << "event: exposed\n";
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(500, 500);
  glutInitWindowSize(150, 150);
  glutCreateWindow("reshaped and exposed");

  // quando la finestra viene ridimensionata,
  // viene chiamata la funzione reshape().
  // Questa si occupera' di settare i parametri di viewing
  glutReshapeFunc(reshape);
  // Quando la finestra e' visibile viene chiamata la funzione expose()
  glutDisplayFunc(expose);

  glutMainLoop();

  return 0;
}
