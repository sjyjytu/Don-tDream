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
//#include "buddhaColor.h"
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
//bool drawSkyBox = 0, drawBook = 0, drawButt = 0, drawRoom = 1, drawStones = 1, drawSward = 0, drawBomb = 0, drawBuddha = 0, buttToRoom = 0;
//bool earthquake = 0;
//float alpha = 0.1f;  //地震系数
//float beta = 0.06f;  //地震系数
//bool torch_on = 0; //手电筒
//
//Mesh sward;
//Mesh stone;
//Mesh block_unit;
//Mesh wall;
//Bomb bomb;
//Fuse fuse;
//Buddha buddha1;
//Buddha buddha2;
//Buddha buddha3;
//Buddha buddha4;
//
////buddha参数
//float mat_color[] = { 0, 1, 0, 1.0f };
//float mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//float mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//float mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//int buddhaColorIndex = 0;
//
////六脉神剑
//int swardNum = 6;
//float swardR = 2;
//float swardAngle = 360.0 / swardNum;
//float swardSpin = 0.0f;
//float swardTheta = 3.0f;
//
//emitter* blocks;
//
//CjySkyBox* mSkyBox;
//
//float bombY = 3.0f, bombZ = 12.0f, spinX = 45;
//float bombVy = 0.05f, bombAy = -0.0015f, bombVz = -0.12f, spinVx = -1;
//
//int flash_count = 0;
//int bomb_count = 0;
//int butt_count = 0;
//float full_light = 1.0f;
//
////书的光照变化
//float light2_diffuse[] = { 5,5,5 };
//float light2_specular[] = { 10,10,10 };
////float light2_pos[] = { 10, 10, -10, 1.0f };
//float light2_pos[] = { -10, 0, 20, 1 };
//float flash_V = -0.4f;
//bool drawLightning = 0;
//bool recoverLight2 = 0;
//
////手电筒
//GLfloat spot_pos[] = { 1, 0.5, 0, 1.0f };
//GLfloat  spot_direction[] = { 0, -0.5, -1.0 };
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
//VECTOR3D worldLightPosition = VECTOR3D(light2_pos[0], light2_pos[1], light2_pos[2]);
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
//void genBookPath()
//{
//	point* p = new point[20];
//	float tx = 6;
//	float ty = 10;
//	p[0].setPoint(-0.8 * tx, -0.565 * ty);
//	p[1].setPoint(-0.585 * tx, -0.15 * ty);
//	p[2].setPoint(-0.37 * tx, 0.095 * ty);
//	p[3].setPoint(-0.155 * tx, 0.205 * ty);
//	p[4].setPoint(0.14 * tx, 0.28 * ty);
//	p[5].setPoint(0.51 * tx, 0.29 * ty);
//	p[6].setPoint(0.675 * tx, 0.175 * ty);
//	p[7].setPoint(0.78 * tx, -0.07 * ty);
//	p[8].setPoint(0.625 * tx, -0.35 * ty);
//	p[9].setPoint(0.24 * tx, -0.35 * ty);
//	p[10].setPoint(-0.005 * tx, -0.265 * ty);
//	p[11].setPoint(-0.08 * tx, -0.035 * ty);
//	p[12].setPoint(0.13 * tx, 0.115 * ty);
//	p[13].setPoint(0.295 * tx, 0.06 * ty);
//	p[14].setPoint(0.32 * tx, -0.09 * ty);
//	p[15].setPoint(0.20 * tx, -0.03 * ty);
//	p[16].setPoint(0.10 * tx, 0.02 * ty);
//	p[17].setPoint(0.0 * tx, 0.0 * ty);
//	bookPath = new spline(p, 18, 18, 0.6);
//}
//
//void displayBookCover()
//{
//	//Get the inverse model matrix
//	MATRIX4X4 inverseModelMatrix;
//	glPushMatrix();
//	glLoadIdentity();
//	glGetFloatv(GL_MODELVIEW_MATRIX, inverseModelMatrix);
//	glPopMatrix();
//
//	//Get the object space light vector
//	VECTOR3D objectLightPosition = inverseModelMatrix * worldLightPosition;
//
//	//Loop through vertices
//	for (int i = 0; i < bookCover.numVertices; ++i)
//	{
//		VECTOR3D lightVector = objectLightPosition - bookCover.vertices[i].position;
//
//		//Calculate tangent space light vector
//		bookCover.vertices[i].tangentSpaceLight.x =
//			bookCover.vertices[i].sTangent.DotProduct(lightVector);
//		bookCover.vertices[i].tangentSpaceLight.y =
//			bookCover.vertices[i].tTangent.DotProduct(lightVector);
//		bookCover.vertices[i].tangentSpaceLight.z =
//			bookCover.vertices[i].normal.DotProduct(lightVector);
//	}
//
//
//	//Draw bump pass
//	//Bind normal map to texture unit 0
//	glBindTexture(GL_TEXTURE_2D, normalMap);
//	glEnable(GL_TEXTURE_2D);
//
//	//Bind normalisation cube map to texture unit 1
//	glActiveTextureARB(GL_TEXTURE1_ARB);
//	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, normalisationCubeMap);
//	glEnable(GL_TEXTURE_CUBE_MAP_ARB);
//	glActiveTextureARB(GL_TEXTURE0_ARB);
//
//	//Set vertex arrays for book
//	glVertexPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].position);
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	//Send texture coords for normal map to unit 0
//	glTexCoordPointer(2, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].s);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	//Send tangent space light vectors for normalisation to unit 1
//	glClientActiveTextureARB(GL_TEXTURE1_ARB);
//	glTexCoordPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].tangentSpaceLight);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glClientActiveTextureARB(GL_TEXTURE0_ARB);
//
//
//	//Set up texture environment to do (tex0 dot tex1)*color
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
//	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
//	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_REPLACE);
//
//	glActiveTextureARB(GL_TEXTURE1_ARB);
//
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
//	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
//	glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_DOT3_RGB_ARB);
//	glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);
//
//	glActiveTextureARB(GL_TEXTURE0_ARB);
//
//
//
//	//Draw book
//	glDrawElements(GL_TRIANGLES, bookCover.numIndices, GL_UNSIGNED_INT, bookCover.indices);
//
//
//	//Disable textures
//	glDisable(GL_TEXTURE_2D);
//
//	glActiveTextureARB(GL_TEXTURE1_ARB);
//	glDisable(GL_TEXTURE_CUBE_MAP_ARB);
//	glActiveTextureARB(GL_TEXTURE0_ARB);
//
//	//disable vertex arrays
//	glDisableClientState(GL_VERTEX_ARRAY);
//
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	glClientActiveTextureARB(GL_TEXTURE1_ARB);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glClientActiveTextureARB(GL_TEXTURE0_ARB);
//
//	//Return to standard modulate texenv
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//
//	//If we are drawing both passes, enable blending to multiply them together
//	//Enable multiplicative blending
//	glBlendFunc(GL_DST_COLOR, GL_ZERO);
//	glEnable(GL_BLEND);
//
//	//Perform a second pass to color the book
//	//Bind decal texture
//	glBindTexture(GL_TEXTURE_2D, decalTexture);
//	glEnable(GL_TEXTURE_2D);
//
//	//Set vertex arrays for book
//	glVertexPointer(3, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].position);
//	glEnableClientState(GL_VERTEX_ARRAY);
//
//	glNormalPointer(GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].normal);
//	glEnableClientState(GL_NORMAL_ARRAY);
//
//	glTexCoordPointer(2, GL_FLOAT, sizeof(Book_VERTEX), &bookCover.vertices[0].s);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	//Draw book
//	glDrawElements(GL_TRIANGLES, bookCover.numIndices, GL_UNSIGNED_INT, bookCover.indices);
//
//	//Disable texture
//	glDisable(GL_TEXTURE_2D);
//
//	//disable vertex arrays
//	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_NORMAL_ARRAY);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//
//	//Disable blending if it is enabled
//	//glBlendFunc(GL_ONE, GL_ONE);  //return to default
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //return to default
//	glDisable(GL_BLEND);
//	/*glFinish();
//	glutSwapBuffers();*/
//}
//float bookAngle = 0.0f;
//float bookOmega = 1.0f;
//int bookPos = 0;
//int bookPosCounter = 0;
//int bookPathSize;
//const int posPerAngle = 2;
//
//void displayLightning()
//{
//	float high = 8;
//	float width = 5;
//	glEnable(GL_BLEND);
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, texture[10]);
//	glPushMatrix();
//	//让闪电随机动起来
//	glTranslatef((rand() % 50 - 25) / 50.0f, (rand() % 50 - 25) / 50.0f, (rand() % 50 - 25) / 5.0f);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0, 0);
//	glNormal3f(0, 0, 1);
//	glVertex3f(-width, 0, -3);
//
//	glTexCoord2f(0, 1);
//	glNormal3f(0, 0, 1);
//	glVertex3f(-width, high, -3);
//
//	glTexCoord2f(1, 1);
//	glNormal3f(0, 0, 1);
//	glVertex3f(width, high, -3);
//
//	glTexCoord2f(1, 0);
//	glNormal3f(0, 0, 1);
//	glVertex3f(width, 0, -3);
//	glEnd();
//	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);
//	glDisable(GL_BLEND);
//}
//
//void myDisplay()
//{
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
//	if (fog)
//	{
//		fcEnd -= fcSEChangeV;
//		fcSEChangeV *= 0.9999f;
//		glFogf(GL_FOG_END, fcEnd);
//		if (fcEnd <= 7.0f)
//		{
//			fog = 0;
//			fogHold = 1;
//			drawBook = 0;
//			cout << "fcSE: " << fcSEChangeV << endl;
//		}
//	}
//	if (fogHold)
//	{
//		fogCounter++;
//		if (fogCounter >= 2000)
//		{
//			fogHold = 0;
//			fogDismiss = 1;
//		}
//	}
//
//	if (fogDismiss)
//	{
//		fcEnd += fcSEChangeV;
//		fcSEChangeV *= 0.9999f;
//		glFogf(GL_FOG_END, fcEnd);
//		if (fcEnd >= 20.0f)
//		{
//			fogDismiss = 0;
//			drawButt = 1;
//			cout << "fcSE: " << fcSEChangeV << endl;
//			glDisable(GL_FOG);
//		}
//	}
//	if (drawSkyBox)
//	{
//		glEnable(GL_TEXTURE_2D);
//		glPushMatrix();
//		glTranslatef(0.0, -y_point, -2);
//		glRotated(120, 0, 1, 0);
//		mSkyBox->ShowSky();
//		glPopMatrix();
//		glDisable(GL_TEXTURE_2D);
//	}
//
//	if (drawLightning)
//	{
//		//电闪雷鸣
//		for (int i = 0; i < 3; i++)
//		{
//			light2_diffuse[i] += flash_V;
//			light2_specular[i] += 2 * flash_V;
//		}
//		if (light2_diffuse[0] < 0 || light2_diffuse[0] > 5)
//		{
//			flash_V = -flash_V;
//		}
//		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
//		glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//	}
//
//	if (drawBook)
//	{
//		glPushMatrix();  //1
//		glTranslated(-0.5f, -1, -8);
//		if (bookPos <= bookPathSize)
//		{
//			//闪电
//			drawLightning = 1;
//
//			//书旋转轨迹
//			bookPosCounter++;
//			if (bookPosCounter == posPerAngle)
//			{
//				displayLightning();
//				bookPos += 1;
//				bookPosCounter = 0;
//			}
//			//飞入画面
//			glTranslatef(bookPath->getX(bookPos), 0.0, bookPath->getY(bookPos));
//			glRotatef((bookPos * posPerAngle + bookPosCounter) * 1.5f + 156, 1, 0, 1);
//			//glRotatef((bookPos * posPerAngle + bookPosCounter) * 1.5f + 156, 1, 0, 0);
//		}
//		else if (flash_count < 900)
//		{
//			//书停，闪电息，雾渐起
//			drawLightning = 0;
//			recoverLight2 = 1;
//			flash_count++;
//			if (flash_count >= 300)
//			{
//				float fc = flash_count / 900.0f;
//				glEnable(GL_FOG);
//				GLfloat fogColor[] = { fc, fc, fc, 0.0 };
//				glFogfv(GL_FOG_COLOR, fogColor);
//			}
//		}
//		else
//		{
//			//雾渐浓
//			fog = 1;
//		}
//
//		//画书封面
//		glPushMatrix();  //2
//		glScaled(bookCoverScaleX, bookCoverScaleY, 1);
//		displayBookCover();
//		glPopMatrix();  //2
//		//画书体
//		glPushMatrix();  //3
//		glTranslatef(bookTranslateX, bookTranslateY, 0.0);
//		glRotatef(90, 0, 1, 0);
//		glRotatef(bookRotate, 1, 0, 0);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[2]);
//		book.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //3
//		glPopMatrix();  //1
//
//		if (recoverLight2)
//		{
//			//光复
//			for (int i = 0; i < 3; i++)
//			{
//				light2_diffuse[i] = 5;
//				light2_specular[i] = 10;
//			}
//			glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
//			glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//		}
//	}
//
//	if (drawButt)
//	{
//		butt_count++;
//		if (butt_count < 4000)
//		{
//
//		}
//		else if (butt_count < 6000)
//		{
//			AngleXZ -= 0.005f;
//			look[0] = eye[0] + 100 * COS(AngleXZ);
//			look[2] = eye[2] + 100 * SIN(AngleXZ);
//		}
//		else if (butt_count < 15000)
//		{
//			//cout << butt_count << endl;
//			AngleXZ -= 0.005f;
//			eye[2] += SIN(AngleXZ) * speed * 0.0003f;
//			eye[0] += COS(AngleXZ) * speed * 0.0003f;
//			look[0] = eye[0] + 100 * COS(AngleXZ);
//			look[2] = eye[2] + 100 * SIN(AngleXZ);
//		}
//		//用环境光变暗来实现转场
//		else if (butt_count < 25000)
//		{
//			//由1变0
//			full_light -= 0.0001f;
//			GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
//			// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//			for (int i = 0; i < 3; i++)
//			{
//				light2_diffuse[i] -= 0.0005f;
//				light2_specular[i] -= 0.001f;
//			}
//			glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
//			glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//		}
//		else
//		{
//			//glDisable(GL_LIGHT2);
//			drawBook = 0;
//			drawSkyBox = 0;
//			drawButt = 0;
//			AngleXZ = -90;
//			eye[0] = 0;
//			eye[1] = 0;
//			eye[2] = 0;
//			look[0] = eye[0] + 100 * COS(AngleXZ);
//			look[2] = eye[2] + 100 * SIN(AngleXZ);
//			buttToRoom = 1;
//			drawRoom = 1;
//			drawStones = 1;
//			flash_count = 0;
//		}
//		glPushMatrix();
//		glTranslated(-0.5f, -1, -8);
//		glEnable(GL_BLEND);
//		butt->show();
//		glDisable(GL_BLEND);
//		glPopMatrix();
//
//
//	}
//
//	if (buttToRoom)
//	{
//		flash_count++;
//		full_light += 0.0001f;
//		GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
//		// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//		if (flash_count == 10000)
//		{
//			cout << full_light << endl;
//			flash_count = 0;
//			buttToRoom = 0;
//		}
//	}
//
//	if (drawRoom)
//	{
//		glDisable(GL_LIGHT1);
//		glDisable(GL_LIGHT2);
//		glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//		glEnable(GL_TEXTURE_2D);
//		//爆炸后的地震
//		glPushMatrix();
//		if (earthquake)
//		{
//			glRotatef((rand() % 2 - 0.5) * alpha, 1, 0, 0);
//			glRotatef((rand() % 2 - 0.5) * alpha, 0, 1, 0);
//			glRotatef((rand() % 2 - 0.5) * alpha, 0, 0, 1);
//			glTranslatef((rand() % 2 - 0.5) * beta, (rand() % 2 - 0.5) * beta, (rand() % 2 - 0.5) * beta);
//		}
//		glPushMatrix();
//		glPushMatrix();
//		glTranslatef(0.0, -3, -15);
//		glRotatef(90, 0, 1, 0);
//		float high = 12;
//		glScaled(1, 4, 1);
//		glBindTexture(GL_TEXTURE_2D, texture[11]);
//		//wall.drawMesh();
//		glPopMatrix();
//
//		//画地面
//		glBindTexture(GL_TEXTURE_2D, texture[9]);
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
//		glNormal3f(0, 0, -1);
//		glVertex3f(-5, 0, -5);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(0, 0, -1);
//		glVertex3f(-5, high, -5);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(0, 0, -1);
//		glVertex3f(5, high, -5);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(0, 0, -1);
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
//
//		glPopMatrix();
//		glPopMatrix();
//		glDisable(GL_TEXTURE_2D);
//	}
//
//	if (drawStones && torch_on)
//	{
//		//画4个石头
//		glPushMatrix();  //1
//		glTranslatef(0.0, -3, -10);
//		glPushMatrix();  //2
//		glTranslatef(-1.5, 0, -2.0);
//		//glRotated(-45, 0, 1, 0);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[11]);
//		stone.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //2
//
//		glPushMatrix();  //2
//		glTranslatef(2.0, 0, -1);
//		glRotated(140, 1, 1, 0);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[11]);
//		stone.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //2
//
//		glPushMatrix();  //2
//		glTranslatef(-2.0, 0, 1.5);
//		glRotated(-45, 0, 1, 0);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[11]);
//		stone.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //2
//
//		glPushMatrix();  //2
//		glTranslatef(0.5, 0, 1.8);
//		glRotated(56, 0, 0, 1);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[11]);
//		stone.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();  //2
//		glPopMatrix();  //1
//	}
//
//	if (drawBomb)
//	{
//		glPushMatrix();  //1
//		glTranslatef(0.0, -3, -12);
//		if (bombZ > 2)
//		{
//			glPushMatrix();  //2
//			//抛物线运动
//			glTranslatef(0.0f, bombY, bombZ);
//			glRotatef(spinX, 1, 0, 0);
//			glScaled(0.2f, 0.2f, 0.2f);
//			glEnable(GL_TEXTURE_2D);
//			glBindTexture(GL_TEXTURE_2D, texture[1]);
//			bomb.drawMesh();
//			glBindTexture(GL_TEXTURE_2D, texture[2]);
//			fuse.ignite();
//			glPopMatrix();  //2
//			bombY += bombVy;
//			bombVy += bombAy;
//			bombZ += bombVz;
//			spinX += spinVx;
//			glDisable(GL_TEXTURE_2D);
//		}
//		else if (bomb_count < 250)
//		{
//			//关灯,爆炸出石块
//			earthquake = 1;
//			alpha -= 0.08 / 250.0f;
//			beta -= 0.04 / 250.0f;
//			torch_on = 0;
//			glDisable(GL_LIGHT0);
//			glEnable(GL_LIGHT3);
//			bomb_count++;
//			blocks->update();
//			drawStones = 0;
//		}
//		else
//		{
//			glDisable(GL_LIGHT3);
//			drawBomb = 0;
//			drawBuddha = 1;
//			drawSward = 1;
//		}
//		glPopMatrix();  //1
//	}
//
//	if (drawBuddha)
//	{
//		glEnable(GL_LIGHT1);
//		glColorMaterial(GL_FRONT, GL_DIFFUSE);
//		glEnable(GL_COLOR_MATERIAL);
//		if (drawSward)
//		{
//			swardSpin += swardTheta;
//			for (int i = 0; i < 3; i++)
//			{
//				mat_color[i] = (rand() % 100) * 0.01f;
//			}
//			glColor4fv(mat_color);
//			glPushMatrix();
//			glTranslatef(0, 2, -10);
//			for (int i = 0; i < swardNum; i++)
//			{
//				glPushMatrix();
//				/*glTranslatef(swardR * COS(i * swardAngle + swardSpin), 0, swardR* SIN(i* swardAngle + swardSpin));
//				glRotatef(-(i * swardAngle + swardSpin) - 90, 0, 1, 0);*/
//				float sangle = float(i * swardAngle) + swardSpin;
//				glTranslatef(swardR * COS(sangle), 0, swardR * SIN(sangle));
//				glRotatef(-sangle - 90, 0, 1, 0);
//				glScalef(2, 2, 2);
//				sward.drawMesh();
//				glPopMatrix();
//			}
//			glPopMatrix();
//		}
//		if (torch_on)
//		{
//			spot_pos[1] = 5;
//			glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//		}
//		glPushMatrix();
//		glTranslatef(0.0, -4, -10);
//		glScalef(10.0f, 10.0f, 10.0f);
//		glColor4fv(mat_colors[buddhaColorIndex]);  //buddha材料属性	
//		if (torch_on)
//		{
//			if (buddhaColorIndex < 200)
//			{
//				buddhaColorIndex++;
//			}
//			if (buddhaColorIndex <= 100)
//			{
//				alpha -= 0.0002f;
//				beta -= 0.0002f;
//				buddha4.drawMesh();
//			}
//			else if (buddhaColorIndex <= 185)
//			{
//				drawSward = 0;
//				earthquake = 0;
//				buddha3.drawMesh();
//			}
//			else if (buddhaColorIndex < 195)
//			{
//				//buddha2.drawMesh();
//				buddha3.drawMesh();
//			}
//			else
//			{
//				//buddha1.drawMesh();
//				buddha3.drawMesh();
//			}
//			//cout << buddhaColorIndex << endl;
//		}
//		else
//		{
//			buddhaColorIndex = 0;
//			buddha4.drawMesh();
//		}
//		glColor3f(0, 0, 0); // 恢复颜色，防止污染
//		glPopMatrix();
//		glDisable(GL_COLOR_MATERIAL);
//	}
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
//			glEnable(GL_LIGHT0);
//		}
//		else
//		{
//			glDisable(GL_LIGHT0);
//		}
//		break;
//	case 'b':
//		drawBomb = 1;
//		break;
//	case 'g':
//		drawBook = 1;
//		drawSkyBox = 1;
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
//particle3d* init_block(float x, float y, float z)
//{
//	float x_offset = (rand() % 40 - 20) / 5;
//	float y_offset = (rand() % 40 - 20) / 20;
//	float z_offset = (rand() % 40 - 20) / 10;
//	float size = rand() % 10 * 0.01f;
//	float speed[] = { float(rand() % 10 - 4) / 40, float(rand() % 10 - 4) / 20, float(rand() % 10 - 4) / 40 };
//	float acc[] = { 1.0f * (rand() % 3 - 1) / 900,4.9 / 400 ,1.0f * (rand() % 3 - 1) / 900 };
//	float angle[] = { rand() % 360, rand() % 360 ,rand() % 360 };
//
//	particle3d* p = new flame_particle(size, size, size, x + x_offset, y + y_offset, z + z_offset,
//		speed[0], speed[1], speed[2], acc[0], acc[1], acc[2], angle[0], angle[1], angle[2],
//		rand() % 40 + 10, texture[12]);
//	return p;
//}
//
//void initBook(void)
//{
//	//Generate Book Path
//	genBookPath();
//	bookPathSize = bookPath->size();
//	//Check for and set up extensions
//	if (!SetUpARB_multitexture() || !SetUpARB_texture_cube_map() ||
//		!SetUpARB_texture_env_combine() || !SetUpARB_texture_env_dot3())
//	{
//		printf("Required Extension Unsupported\n");
//		exit(0);
//	}
//
//	//Load identity modelview
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	//Shading states
//	glShadeModel(GL_SMOOTH);
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//
//	//Depth states
//	glClearDepth(1.0f);
//	glDepthFunc(GL_LEQUAL);
//	glEnable(GL_DEPTH_TEST);
//
//	//glEnable(GL_CULL_FACE);
//
//	//Load normal map
//	IMAGE normalMapImage;
//	//normalMapImage.Load("Normal map.bmp");
//	normalMapImage.Load((char*)("tex\\book_word.bmp"));
//	normalMapImage.ExpandPalette();
//
//	//Convert normal map to texture
//	glGenTextures(1, &normalMap);
//	glBindTexture(GL_TEXTURE_2D, normalMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, normalMapImage.width, normalMapImage.height,
//		0, normalMapImage.format, GL_UNSIGNED_BYTE, normalMapImage.data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//Load decal image
//	IMAGE decalImage;
//	//decalImage.Load("Decal.bmp");
//	decalImage.Load((char*)("tex\\string.bmp"));
//	decalImage.ExpandPalette();
//
//	//Convert decal image to texture
//	glGenTextures(1, &decalTexture);
//	glBindTexture(GL_TEXTURE_2D, decalTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, decalImage.width, decalImage.height,
//		0, decalImage.format, GL_UNSIGNED_BYTE, decalImage.data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//
//	//Create normalisation cube map
//	glGenTextures(1, &normalisationCubeMap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, normalisationCubeMap);
//	GenerateNormalisationCubeMap();
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//}
//
//void myInit()
//{
//	initBook();
//	//glClearColor(1.0, 0.0, 0.0, 0.0);
//	eyex = 0.0, eyey = 0.0, eyez = 20.0f;
//	lookx = 0.0, looky = 0.0, lookz = 0.0;
//
//	srand(unsigned(time(nullptr)));
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//gluPerspective(60.0, windowWidth / windowHeight, 1.0, 21.0);
//	gluPerspective(60.0, windowWidth / windowHeight, 1.0, 30.0);
//
//	glEnable(GL_DEPTH_TEST);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//
//	//手电筒的光
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20);
//	//GLfloat spot_pos[] = { 0, -1, 2, 0.0f };
//
//	//照着buddha的光
//	float light1_pos[] = { 0, 3, 2, 0.0f };
//	float light1_diffuse[] = { 5,5,5 };
//	float light1_specular[] = { 10,10,10 };
//
//	//Set up light
//	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
//
//	float light0_diffuse[] = { 5,5,5 };
//	float light0_specular[] = { 10,10,10 };
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
//
//	//炸弹爆炸的光
//	float light3_pos[] = { 0, 3, 3, 0.0f };
//	float light3_diffuse[] = { 1,0.3,0.3 };
//
//	//Set up light
//	glLightfv(GL_LIGHT3, GL_POSITION, light3_pos);
//	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_diffuse);
//
//	//双面光照
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//	glEnable(GL_LIGHTING);
//	// 指定全局环境光的RGBA强度值,照亮书和蝴蝶，后面可以换成光源，让字体发光
//	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//
//	//Set up light
//	glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
//	glEnable(GL_LIGHT2);
//
//	//迷雾
//	// 启用雾化功能-----------------
//	//glFogi(GL_FOG_MODE, GL_EXP2  /*GL_EXP	GL_EXP2	GL_LINEAR*/);
//	glFogi(GL_FOG_MODE, GL_LINEAR  /*GL_EXP	GL_EXP2	GL_LINEAR*/);
//	glFogf(GL_FOG_DENSITY, 0.15f);
//	glFogf(GL_FOG_START, fcStart);
//	glFogf(GL_FOG_END, fcEnd);
//	glHint(GL_FOG_HINT, GL_NICEST);
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
//	int* tex = new int[3];
//	tex[0] = texture[5];
//	tex[1] = texture[6];
//	tex[2] = texture[7];
//	butt = new butterflyManager(tex);
//	butt->isDraw = true;
//	delete tex;
//
//	TCHAR filename5[] = L"tex\\Sword_roughness.jpg";  //这里应该用好的mapping
//	BuildTexture(filename5, texture[8]);
//	//石头们(一个当多个用呗
//	stone.readFile("obj\\stone.obj");
//	//石屑
//	block_unit.readFile("obj\\rock.obj");
//	//剑
//	sward.readFile("obj\\sward.obj");
//
//	TCHAR filename6[] = L"tex\\th.jpg";  //这里应该用好的mapping
//	BuildTexture(filename6, texture[9]);
//
//	//炸弹
//	TCHAR filename7[] = L"tex\\gold.jpg";
//	BuildTexture(filename7, texture[1]);
//	TCHAR filename8[] = L"tex\\string.jpg";
//	BuildTexture(filename8, texture[2]);
//	TCHAR filename9[] = L"tex\\spark.bmp";
//	BuildTexture(filename9, texture[3]);
//
//	//石屑
//	TCHAR filename12[] = L"tex\\rock.jpg";
//	BuildTexture(filename12, texture[12]);
//
//	//闪电
//	TCHAR filename10[] = L"tex\\shandian4.jpg";
//	BuildTexture(filename10, texture[10]);
//
//	TCHAR filename11[] = L"tex\\stone.jpg";
//	BuildTexture(filename11, texture[11]);
//
//	//墙
//	wall.readFile("obj\\wall.obj");
//	TCHAR filename13[] = L"tex\\wall.jpg";
//	BuildTexture(filename13, texture[13]);
//
//	bomb.readFile("obj\\new_bomb.obj");
//	fuse.readFile("obj\\new_fuse.obj");
//	book.readFile("obj\\book.obj");
//
//	blocks = new emitter(200, 0.0f, 2.0f, 2.0f);
//	blocks->emit(init_block);
//	cout << "okk" << endl;
//	blocks->block = block_unit;
//	cout << "okk2" << endl;
//
//	buddha4.readFile("obj\\happy_vrip_res4.obj");
//	cout << "load buddha4 finish" << endl;
//	/*buddha3.readFile("obj\\happy_vrip_res3.obj");
//	cout << "load buddha3 finish" << endl;*/
//	/*buddha2.readFile("obj\\happy_vrip_res2.obj");
//	cout << "load buddha2 finish" << endl;
//	buddha1.readFile("obj\\happy_vrip.obj");
//	cout << "load buddha1 finish" << endl;*/
//
//	//天空盒子
//	CString TexPath(".\\skybox\\mp_cloud9\\cloud9_"); // 云 台  这个好
//	mSkyBox = new CjySkyBox(skyboxSize, TexPath + "bk.tga", TexPath + "ft.tga", TexPath +
//		"rt.tga", TexPath + "lf.tga", TexPath + "up.tga", TexPath + "dn.tga");
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
