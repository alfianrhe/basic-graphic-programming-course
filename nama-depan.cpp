// Compile: g++ filename.cpp -o filename -lglut -lGL -lGLU

#include "GL/glut.h"
#include "math.h"


void initGL()
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void timer(int value)
{
  glutPostRedisplay();
  glutTimerFunc(15, timer, 0);
}


void reshape(GLsizei width, GLsizei height)
{
  if (height == 0)
    height = 1;
  GLfloat aspect = (GLfloat)width / (GLfloat)height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0.0, 0.0, -6.0);
  glBegin(GL_LINES);
	glColor3f(0.75,0.5,0.45); // green

	// Outer Square
	glVertex3f(0,0,0); // Starting Coordinate
	glVertex3f(0,2.25,0); // Ending Coordinate

	glVertex3f(0,2.25,0); // Starting Coordinate
	glVertex3f(1.75,2.25,0); // Ending Coordinate

	glVertex3f(1.75,2.25,0); // Starting Coordinate
	glVertex3f(1.75,0,0); // Ending Coordinate

	glVertex3f(1.75,0,0); // Starting Coordinate
	glVertex3f(1.25,0,0); // Ending Coordinate

	glVertex3f(1.25,0,0); // Starting Coordinate
	glVertex3f(1.25,0.75,0); // Ending Coordinate

	glVertex3f(1.25,0.75,0); // Starting Coordinate
	glVertex3f(0.5,0.75,0); // Ending Coordinate

	glVertex3f(0.5,0.75,0); // Starting Coordinate
	glVertex3f(0.5,0,0); // Ending Coordinate

	glVertex3f(0.5,0,0); // Starting Coordinate
	glVertex3f(0,0,0); // Ending Coordinate

	// Center Square
	glVertex3f(0.5,1,0); // Starting Coordinate
	glVertex3f(0.5,2,0); // Ending Coordinate

	glVertex3f(0.5,2,0); // Starting Coordinate
	glVertex3f(1.25,2,0); // Ending Coordinate

	glVertex3f(1.25,2,0); // Starting Coordinate
	glVertex3f(1.25,1,0); // Ending Coordinate

	glVertex3f(1.25,1,0); // Starting Coordinate
	glVertex3f(0.5,1,0); // Ending Coordinate	

  glEnd();

  glFlush();
  glutSwapBuffers();
}

// Main Program
int main(int argc, char **argv) //argv : argument 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("praktikum 1");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  initGL();
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return 0;
}
