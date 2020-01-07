#define _CRT_SECURE_NO_WARNINGS
#define PI			3.14159f
#define D2rad(X)	PI*X/180.0f		//度°转为弧度rad
#define SIN(X)		sin(D2rad(X))	// 重新定义sin(X),单位为度，不是弧度
#define COS(X)		cos(D2rad(X))	// 重新定义cos(X),单位为度，不是弧度
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "Extensions/ARB_multitexture_extension.h"
#include "Extensions/ARB_texture_cube_map_extension.h"
#include "Extensions/ARB_texture_env_combine_extension.h"
#include "Extensions/ARB_texture_env_dot3_extension.h"
#include "Image/IMAGE.h"
#include "Maths/Maths.h"
#include "book.h"
#include "Normalisation Cube Map.h"
#include <stdlib.h>
#include <tchar.h>
#include"texture.h"
#include "cmath"
#include"butterfly.h"
#include <time.h>
#include "mesh.h"
#include "bomb.h"
#include "fuse.h"
#include "buddha.h"
#include "particle3d.h"
#include "jySkySphere.h"
#include "jySkyBox.h"


const int windowWidth = 800;
const int windowHeight = 600;

int mouseDownX;
int mouseDownY;
int skyboxSize = 20;
float y_point = skyboxSize / 2.0f;
float	    eye[3] = { 0, 0, 0 }; 	//视点:当相机位于天空盒子的几何中心上时，视觉效果最好！！！！
float	    AngleXZ = -90;	            //方位角：XZ平面内转动，绕Y轴转动，单位：度
float	    AngleYZ = 0;	            //仰俯角：YZ平面内转动，绕X轴转动，单位：度
float	    look[3] = { eye[0] + 100 * COS(AngleXZ),
						eye[1] + AngleYZ,
						eye[2] + 100 * SIN(AngleXZ) };	                        //目标点

GLuint texture[10];

float angle = 0.0f;

butterflyManager* butt;

float eyex, eyey, eyez, lookx, looky, lookz;

bool drawSkyBox = 1, drawBook = 1, drawButt = 0, drawRoom = 0, drawSward = 0, drawBomb = 0, drawBuddha = 0, buttToRoom = 0;

bool torch_on = 0; //手电筒

Mesh sward;
Bomb bomb;
Fuse fuse;
Buddha buddha1;
Buddha buddha2;
Buddha buddha3;
Buddha buddha4;

emitter* blocks;

CjySkyBox* mSkyBox;

float bombY = 3.0f, bombZ = 12.0f, spinX = 45;
float bombVy = 0.05f, bombAy = -0.001f, bombVz = -0.08f, spinVx = -1;

int flash_count = 0;
float full_light = 1.0f;

//书的光照变化
float light2_diffuse[] = { 5,5,5 };
float light2_specular[] = { 10,10,10 };
float light2_pos[] = { 0, 3, -2, 0.0f };

//book bump mapping
//Our book
Book bookCover;
Mesh book;

//Normal map
GLuint normalMap;

//Decal texture
GLuint decalTexture;

//Normalisation cube map
GLuint normalisationCubeMap;

VECTOR3D worldLightPosition = VECTOR3D(10.0f, 10.0f, 10.0f);

