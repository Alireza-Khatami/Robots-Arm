//Include necessary header files
#include "freeglut.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
//Link with necessary libraries.
//This need to be written in at least one .cpp file in the project
//#pragma comment (lib, "freeglut.lib")

struct axis 
{
	float x;
	float y;
	float z;
};
class Robot_joint
{
public:

	float sizex, sizey, sizez,theta1;
	 Robot_joint(float sizex, float sizey, float sizez) {
		this->sizex = sizex;
		this->sizey = sizey;
		this->sizez = sizez;
	 }
	 void draw(float r, float g, float b, axis d = { 0,0,1 }, axis transfer = { 0,0,0 }) {


		float color[] = { r, g, b, 0.25f };
		//float specularColor[] = {1.0, 0.0f, 0.0f, 1.0f};
		//glutSolidSphere(size, 360, 100);
		
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glMaterialfv(GL_FRONT, GL_SPECULAR, color);
			glMateriali(GL_FRONT, GL_SHININESS, 120);
			glRotatef(theta1, d.x, d.y,d.z);
			glTranslated(sizex / 2, 0, 0);
			glPushMatrix();
			glScalef(sizex,sizey,sizez);
			glutSolidCube(1);
			glPopMatrix();
			glTranslated(sizex/2, 0, 0);
			//glTranslated(sizex, 0, 0);
		

	}
};



//Callback function prototypes
void render(void);
void onKeyboard(unsigned char, int, int);
void update(void);

#define ESC_ASCII 27

int g_Win;	//Stores window identifier (handle) returned by glutCreateWindow
			//We need this handle to terminate the window
int selector = 0;
float Const_theta_start = 180 / 3.14;
float g_X = 0.0f, g_Theta = 0.0f, g_Z = 50.0f, g_Y = 0.0, theta1 =0;
float r = 50, theta2 = Const_theta_start, beta1 = 0;
Robot_joint list_of_Joints[8] = { {4,2,2} ,{4, 2, 2},{3, 2, 2},{2, .5, .5} ,{3,.5 ,.5},{3,.5 ,.5},{3,.5 ,.5},{3,.5 ,.5} };

//Robot_joint r1 = Robot_joint(4,2,2);
//Robot_joint r2 = Robot_joint(4, 2, 2);
//Robot_joint r3 = Robot_joint(3, 2, 2);
//Robot_joint finger1_J = Robot_joint(2, .5, .5);
//Robot_joint finger2_J = Robot_joint(3,.5 ,.5);
//Robot_joint finger3_J = Robot_joint(3, .5, .5);
//Robot_joint finger4_J = Robot_joint(3, .5, .5);
//Robot_joint finger5_J = Robot_joint(3, .5, .5);
int main(int argc, char** argv)
{


	//==========================================
	//Step 1: Initialize GLUT
	//==========================================
	glutInit(&argc, argv);

	//GLUT_RGBA: Red, Green, Blue, Alpha color representation.
	//GLUT_DOUBLE: Double buffering 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glClearDepth(0.0f);
	glDepthFunc(GL_LEQUAL);

	//Create Window
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	g_Win = glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
	//Set the color to be used to clear display buffer.
	//Try different values.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Set projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);

	//==========================================
	//Step 2: Register callback functions
	//==========================================
	glutDisplayFunc(render);
	glutKeyboardFunc(onKeyboard);
	glutIdleFunc(update);

	glEnable(GL_LIGHTING);	//Enable lighting
	glEnable(GL_SPECULAR);
	glEnable(GL_NORMALIZE);	//Enable auto-normalization of normal vectors
	float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);	//Zero global ambient component
	glShadeModel(GL_SMOOTH);



	//Setup material


	//==========================================
	//Step 3: Enter main loop
	//==========================================
	glutMainLoop();
	return 0;
}

//Callback function definitions
void render(void)
{
	//Clear display buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Draw something
	glLoadIdentity();
	float second_R = r * cosf(theta2);
	gluLookAt(second_R * sinf(beta1), r * sin(theta2), second_R * cosf(beta1), 0, 0.0, 0, 0, r * cos(theta2), 0);

		//Sunlight0
	float light0position[] = { 0.0f,0.0f,0.0f,1.0f };
	float light0Ambient[] = { 1.0f, 1.0f, 1.0f , 1.0f };
	float light0Diffuse[] = { 1.0f, 1.0f, 1.0f };
	//float light0Specular[] = {1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light0position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glEnable(GL_LIGHT0);	//Enable light source 0

	//glRotatef(sun.angle + 30, 1, 0, 0);
	axis colors[] = { {1,1,0},{0,1,1},{1,0,1} };
	glPushMatrix();
	for (unsigned int i = 0;i < 3;i++) 
		list_of_Joints[i].draw(colors[i].x, colors[i].y, colors[i].z);

		glPushMatrix();
		glRotatef(60, 0, 1, 0);
		glTranslated(2, 0, 0);
		list_of_Joints[3].draw(1, 0, 0);
		glPopMatrix();


		axis locs[] = { {2,0,-.75},{2,0,0},{2,0,.75},{2,0,1.5} };

		for (int i = 4;i < 8; i++) {
		glPushMatrix();
		glTranslated(locs[i-4].x, locs[i - 4].y, locs[i - 4].z);
		list_of_Joints[i].draw(1, 0, 0);
		glPopMatrix();
	}



	glPopMatrix();





	//Output color buffer to screen
	glutSwapBuffers();
}


void update(void) {

	
	
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int, int)
{
	switch (key)
	{
		case 'i':
			if (selector + 1 > 7)
				selector = 0;
			else
				selector += 1;
			break;
		case 'u':
			if (selector - 1 < 0)
				selector = 7;
			else
				selector -= 1;
			break;
		case 'e':
			list_of_Joints[selector].theta1 += 10;
			break;
		case 'q':
			list_of_Joints[selector].theta1 -= 10;
			break;
		case 'm': {

			theta2 += .1;
			std::cout << theta2 << " ######### " << beta1 << std::endl;
		}

			break;
		case 'n': {
			theta2 -= .1;
			std::cout << theta2 << " ######### " << beta1 << std::endl;}
			break;

		case 'p': {
			for (unsigned int i = 0;i < 8;i++) {
				list_of_Joints[i].theta1 = 0;
			}
			theta2 = Const_theta_start;
			beta1 = 0;
		}
				
			break;
	}
	glutPostRedisplay();
}