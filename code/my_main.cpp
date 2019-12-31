//#define _CRT_SECURE_NO_WARNINGS    
//
//#include"texture.h"
//#include "mesh.h"
//#include "cmath"
//
//const int windowWidth = 800;
//const int windowHeight = 600;
//
//const float pi = 3.14159;
//float camera_angle = 0.0;
//float camera_z = 0.0;
//float camera_x = 0.0;
//float camera_speed = 1.0;
//
//Mesh book;
//
//Mesh stoneman;
//
//GLuint texture[10];
//
//GLfloat light0_position3[] = { 0.0f,3.8f,0.0,1. };
//
//float angle = 0.0f;
//
//
//void specialKey(int key, int xx, int yy)
//{
//	float angle_C = (camera_angle - 90.) * pi / 180.; // 初始状态下，相机沿着z轴的负半轴行走
//	switch (key)
//	{
//	case GLUT_KEY_LEFT: // 左转角度-1°
//		camera_angle -= 1.0;
//		break;
//	case GLUT_KEY_RIGHT: // 右转角度+1°
//		camera_angle += 1.0;
//		break;
//	case GLUT_KEY_UP: // 根据左右转动后的角度，计算相机在固定坐标系中的位置
//		camera_x += camera_speed * cos(angle_C);
//		camera_z += camera_speed * sin(angle_C);
//		break;
//	case GLUT_KEY_DOWN:
//		camera_x -= camera_speed * cos(angle_C);
//		camera_z -= camera_speed * sin(angle_C);
//		break;
//	}
//}
//
//void myDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_NORMALIZE);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	float angle_C = (camera_angle + 90) * pi / 180.;
//	gluLookAt(camera_x, 3, camera_z + 8, camera_x - 10. * cos(angle_C), 0, camera_z - 10. * sin(angle_C), 0, 1, 0);
//
//	/*glRotated(angle, 0, 1, 0);
//	angle += 0.01f;*/
//	
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texture[8]);
//	//book.drawMesh();
//	glTranslated(-5, -5, 0);
//	glScaled(0.05, 0.05, 0.05);
//	stoneman.drawMesh();
//
//	glBegin(GL_POLYGON);
//	glTexCoord2f(0, 0);
//	glNormal3f(0,0,1);
//	glVertex3f(0,0,0);
//
//	glTexCoord2f(1, 0);
//	glNormal3f(0, 0, 1);
//	glVertex3f(1, 0, 0);
//
//	glTexCoord2f(1, 1);
//	glNormal3f(0, 0, 1);
//	glVertex3f(1, 2, 0);
//
//	glTexCoord2f(0, 1);
//	glNormal3f(0, 0, 1);
//	glVertex3f(0, 2, 0);
//
//	glEnd();
//	glDisable(GL_TEXTURE_2D);
//
//	glutSwapBuffers();
//	glutPostRedisplay();
//}
//
//void myInit()
//{
//	//光源
//	GLfloat light0_diffuse[] = { 0.9f,0.5f,0.7f,1. };
//	GLfloat light0_spec[] = { 0.9f,0.0f,0.0f,1. };
//
//	GLfloat light1_ambient[] = { 1.,0.8,0.8,1. };
//	GLfloat light1_position3[] = { -5.0,-12.0,6.0,1. };
//
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
//	glLightfv(GL_LIGHT0, GL_POSITION, light0_position3);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_ambient);
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
//	glLightfv(GL_LIGHT1, GL_POSITION, light1_position3);
//
//	//glEnable(GL_LIGHTING);
//	//glEnable(GL_LIGHT1);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, windowWidth / windowHeight, 1.0, 21.0);
//
//	//读取模型
//	glClearColor(0, 0, 0, 1);
//	glEnable(GL_NORMALIZE);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_TEXTURE_2D);
//	glShadeModel(GL_SMOOTH);
//	glColor4f(1.0, 1.0, 1.0, 1.0f);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//
//	//纹理
//	char filename[] = "book_word.jpg";
//	BuildTexture(filename, texture[0]);
//
//	book.readFile("book.obj");
//
//	stoneman.readFile("sword2.obj");
//	char filename5[] = "Sword_roughness.jpg";
//	BuildTexture(filename5, texture[8]);
//}spe
//
//
//int main()
//{
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
//	glutInitWindowPosition(50, 50);
//	glutInitWindowSize(windowWidth, windowHeight);
//	glutCreateWindow("客天涯的炸弹");
//
//	myInit();
//	glutDisplayFunc(myDisplay);
//	glutSpecialFunc(specialKey);
//
//	glutMainLoop();
//	return 0;
//}