void displayBookCover()
{
	//Get the inverse model matrix
	MATRIX4X4 inverseModelMatrix;
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, inverseModelMatrix);
	glPopMatrix();

	//Get the object space light vector
	VECTOR3D objectLightPosition = inverseModelMatrix * worldLightPosition;

	//Loop through vertices
	for (int i = 0; i < bookCover.numVertices; ++i)
	{
		VECTOR3D lightVector = objectLightPosition - bookCover.vertices[i].position;

		//Calculate tangent space light vector
		bookCover.vertices[i].tangentSpaceLight.x =
			bookCover.vertices[i].sTangent.DotProduct(lightVector);
		bookCover.vertices[i].tangentSpaceLight.y =
			bookCover.vertices[i].tTangent.DotProduct(lightVector);
		bookCover.vertices[i].tangentSpaceLight.z =
			bookCover.vertices[i].normal.DotProduct(lightVector);
	}


	//Draw bump pass
	//Bind normal map to texture unit 0
	glBindTexture(GL_TEXTURE_2D, normalMap);
	glEnable(GL_TEXTURE_2D);

	//Bind normalisation cube map to texture unit 1
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, normalisationCubeMap);
	glEnable(GL_TEXTURE_CUBE_MAP_ARB);
	glActiveTextureARB(GL_TEXTURE0_ARB);

	//Set vertex arrays for book
	glVertexPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].position);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Send texture coords for normal map to unit 0
	glTexCoordPointer(2, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].s);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Send tangent space light vectors for normalisation to unit 1
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glTexCoordPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].tangentSpaceLight);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);


	//Set up texture environment to do (tex0 dot tex1)*color
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE);

	glActiveTextureARB(GL_TEXTURE1_ARB);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_DOT3_RGB_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);

	glActiveTextureARB(GL_TEXTURE0_ARB);



	//Draw book
	glDrawElements(GL_TRIANGLES, bookCover.numIndices, GL_UNSIGNED_INT, bookCover.indices);


	//Disable textures
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_CUBE_MAP_ARB);
	glActiveTextureARB(GL_TEXTURE0_ARB);

	//disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);

	//Return to standard modulate texenv
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//If we are drawing both passes, enable blending to multiply them together
	//Enable multiplicative blending
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glEnable(GL_BLEND);

	//Perform a second pass to color the book
	//Bind decal texture
	glBindTexture(GL_TEXTURE_2D, decalTexture);
	glEnable(GL_TEXTURE_2D);

	//Set vertex arrays for book
	glVertexPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].position);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].normal);
	glEnableClientState(GL_NORMAL_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].s);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Draw book
	glDrawElements(GL_TRIANGLES, bookCover.numIndices, GL_UNSIGNED_INT, bookCover.indices);

	//Disable texture
	glDisable(GL_TEXTURE_2D);

	//disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//Disable blending if it is enabled
	glBlendFunc(GL_ONE, GL_ONE);  //return to default
	glDisable(GL_BLEND);
	/*glFinish();
	glutSwapBuffers();*/
}
bool stop = 0;
bool fog = 0;
bool fogHold = 0;
int fogCounter = 0;
bool fogDismiss = 0;
float fcStart = 0.0f;
float fcEnd = 40.0f;
float fcSEChangeV = 0.01f;
float bookTranslateX = 0.67f;
float bookTranslateY = 1.0f;
float bookMove = 0.01f;
float bookCoverScaleX = 1.37f;
float bookCoverScaleY = 1.0f;
float bookCoverScale = 0.1f;
float bookRotate = -1;
float bookRotateV = 0.1f;
void myDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
	if (fog)
	{
		fcEnd -= fcSEChangeV;
		fcSEChangeV *= 0.9999f;
		glFogf(GL_FOG_END, fcEnd);
		if (fcEnd <= 7.0f)
		{
			fog = 0;
			fogHold = 1;
			drawBook = 0;
			cout << "fcSE: " << fcSEChangeV << endl;
		}
	}
	if (fogHold)
	{
		fogCounter++;
		if (fogCounter >= 2000)
		{
			fogHold = 0;
			fogDismiss = 1;
		}
	}

	if (fogDismiss)
	{
		fcEnd += fcSEChangeV;
		fcSEChangeV *= 0.9999f;
		glFogf(GL_FOG_END, fcEnd);
		if (fcEnd >= 20.0f)
		{
			fogDismiss = 0;
			drawButt = 1;
			cout << "fcSE: " << fcSEChangeV << endl;
			glDisable(GL_FOG);
		}
	}
	if (drawSkyBox)
	{
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(0.0, -y_point, -2);
		glRotated(120, 0, 1, 0);
		mSkyBox->ShowSky();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	if (drawBook)
	{
		glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
		glPushMatrix();
		glTranslated(-0.5f, -1, -8);
		//画书封面
		glPushMatrix();
		glScaled(bookCoverScaleX, bookCoverScaleY, 1);
		displayBookCover();
		glPopMatrix();
		//画书体
		glPushMatrix();
		glTranslatef(bookTranslateX, bookTranslateY, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(bookRotate, 1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		book.drawMesh();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPopMatrix();

		/*flash_count++;
		if (flash_count > 10000)
		{
			drawButt = 1;
		}*/
	}

	if (drawButt)
	{
		AngleXZ -= 0.005f;
		look[0] = eye[0] + 100 * COS(AngleXZ);
		look[2] = eye[2] + 100 * SIN(AngleXZ);
		glPushMatrix();
		glTranslated(-0.5f, -1, -8);
		glEnable(GL_BLEND);
		butt->show();
		glDisable(GL_BLEND);
		glPopMatrix();
		/*if (flash_count == 10005)
		{
			glEnable(GL_FOG);
		}*/
		//用环境光变暗来实现消失在迷雾中
		if (flash_count > 20000)
		{
			//由1变0
			full_light -= 0.0001f;
			GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
			// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			for (int i = 0; i < 3; i++)
			{
				light2_diffuse[i] -= 0.0005f;
				light2_specular[i] -= 0.001f;
			}
			glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
			glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
		}
		if (flash_count == 30000)
		{
			//glDisable(GL_LIGHT2);
			drawBook = 0;
			drawSkyBox = 0;
			drawButt = 0;
			AngleXZ = -90;
			look[0] = eye[0] + 100 * COS(AngleXZ);
			look[2] = eye[2] + 100 * SIN(AngleXZ);
			buttToRoom = 1;
			drawRoom = 1;
			drawSward = 1;
			flash_count = 0;
			//还应加入消失在迷雾中
		}
	}

	if (buttToRoom)
	{
		flash_count++;
		full_light += 0.00003f;
		GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
		// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		if (flash_count == 10000)
		{
			cout << full_light << endl;
			flash_count = 0;
			buttToRoom = 0;
		}
	}

	if (drawRoom)
	{
		glDisable(GL_LIGHT1);
		//glEnable(GL_LIGHT1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[9]);
		glPushMatrix();
		glTranslatef(0.0, -3, -10);
		//画左面
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glNormal3f(1, 0, 0);
		glVertex3f(-5, 0, 10);

		glTexCoord2f(0, 1);
		glNormal3f(1, 0, 0);
		glVertex3f(-5, 10, 10);

		glTexCoord2f(1, 1);
		glNormal3f(1, 0, 0);
		glVertex3f(-5, 10, -5);

		glTexCoord2f(1, 0);
		glNormal3f(1, 0, 0);
		glVertex3f(-5, 0, -5);

		//画右面
		glTexCoord2f(0, 0);
		glNormal3f(-1, 0, 0);
		glVertex3f(5, 0, 10);

		glTexCoord2f(0, 1);
		glNormal3f(-1, 0, 0);
		glVertex3f(5, 10, 10);

		glTexCoord2f(1, 1);
		glNormal3f(-1, 0, 0);
		glVertex3f(5, 10, -5);

		glTexCoord2f(1, 0);
		glNormal3f(-1, 0, 0);
		glVertex3f(5, 0, -5);

		//画前面
		glTexCoord2f(0, 0);
		glNormal3f(0, 0, 1);
		glVertex3f(-5, 0, -5);

		glTexCoord2f(0, 1);
		glNormal3f(0, 0, 1);
		glVertex3f(-5, 10, -5);

		glTexCoord2f(1, 1);
		glNormal3f(0, 0, 1);
		glVertex3f(5, 10, -5);

		glTexCoord2f(1, 0);
		glNormal3f(0, 0, 1);
		glVertex3f(5, 0, -5);

		//画地面
		glTexCoord2f(0, 0);
		glNormal3f(0, 1, 0);
		glVertex3f(-5, 0, 10);

		glTexCoord2f(0, 1);
		glNormal3f(0, 1, 0);
		glVertex3f(-5, 0, -5);

		glTexCoord2f(1, 1);
		glNormal3f(0, 1, 0);
		glVertex3f(5, 0, -5);

		glTexCoord2f(1, 0);
		glNormal3f(0, 1, 0);
		glVertex3f(5, 0, 10);

		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	if (torch_on)
	{
		float y = AngleYZ / 180.0f;
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
		GLfloat spot_pos[] = { eye[0] - COS(AngleXZ), -y, eye[2] - SIN(AngleXZ), 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
		GLfloat  spot_direction[] = { 100 * COS(AngleXZ),y - 3, 100 * SIN(AngleXZ) };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	if (drawSward && torch_on)
	{
		glPushMatrix();
		glTranslatef(0.0, -3, -10);
		glPushMatrix();
		glRotated(-45, 0, 1, 0);
		glScaled(0.01, 0.01, 0.01);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[8]);
		sward.drawMesh();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPopMatrix();
	}

	if (drawBomb)
	{
		glPushMatrix();
		glTranslatef(0.0, -3, -12);
		if (bombZ > 2)
		{
			glPushMatrix();
			//抛物线运动
			glTranslatef(0.0f, bombY, bombZ);
			glRotatef(spinX, 1, 0, 0);
			glScaled(0.2f, 0.2f, 0.2f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			bomb.drawMesh();
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			fuse.ignite();
			glPopMatrix();
			bombY += bombVy;
			bombVy += bombAy;
			bombZ += bombVz;
			spinX += spinVx;
			glDisable(GL_TEXTURE_2D);
		}
		else if (flash_count < 3000)
		{
			//爆炸出石块
			torch_on = 0;
			flash_count++;
			blocks->update();
			drawSward = 0;
		}
		else
		{
			flash_count = 0;
			drawBomb = 0;
			drawBuddha = 1;
		}
		glPopMatrix();
	}

	if (drawBuddha)
	{
		glPushMatrix();
		glTranslatef(0.0, -3, -10);
		glEnable(GL_LIGHT1);
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, 0.0f);
		glScalef(10.0f, 10.0f, 10.0f);
		glEnable(GL_TEXTURE_2D);
		//if (torch_on)
		//{
		//	flash_count++;
		//	cout << flash_count << endl;
		//	//材质逐渐变银最后变金色
		//	glBindTexture(GL_TEXTURE_2D, texture[1]);
		//	if (flash_count==100)
		//	{
		//		cout << "buddha load res3" << endl;
		//		buddha.reReadFile("obj\\happy_vrip_res3.obj");
		//		cout << "buddha finish res3" << endl;
		//	}
		//	else if(flash_count == 120)
		//	{
		//		cout << "buddha load res2" << endl;
		//		buddha.reReadFile("obj\\happy_vrip_res2.obj");
		//		cout << "buddha finish res2" << endl;
		//	}
		//	else if(flash_count == 140)
		//	{
		//		cout << "buddha load res1" << endl;
		//		buddha.reReadFile("obj\\happy_vrip.obj");
		//		cout << "buddha finish res1" << endl;
		//	}
		//}
		//else
		//{
		//	if (flash_count!=0)
		//	{
		//		flash_count = 0;
		//		cout << "buddha load res4" << endl;
		//		buddha.reReadFile("obj\\happy_vrip_res4.obj");
		//		cout << "buddha finish res4" << endl;
		//	}
		//	//绑定粗糙纹理,设置灰色石质
		//	glBindTexture(GL_TEXTURE_2D, texture[1]);
		//}
		//buddha.drawMesh();
		if (torch_on)
		{
			flash_count++;
			if (flash_count >= 100 && flash_count < 200)
			{
				buddha3.drawMesh();
			}
			if (flash_count >= 200 && flash_count < 240)
			{
				buddha2.drawMesh();
			}
			if (flash_count >= 240)
			{
				buddha1.drawMesh();
			}
		}
		else
		{
			flash_count = 0;
			buddha4.drawMesh();
		}
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	/*case ' ':
		torch_on = !torch_on;
		break;
	case 'b':
		drawBomb = 1;
		break;
	case 'g':
		drawBook = 1;
		break;
	case 's':
		drawSkyBox = !drawSkyBox;
		break;
	case 'p':
		stop = !stop;
		break;
	case 'f':
		fog = !fog;
		if (fog)
		{
			glEnable(GL_FOG);
		}
		else
		{
			glDisable(GL_FOG);
		}
		break;*/
	case 'a': // 左100
		bookTranslateX -= bookMove;
		cout << bookTranslateX << ", " << bookTranslateY << endl;
		break;
	case 'd':// 右102
		bookTranslateX += bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
		break;
	case 'w':// 上101
		bookTranslateY += bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
		break;
	case 's':// 下103
		bookTranslateY -= bookMove; cout << bookTranslateX << ", " << bookTranslateY << endl;
		break;
	case 'q':// 上101
		bookRotate += bookRotateV; cout << bookRotate << endl;
		break;
	case 'e':// 下103
		bookRotate -= bookRotateV; cout << bookRotate << endl;
		break;
	case '1':
		fcStart -= fcSEChangeV;
		cout << fcStart << "  " << fcEnd << endl;
		glFogf(GL_FOG_START, fcStart);
		glFogf(GL_FOG_END, fcEnd);
		break;
	case '2':
		fcStart += fcSEChangeV;
		cout << fcStart << "  " << fcEnd << endl;
		glFogf(GL_FOG_START, fcStart);
		glFogf(GL_FOG_END, fcEnd);
		break;
	case '3':
		fcEnd -= fcSEChangeV;
		cout << fcStart << "  " << fcEnd << endl;
		glFogf(GL_FOG_START, fcStart);
		glFogf(GL_FOG_END, fcEnd);
		break;
	case '4':
		fcEnd += fcSEChangeV;
		glFogf(GL_FOG_START, fcStart);
		glFogf(GL_FOG_END, fcEnd);
		cout << fcStart << "  " << fcEnd << endl;
		break;
	case '5':
		fcSEChangeV *= 2;
		cout << fcSEChangeV<< endl;
		break;
	case '6':
		fcSEChangeV /= 2;
		cout << fcSEChangeV<< endl;
		break;
	case '7':
		bookMove += 0.1f;
		cout << bookMove << endl;
		break;
	case '8':
		bookMove -= 0.1f;
		cout << bookMove << endl;
		break;
	case '9':
		bookCoverScale *= 10;
		cout << bookCoverScale << endl;
		break;
	case '0':
		bookCoverScale *= 0.1f;
		cout << bookCoverScale << endl;
		break;
	case '-':
		bookRotateV *= 0.1f;
		cout << bookRotateV << endl;
		break;
	case '=':
		bookRotateV *= 10.0f;
		cout << bookRotateV << endl;
		break;
	case 'j': // 左100
		bookCoverScaleX -= bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
		break;
	case 'l':// 右102
		bookCoverScaleX += bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
		break;
	case 'i':// 上101
		bookCoverScaleY += bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
		break;
	case 'k':// 下103
		bookCoverScaleY -= bookCoverScale; cout << bookCoverScaleX << ", " << bookCoverScaleY << endl;
		break;
	default:
		break;
	}
}

void specialKey(int key, int xx, int yy)
{
	float speed = 1.0f;
	// cout << key;
	switch (key)
	{
	case GLUT_KEY_LEFT: // 左100
		AngleXZ -= speed;
		break;
	case GLUT_KEY_RIGHT:// 右102
		AngleXZ += speed;
		break;
	case GLUT_KEY_UP:// 上101
		eye[2] += SIN(AngleXZ) * speed;
		eye[0] += COS(AngleXZ) * speed;
		break;
	case GLUT_KEY_DOWN:// 下103
		eye[2] -= SIN(AngleXZ) * speed;
		eye[0] -= COS(AngleXZ) * speed;
		break;
	case GLUT_KEY_PAGE_UP:// PageUp104
		AngleYZ += speed;
		AngleYZ = AngleYZ < -360 ? -360 : AngleYZ;
		AngleYZ = AngleYZ > 360 ? 360 : AngleYZ;
		break;
	case GLUT_KEY_PAGE_DOWN:// PageDown105
		AngleYZ -= speed;
		AngleYZ = AngleYZ < -360 ? -360 : AngleYZ;
		AngleYZ = AngleYZ > 360 ? 360 : AngleYZ;
		break;
	}
	//摄像机的方向
	look[0] = eye[0] + 100 * COS(AngleXZ);
	look[2] = eye[2] + 100 * SIN(AngleXZ);
	look[1] = eye[1] + AngleYZ;
	glutPostRedisplay();
}

void onMouseMoveButtonDown(int x, int y)
{
	AngleXZ += (x - mouseDownX) / 5.0f;
	AngleYZ -= (y - mouseDownY) / 5.0f;

	//摄像机的方向
	look[0] = (float)(eye[0] + 100 * COS(AngleXZ));
	look[2] = (float)(eye[2] + 100 * SIN(AngleXZ));
	look[1] = eye[1] + AngleYZ;

	glutPostRedisplay();

	mouseDownX = x;
	mouseDownY = y;
}


void onMouseDown(int button, int state, int x, int y)
{
	mouseDownX = x;
	mouseDownY = y;
}

particle3d* init_block(float x, float y, float z)
{
	float size = rand() % 10;
	float color[] = { 226 / 255.0f, 17 / 255.0f, 12 / 255.0f };
	particle3d* p = new particle3d(size, x, y, z,
		(rand() % 10 - 5) / 100.0, (rand() % 10 - 5) / 100.0, (rand() % 10 - 5) / 100.0,
		(rand() % 10 - 5) / 1000.0, (rand() % 10 - 5) / 1000.0, (rand() % 10 - 5) / 1000.0,
		rand() % 50, color);
	return p;
}

void initBook(void)
{
	//Check for and set up extensions
	if (!SetUpARB_multitexture() || !SetUpARB_texture_cube_map() ||
		!SetUpARB_texture_env_combine() || !SetUpARB_texture_env_dot3())
	{
		printf("Required Extension Unsupported\n");
		exit(0);
	}

	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	//Load normal map
	IMAGE normalMapImage;
	//normalMapImage.Load("Normal map.bmp");
	normalMapImage.Load((char * )("tex\\book_word.bmp"));
	normalMapImage.ExpandPalette();

	//Convert normal map to texture
	glGenTextures(1, &normalMap);
	glBindTexture(GL_TEXTURE_2D, normalMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, normalMapImage.width, normalMapImage.height,
		0, normalMapImage.format, GL_UNSIGNED_BYTE, normalMapImage.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Load decal image
	IMAGE decalImage;
	//decalImage.Load("Decal.bmp");
	decalImage.Load((char*)("tex\\string.bmp"));
	decalImage.ExpandPalette();

	//Convert decal image to texture
	glGenTextures(1, &decalTexture);
	glBindTexture(GL_TEXTURE_2D, decalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, decalImage.width, decalImage.height,
		0, decalImage.format, GL_UNSIGNED_BYTE, decalImage.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//Create normalisation cube map
	glGenTextures(1, &normalisationCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, normalisationCubeMap);
	GenerateNormalisationCubeMap();
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void myInit()
{
	initBook();
	//glClearColor(1.0, 0.0, 0.0, 0.0);
	eyex = 0.0, eyey = 0.0, eyez = 20.0f;
	lookx = 0.0, looky = 0.0, lookz = 0.0;

	srand(unsigned(time(nullptr)));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, windowWidth / windowHeight, 1.0, 21.0);
	gluPerspective(60.0, windowWidth / windowHeight, 1.0, 30.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//float pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	//float white[] = { 255,255,255 };
	//float dimwhite[] = { 0.2 * 255,0.2 * 255,0.2 * 255 };
	////Set up light
	//glLightfv(GL_LIGHT1, GL_POSITION, pos);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, dimwhite);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	//glEnable(GL_LIGHT1);

	//手电筒的光
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
	GLfloat spot_pos[] = { 0, -1, 2, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
	GLfloat  spot_direction[] = { 0, 0.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

	//照着buddha的光
	float light1_pos[] = { 0, 3, 2, 0.0f };
	float light1_diffuse[] = { 5,5,5 };
	float light1_specular[] = { 10,10,10 };
	float dimwhite[] = { 2,2,2 };
	//Set up light
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, dimwhite);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);

	glEnable(GL_LIGHTING);
	// 指定全局环境光的RGBA强度值,照亮书和蝴蝶，后面可以换成光源，让字体发光
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	//Set up light
	glEnable(GL_LIGHT2);

	//迷雾
	// 启用雾化功能-----------------
	//glEnable(GL_FOG);
	//GLfloat fogColor[] = { fc, fc, fc, 0.0 };
	GLfloat fogColor[] = { 1, 1, 1, 0.0 };
	//glFogi(GL_FOG_MODE, GL_EXP2  /*GL_EXP	GL_EXP2	GL_LINEAR*/);
	glFogi(GL_FOG_MODE, GL_LINEAR  /*GL_EXP	GL_EXP2	GL_LINEAR*/);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.15f);
	glFogf(GL_FOG_START, fcStart);
	glFogf(GL_FOG_END, fcEnd);
	glHint(GL_FOG_HINT, GL_NICEST);

	//纹理
	TCHAR filename[] = L"tex\\book_word.jpg";
	BuildTexture(filename, texture[0]);
	TCHAR filename2[] = L"tex\\Butterfly1.bmp";
	BuildTexture(filename2, texture[5]);
	TCHAR filename3[] = L"tex\\Butterfly2.bmp";
	BuildTexture(filename3, texture[6]);
	TCHAR filename4[] = L"tex\\Butterfly3.bmp";
	BuildTexture(filename4, texture[7]);
	int* tex = new int[3];
	tex[0] = texture[5];
	tex[1] = texture[6];
	tex[2] = texture[7];
	butt = new butterflyManager(tex);
	butt->isDraw = true;
	delete tex;

	cout << "ok0" << endl;
	TCHAR filename5[] = L"tex\\Sword_roughness.jpg";  //这里应该用好的mapping
	BuildTexture(filename5, texture[8]);
	cout << "ok" << endl;
	sward.readFile("obj\\sword2.obj");

	TCHAR filename6[] = L"tex\\th.jpg";  //这里应该用好的mapping
	BuildTexture(filename6, texture[9]);

	//炸弹
	TCHAR filename7[] = L"tex\\bomb5.jpg";
	BuildTexture(filename7, texture[1]);
	TCHAR filename8[] = L"tex\\string.jpg";
	BuildTexture(filename8, texture[2]);
	TCHAR filename9[] = L"tex\\spark.bmp";
	BuildTexture(filename9, texture[3]);

	bomb.readFile("obj\\new_bomb.obj");
	fuse.readFile("obj\\new_fuse.obj");
	book.readFile("obj\\book.obj");

	blocks = new emitter(200, 0.0f, 2.0f, 2.0f);
	blocks->emit(init_block);

	//buddha4.readFile("obj\\happy_vrip_res4.obj");
	//cout << "load buddha4 finish" << endl;
	/*buddha3.readFile("obj\\happy_vrip_res3.obj");
	cout << "load buddha3 finish" << endl;
	buddha2.readFile("obj\\happy_vrip_res2.obj");
	cout << "load buddha2 finish" << endl;
	buddha1.readFile("obj\\happy_vrip.obj");
	cout << "load buddha1 finish" << endl;*/

	//天空盒子
	CString TexPath(".\\skybox\\mp_cloud9\\cloud9_"); // 云 台  这个好
	mSkyBox = new CjySkyBox(skyboxSize, TexPath + "bk.tga", TexPath + "ft.tga", TexPath +
		"rt.tga", TexPath + "lf.tga", TexPath + "up.tga", TexPath + "dn.tga");
}


int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("客天涯的盗墓笔记");

	myInit();
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(Key);
	glutMouseFunc(onMouseDown);
	glutMotionFunc(onMouseMoveButtonDown);
	glutMainLoop();
	return 0;
}
