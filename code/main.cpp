//#include <GL/glut.h>
//#include <iostream>
//#include <iomanip>
//#include <algorithm>
//#include <cmath>
//#include "MyMath.h"
//
//using namespace std;
//
//const int XINIT = 800, YINIT = 800;
//
//const int XMAX = 1600, YMAX = 800;
//
//float height[XMAX + 1][YMAX + 1];
//
//int XCURR = XINIT, YCURR = YINIT;
//
//const int MY_POLYGON = 0, MY_SPHERE = 1;
//
//const int MY_MODE = MY_SPHERE;
//
//Vector3f position[XMAX + 1][YMAX + 1], normal[XMAX + 1][YMAX + 1];
//
//void InitNormal() {
//	for (int i = 0; i <= XMAX; i++)
//		for (int j = 0; j <= YMAX; j++) {
//			if (MY_MODE == MY_POLYGON) {
//				normal[i][j].x = 0.0;
//				normal[i][j].y = 0.0;
//				normal[i][j].z = 1.0;
//			}
//			if (MY_MODE == MY_SPHERE) {
//				normal[i][j] = position[i][j];
//			}
//			if (i != XMAX)
//				normal[i][j] = normal[i][j] - (position[i][j] - position[i + 1][j]).Unitization() * (height[i][j] - height[i + 1][j]);
//			if (i != 0)
//				normal[i][j] = normal[i][j] - (position[i][j] - position[i - 1][j]).Unitization() * (height[i][j] - height[i - 1][j]);
//			if (j != YMAX)
//				normal[i][j] = normal[i][j] - (position[i][j] - position[i][j + 1]).Unitization() * (height[i][j] - height[i][j + 1]);
//			if (j != 0)
//				normal[i][j] = normal[i][j] - (position[i][j] - position[i][j - 1]).Unitization() * (height[i][j] - height[i][j - 1]);
//			normal[i][j].Unitization();
//		}
//}
//void RenderScene() {
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glPointSize(10.0f);
//	glLineWidth(1.0f);
//	glPushMatrix();
//	{
//		GLfloat sunLightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//		GLfloat sunLightAmbient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
//		GLfloat sunLightDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
//		GLfloat sunLightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		glLightfv(GL_LIGHT0, GL_POSITION, sunLightPosition);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, sunLightAmbient);
//
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, sunLightDiffuse);
//		glLightfv(GL_LIGHT0, GL_SPECULAR, sunLightSpecular);
//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHTING);
//	}
//	/*
//		static float rotateTheta = 0.0;
//		glRotated(-23.5, 0.0, 0.0, 1.0);
//		glRotated(rotateTheta, 0.0, 1.0, 0.0);
//		rotateTheta += 1;
//	*/
//	{
//		GLfloat triangleMatAmbient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
//		GLfloat triangleMatDiffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
//		GLfloat triangleMatSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		GLfloat triangleMatEmission[] = { 0.1f, 0.1f, 0.3f, 1.0f };
//		GLfloat triangleMatShininess = 100.0f;
//		glMaterialfv(GL_FRONT, GL_AMBIENT, triangleMatAmbient);
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, triangleMatDiffuse);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, triangleMatSpecular);
//		glMaterialfv(GL_FRONT, GL_EMISSION, triangleMatEmission);
//		glMaterialf(GL_FRONT, GL_SHININESS, triangleMatShininess);
//	}
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glBegin(GL_TRIANGLES);
//	{
//		for (int i = 0; i < XMAX; i++)
//			for (int j = 0; j < YMAX; j++) {
//				glNormal3fv(normal[i][j]());
//				glVertex3fv(position[i][j]());
//				glNormal3fv(normal[i + 1][j]());
//				glVertex3fv(position[i + 1][j]());
//				glNormal3fv(normal[i][j + 1]());
//				glVertex3fv(position[i][j + 1]());
//			}
//		for (int i = 0; i < XMAX; i++)
//			for (int j = 0; j < YMAX; j++) {
//				glNormal3fv(normal[i + 1][j]());
//				glVertex3fv(position[i + 1][j]());
//				glNormal3fv(normal[i + 1][j + 1]());
//				glVertex3fv(position[i + 1][j + 1]());
//				glNormal3fv(normal[i + 1][j + 1]());
//				glVertex3fv(position[i][j + 1]());
//			}
//	}
//	glEnd();
//	glPopMatrix();
//	glutSwapBuffers();
//}
//void ReshapeWindow(int w, int h) {
//	glViewport(0, 0, w, h);
//	XCURR = w;
//	YCURR = h;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(2 * atan(h / (YINIT * 5.0)) / PI * 180, 1.0 * w / h, 0.5, 18);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0);
//}
//void MouseMotion(int x, int y) {
//	float xFloat = (x - XCURR * 0.5f) / (YINIT * 0.5);
//	float yFloat = (YCURR * 0.5f - y) / (YINIT * 0.5);
//	if (xFloat < -1.0 || xFloat > 1.0 || yFloat < -1.0 || yFloat > 1.0)
//		return;
//
//	int xInt = floor((xFloat + 1.0) * 0.5 * XMAX);
//	int yInt = floor((yFloat + 1.0) * 0.5 * YMAX);
//
//	height[xInt + 0][yInt + 0] = -3;
//	height[xInt + 1][yInt + 0] = -3;
//	height[xInt + 0][yInt + 1] = -3;
//	height[xInt + 1][yInt + 1] = -3;
//}
//
//void MyInit() {
//	for (int i = 0; i <= XMAX; i++)
//		for (int j = 0; j <= YMAX; j++) {
//			{
//				if (i % 80 >= 20 && i % 80 < 60 && j % 80 >= 20 && j % 80 < 60)
//					height[i][j] = 2.0;
//				else
//					height[i][j] = 0.0;
//			}
//			if (MY_MODE == MY_POLYGON) {
//				position[i][j].x = i * 2.0 / XMAX - 1.0;
//				position[i][j].y = j * 2.0 / YMAX - 1.0;
//				position[i][j].z = 0.0;
//			}
//			if (MY_MODE == MY_SPHERE) {
//				float theta = i * 2.0 * PI / XMAX, fai = j * PI / YMAX;
//				position[i][j].x = 1.0 * sin(fai) * sin(theta);
//				position[i][j].y = 1.0 * cos(fai);
//				position[i][j].z = 1.0 * sin(fai) * cos(theta);
//			}
//		}
//
//	InitNormal();
//}
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowPosition(800, 40);
//	glutInitWindowSize(XINIT, YINIT);
//	glutCreateWindow("OpenGL");
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_DEPTH_TEST);
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ReshapeWindow);
//	//	glutIdleFunc(RenderScene);
//	//	glutMotionFunc(MouseMotion);
//	MyInit();
//	glutMainLoop();
//}
