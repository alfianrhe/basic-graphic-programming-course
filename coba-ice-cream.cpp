#include "GL/glut.h"
#include "stdio.h"
#include "math.h"

float R_Z=0.0f, R_X=0.0f, R_Y=0.0f;  
float T_Z=-16.0f, T_X=0.0f, T_Y=0.0f;  

void initGL()
{  
    glShadeModel(GL_FLAT);

    float ambient[] = {1.0f,1.0f,1.0f,1.0f};
    float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
    float specular[] = {0.2f,1.0f,0.2f,1.0f};
    float position[] = {20.0f,30.0f,20.0f,0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);  
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular); 

    float mambient[] ={0.2588f, 0.4588f, 0.745f, 0.55f};  
    float mdiffuse[] ={0.545f, 0.6784f, 0.9725f, 0.55f };  
    float mspecular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };  
    float mshine =76.8f;  
	glMaterialfv(GL_FRONT,GL_AMBIENT,mambient);  
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mdiffuse);  
	glMaterialfv(GL_FRONT,GL_SPECULAR,mspecular);  
	glMaterialf (GL_FRONT,GL_SHININESS,mshine);  
	glEnable(GL_LIGHTING); 
	glEnable(GL_LIGHT0);  
	glEnable(GL_DEPTH_TEST);  
	glEnable(GL_NORMALIZE);  
}

void Bola()
{  
float NEW_BODY_RADIUS;
float BODY_RADIUS=1.2f;
float BODY_LENGTH=1.0f;
double clip_plane[]= {0.0,0.0,-1.0,0.0};
    // for separate half side of ball
glClipPlane(GL_CLIP_PLANE0,clip_plane);
glEnable(GL_CLIP_PLANE0);  
int SLICES=120;  
int STACKS=120;  
    GLUquadric *q = gluNewQuadric();  
    gluSphere(q, BODY_RADIUS, SLICES, STACKS);
    gluDeleteQuadric(q);
    glDisable(GL_CLIP_PLANE0);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);
}

void Tabung()
    {  
    float BODY_LENGTH=3.0f;  
    float BODY_RADIUS=1.2f;  
    float BODY_RADIUS2=1.4f;  
    int SLICES=120;  
    int STACKS=120;  
        GLUquadric *q = gluNewQuadric();
        gluDisk(q, 0.0f, BODY_RADIUS2, SLICES, STACKS);  
        gluCylinder(q, BODY_RADIUS2, BODY_RADIUS2, 0.5f, SLICES, STACKS);  
        glTranslatef(0.0f, 0.0f, 0.5f);
        gluDisk(q, 0.0f, BODY_RADIUS2, SLICES, STACKS);          
        gluCylinder(q, BODY_RADIUS, 0, BODY_LENGTH, SLICES, STACKS);  
        // gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS);  
        // glTranslatef(0.0f, 0.0f, BODY_LENGTH);  
    }

void display()
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glLoadIdentity();

        gluLookAt(1,2,3, // eye pos
                1,1,-1, // Look At
                0,1,0);  // up
    
    glTranslatef(-T_X, T_Y, T_Z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);  
    
    glRotatef(R_X, 1.0f, 0.0f, 0.0f);  
    glRotatef(R_Y, 0.0f, 1.0f, 0.0f);  
    glRotatef(R_Z, 0.0f, 0.0f, 1.0f);  
    
    glPushMatrix();
    Tabung();
    glPopMatrix();

    //  glTranslatef(0.0f,0.0f,2.0f);
    
    glPushMatrix();
    Bola();
    glPopMatrix();
    
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