#include "GL/glut.h"
#include "stdio.h"
#include "math.h"
#define PI 3.14159265

float R_Z=0.0f, R_X=0.0f, R_Y=0.0f;  
float T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;  

void initGL()
{  
    glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Bola()
{  
float NEW_BODY_RADIUS;
float BODY_RADIUS=1.2f;
float BODY_LENGTH=1.0f;
double clip_plane[]= {0.0,0.0,-1.0,0.0};
    // for separate half side of ball
glClipPlane(GL_CLIP_PLANE5,clip_plane);
glEnable(GL_CLIP_PLANE5);  
int SLICES=120;  
int STACKS=120;  
    GLUquadric *q = gluNewQuadric();  
    gluSphere(q, BODY_RADIUS, SLICES, STACKS);
    gluDeleteQuadric(q);
    glDisable(GL_CLIP_PLANE5);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
}

float degreeToRadian(float degree) {
  // 360 degree = 2 pi radian
  //   1 degree = 2 pi / 360 radian
  //   1 degree = pi / 180 radian
  return (degree * PI) / 180.0;
}

void segiBeraturan(float r, int segi, float sudutAwal) {
  float besarSudutRad = degreeToRadian(360.0/segi);
  float sudutAwalRad = degreeToRadian(sudutAwal);
  glBegin(GL_POLYGON);
  for (int titikKe = 0; titikKe < segi; titikKe ++) {
    float sudut1 = besarSudutRad * titikKe + sudutAwalRad;
    float sudut2 = besarSudutRad * (titikKe + 1) + sudutAwalRad;
    float x1 = cos(sudut1) * r;
    float x2 = cos(sudut2) * r;
    float y1 = sin(sudut1) * r;
    float y2 = sin(sudut2) * r;
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    }
  glEnd();
}

void lingkaran(){
  segiBeraturan(0.5, 36, 0) ; // Lingkaran
}

void segiEmpat()
{
  glBegin(GL_POLYGON);
    glVertex3f(-1,1,-1);
	  glVertex3f(-1,0,1);
	  glVertex3f(1,0,1);
	  glVertex3f(1,1,-1);
  glEnd();
}

void balingBaling()
{
  // glBegin(GL_POLYGON);
  //   glVertex3f(-0.5,0,-0.5);
	//   glVertex3f(0.5,0,0.5);
	//   glVertex3f(0.5,0,-0.5);
  // glEnd();
  glBegin(GL_POLYGON);
    glVertex3f(-0.5,0,-0.5);
	  glVertex3f(0.0,0,-0.25);
	  glVertex3f(0.5,0,-0.5);
  glEnd();
  // glBegin(GL_POLYGON);
  //   glVertex3f(-1,0,-1);
	//   glVertex3f(-1,0,1);
	//   glVertex3f(1,0,1);
	//   glVertex3f(1,0,-1);
  // glEnd;
}
float sudut = 0;
void display()
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glLoadIdentity();

        // gluLookAt(1,2,3, // eye pos
        //         1,1,-1, // Look At
        //         0,0,1);  // up
    
    glTranslatef(-T_X, T_Y, T_Z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);  
    
    glRotatef(R_X, 1.0f, 0.0f, 0.0f);  
    glRotatef(R_Y, 0.0f, 1.0f, 0.0f);  
    glRotatef(R_Z, 0.0f, 0.0f, 1.0f);  
    
    segiEmpat();

  glTranslatef(0.0, 0.5, 0.0);
  glColor3f(0.0,1.0,1.0);
  lingkaran();

  glPushMatrix();
  glColor3f(1,0,0);
  glTranslatef(2,0,0);
  glRotatef(sudut,0,-1,0);
  balingBaling();
  glPopMatrix();

  glPushMatrix();
  glColor3f(0,0,1);
  glTranslatef(-2,0,0);
  glRotatef(sudut,0,1,0);
  balingBaling();
  glPopMatrix();
  sudut++;
    
    glFlush();  
    glutSwapBuffers();  
}  

void timer(int value)
{  
	glutPostRedisplay();  
    glutTimerFunc(15, timer, 0);  
}  

void reshape(GLsizei width, GLsizei height)
{  
if (height == 0) height = 1;  
    GLfloat aspect = (GLfloat)width / (GLfloat)height;  
    glViewport(30, 6, width, height);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluPerspective(45.0f, aspect, 1.0f, 20.0f);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  

void keyFunction(unsigned char key, int x, int y){  
switch(key){  
case 79: // Rotasi sumbu Z dengan tombol O
        R_Z = R_Z + 15.0f;  
	break;  
case 73: // Rotasi sumbu Y dengan tombol I
        R_Y = R_Y + 15.0f;  
	break;  
case 76: // Rotasi sumbu X dengan tombol L
        R_X = R_X + 15.0f;  
	break;  
case 81: // Translasi sumbu Z dengan tombol Q
        T_Z = T_Z + 0.5f;  
	break;
case 69: // Translasi sumbu Z dengan tombol E
        T_Z = T_Z - 0.5f;  
	break;  
case 87: // Translasi sumbu Y dengan tombol W
        T_Y = T_Y + 0.5f;  
	break;
case 83: // Translasi sumbu X dengan tombol S
        T_Y = T_Y - 0.5f;  
	break;      
case 68: // Translasi sumbu X dengan tombol D
        T_X = T_X - 0.5f;  
	break;
case 65: // Translasi sumbu X dengan tombol A
        T_X = T_X + 0.5f;  
	break;  
	}
}  

int main(int argc, char **argv)
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  
    glutInitWindowSize(640, 480);  
    glutInitWindowPosition(50, 50);  
    glutCreateWindow("3d-control");  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  
    glutKeyboardFunc(keyFunction);  
    initGL();  
    glutTimerFunc(0, timer, 0); 
    glutMainLoop();
    return 0;
} 