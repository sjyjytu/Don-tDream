//#define _CRT_SECURE_NO_WARNINGS
//#define PI			3.14159f
//#define D2rad(X)	PI*X/180.0f		//度°转为弧度rad
//#define SIN(X)		sin(D2rad(X))	// 重新定义sin(X),单位为度，不是弧度
//#define COS(X)		cos(D2rad(X))	// 重新定义cos(X),单位为度，不是弧度
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <stdio.h>
//#include <GL/glut.h>
//#include <GL/glext.h>
//#include "Extensions/ARB_multitexture_extension.h"
//#include "Extensions/ARB_texture_cube_map_extension.h"
//#include "Extensions/ARB_texture_env_combine_extension.h"
//#include "Extensions/ARB_texture_env_dot3_extension.h"
//#include "Image/IMAGE.h"
//#include "Maths/Maths.h"
//#include "book.h"
//#include "Normalisation Cube Map.h"
//#include <stdlib.h>
//#include <tchar.h>
//#include"texture.h"
//#include "cmath"
//#include"butterfly.h"
//#include <time.h>
//#include "mesh.h"
//#include "bomb.h"
//#include "fuse.h"
//#include "buddha.h"
//#include "particle3d.h"
//#include "jySkySphere.h"
//#include "jySkyBox.h"
//
//
//const int windowWidth = 800;
//const int windowHeight = 600;
//
//int mouseDownX;
//int mouseDownY;
//int skyboxSize = 20;
//float y_point = skyboxSize / 2.0f;
//float	    eye[3] = { 0, 0, 0 }; 	//视点:当相机位于天空盒子的几何中心上时，视觉效果最好！！！！
//float	    AngleXZ = -90;	            //方位角：XZ平面内转动，绕Y轴转动，单位：度
//float	    AngleYZ = 0;	            //仰俯角：YZ平面内转动，绕X轴转动，单位：度
//float	    look[3] = { eye[0] + 100 * COS(AngleXZ),
//						eye[1] + AngleYZ,
//						eye[2] + 100 * SIN(AngleXZ) };	                        //目标点
//
//GLuint texture[20];
//
//float angle = 0.0f;
//
//butterflyManager* butt;
//
//float speed = 1.0f;
//float eyex, eyey, eyez, lookx, looky, lookz;
//
//bool drawSkyBox = 0, drawBook = 0, drawButt = 0, drawRoom = 1, drawSward = 1, drawBomb = 0, drawBuddha = 0, buttToRoom = 0;
//
//bool torch_on = 0; //手电筒
//
//Mesh sward;
//Bomb bomb;
//Fuse fuse;
//Buddha buddha1;
//Buddha buddha2;
//Buddha buddha3;
//Buddha buddha4;
//
//emitter* blocks;
//
//CjySkyBox* mSkyBox;
//
//float bombY = 3.0f, bombZ = 12.0f, spinX = 45;
//float bombVy = 0.05f, bombAy = -0.001f, bombVz = -0.08f, spinVx = -1;
//
//int flash_count = 0;
//int butt_count = 0;
//float full_light = 1.0f;
//
////手电筒
//GLfloat spot_pos[] = { 0, 0, 0, 1.0f };
//GLfloat  spot_direction[] = { 0.0f, 0.0f, -1.0f };
//
////book bump mapping
////Our book
//Book bookCover;
//Mesh book;
//
////Normal map
//GLuint normalMap;
//
////Decal texture
//GLuint decalTexture;
//
////Normalisation cube map
//GLuint normalisationCubeMap;
//
////VECTOR3D worldLightPosition = VECTOR3D(10.0f, 10.0f, 10.0f);
//
//bool stop = 0;
//bool fog = 0;
//bool fogHold = 0;
//int fogCounter = 0;
//bool fogDismiss = 0;
////辛苦调的一些参数
//float fcStart = 0.0f;
//float fcEnd = 40.0f;
//float fcSEChangeV = 0.03f;
//float bookTranslateX = 0.67f;
//float bookTranslateY = 1.0f;
//float bookMove = 0.01f;
//float bookCoverScaleX = 1.37f;
//float bookCoverScaleY = 1.0f;
//float bookCoverScale = 0.1f;
//float bookRotate = -1;
//float bookRotateV = 0.1f;
//
////书飞入场景
//spline* bookPath;
//
//float bookAngle = 0.0f;
//float bookOmega = 1.0f;
//int bookPos = 0;
//int bookPosCounter = 0;
//int bookPathSize;
//const int posPerAngle = 2;
//
//
//void myDisplay()
//{
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
//	glLightfv(GL_LIGHT5, GL_POSITION, spot_pos);
//	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction);
//	
//	if (drawRoom)
//	{
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[9]);
//		glPushMatrix();
//		glTranslatef(0.0, -3, -10);
//		float high = 12;
//		//画左面
//		glBegin(GL_QUADS);
//		glTexCoord2f(0, 0);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, 0, 10);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, high, 10);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, high, -5);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, 0, -5);
//
//		//画右面
//		glTexCoord2f(0, 0);
//		glNormal3f(-1, 0, 0);
//		glVertex3f(5, 0, 10);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(-1, 0, 0);
//		glVertex3f(5, high, 10);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(-1, 0, 0);
//		glVertex3f(5, high, -5);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(-1, 0, 0);
//		glVertex3f(5, 0, -5);
//
//		//画前面
//		glTexCoord2f(0, 0);
//		glNormal3f(0, 0, 1);
//		glVertex3f(-5, 0, -5);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(0, 0, 1);
//		glVertex3f(-5, high, -5);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(0, 0, 1);
//		glVertex3f(5, high, -5);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(0, 0, 1);
//		glVertex3f(5, 0, -5);
//
//		//画地面
//		glTexCoord2f(0, 0);
//		glNormal3f(0, 1, 0);
//		glVertex3f(-5, 0, 10);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(0, 1, 0);
//		glVertex3f(-5, 0, -5);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(0, 1, 0);
//		glVertex3f(5, 0, -5);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(0, 1, 0);
//		glVertex3f(5, 0, 10);
//
//		glEnd();
//		glPopMatrix();
//		glDisable(GL_TEXTURE_2D);
//	}
//
//	if (drawSward && torch_on)
//	{
//		glPushMatrix();  //1
//		glTranslatef(0.0, -3, -10);
//		glPushMatrix();  //2
//		//glRotated(-45, 0, 1, 0);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[8]);
//		sward.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //2
//		glPopMatrix();  //1
//	}
//
//	glutSwapBuffers();
//	glutPostRedisplay();
//}
//
//void Key(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case ' ':
//		torch_on = !torch_on;
//		if (torch_on)
//		{
//			glEnable(GL_LIGHT5);
//		}
//		else
//		{
//			glDisable(GL_LIGHT5);
//		}
//		break;
//		//case 'b':
//		//	drawBomb = 1;
//		//	break;
//		//case 'g':
//		//	drawBook = 1;
//		//	drawSkyBox = 1;
//		//	break;
//		//case 's':
//		//	drawSkyBox = !drawSkyBox;
//		//	break;
//		//case 'p':
//		//	stop = !stop;
//		//	break;
//		//case 'f':
//		//	fog = !fog;
//		//	if (fog)
//		//	{
//		//		glEnable(GL_FOG);
//		//	}
//		//	else
//		//	{
//		//		glDisable(GL_FOG);
//		//	}
//		//	break;
//	case 'a': // 移动light2
//		spot_pos[0] -= 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//	case 'd':// 右102
//		spot_pos[0] += 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//	case 'w':// 上101
//		spot_pos[1] -= 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//	case 's':// 下103
//		spot_pos[1] += 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//	case 'q':// 上101
//		spot_pos[2] -= 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//	case 'e':// 下103
//		spot_pos[2] += 0.5f;
//		cout << "pos: " << spot_pos[0] << ", " << spot_pos[1] << ", " << spot_pos[2] << ", " << endl;
//		break;
//
//	case 'j': // 移动light2
//		spot_direction[0] -= 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	case 'l':// 右102
//		spot_direction[0] += 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	case 'i':// 上101
//		spot_direction[1] -= 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	case 'k':// 下103
//		spot_direction[1] += 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	case 'u':// 上101
//		spot_direction[2] -= 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	case 'o':// 下103
//		spot_direction[2] += 0.5f;
//		cout << "direction: " << spot_direction[0] << ", " << spot_direction[1] << ", " << spot_direction[2] << ", " << endl;
//		break;
//	default:
//		break;
//	}
//}
//
//void specialKey(int key, int xx, int yy)
//{
//	// cout << key;
//	switch (key)
//	{
//	case GLUT_KEY_LEFT: // 左100
//		AngleXZ -= speed;
//		break;
//	case GLUT_KEY_RIGHT:// 右102
//		AngleXZ += speed;
//		break;
//	case GLUT_KEY_UP:// 上101
//		eye[2] += SIN(AngleXZ) * speed;
//		eye[0] += COS(AngleXZ) * speed;
//		break;
//	case GLUT_KEY_DOWN:// 下103
//		eye[2] -= SIN(AngleXZ) * speed;
//		eye[0] -= COS(AngleXZ) * speed;
//		break;
//	case GLUT_KEY_PAGE_UP:// PageUp104
//		AngleYZ += speed;
//		AngleYZ = AngleYZ < -360 ? -360 : AngleYZ;
//		AngleYZ = AngleYZ > 360 ? 360 : AngleYZ;
//		break;
//	case GLUT_KEY_PAGE_DOWN:// PageDown105
//		AngleYZ -= speed;
//		AngleYZ = AngleYZ < -360 ? -360 : AngleYZ;
//		AngleYZ = AngleYZ > 360 ? 360 : AngleYZ;
//		break;
//	}
//	//摄像机的方向
//	look[0] = eye[0] + 100 * COS(AngleXZ);
//	look[2] = eye[2] + 100 * SIN(AngleXZ);
//	look[1] = eye[1] + AngleYZ;
//	glutPostRedisplay();
//}
//
//void onMouseMoveButtonDown(int x, int y)
//{
//	AngleXZ += (x - mouseDownX) / 5.0f;
//	AngleYZ -= (y - mouseDownY) / 5.0f;
//
//	//摄像机的方向
//	look[0] = (float)(eye[0] + 100 * COS(AngleXZ));
//	look[2] = (float)(eye[2] + 100 * SIN(AngleXZ));
//	look[1] = eye[1] + AngleYZ;
//
//	glutPostRedisplay();
//
//	mouseDownX = x;
//	mouseDownY = y;
//}
//
//
//void onMouseDown(int button, int state, int x, int y)
//{
//	mouseDownX = x;
//	mouseDownY = y;
//}
//
//
//void myInit()
//{
//	srand(unsigned(time(nullptr)));
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, windowWidth / windowHeight, 1.0, 30.0);
//
//	glEnable(GL_DEPTH_TEST);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//	
//	//手电筒的光
//	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 10);
//	//GLfloat spot_pos[] = { 0, -1, 2, 0.0f };
//	
//
//	float light0_diffuse[] = { .5,.5,.5,1.0 };
//	float light0_specular[] = { 1,1,1,1.0 };
//	glLightfv(GL_LIGHT5, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT5, GL_SPECULAR, light0_specular);
//	
//	//双面光照
//	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//	glEnable(GL_LIGHTING);
//	// 指定全局环境光的RGBA强度值,照亮书和蝴蝶，后面可以换成光源，让字体发光
//	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//	//Set up light
//
//	//纹理
//	TCHAR filename[] = L"tex\\book_word.jpg";
//	BuildTexture(filename, texture[0]);
//	TCHAR filename2[] = L"tex\\Butterfly1.bmp";
//	BuildTexture(filename2, texture[5]);
//	TCHAR filename3[] = L"tex\\Butterfly2.bmp";
//	BuildTexture(filename3, texture[6]);
//	TCHAR filename4[] = L"tex\\Butterfly3.bmp";
//	BuildTexture(filename4, texture[7]);
//	
//	cout << "ok0" << endl;
//	TCHAR filename5[] = L"tex\\Sword_roughness.jpg";  //这里应该用好的mapping
//	BuildTexture(filename5, texture[8]);
//	cout << "ok" << endl;
//	sward.readFile("obj\\sword2.obj");
//
//	TCHAR filename6[] = L"tex\\th.jpg";  //这里应该用好的mapping
//	BuildTexture(filename6, texture[9]);
//}
//
//
//int main()
//{
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
//	glutInitWindowPosition(50, 50);
//	glutInitWindowSize(windowWidth, windowHeight);
//	glutCreateWindow("客天涯的盗墓笔记");
//
//	myInit();
//	glutDisplayFunc(myDisplay);
//	glutSpecialFunc(specialKey);
//	glutKeyboardFunc(Key);
//	glutMouseFunc(onMouseDown);
//	glutMotionFunc(onMouseMoveButtonDown);
//	glutMainLoop();
//	return 0;
//}
