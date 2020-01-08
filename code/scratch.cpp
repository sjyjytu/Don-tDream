//#define _CRT_SECURE_NO_WARNINGS
//#define PI			3.14159f
//#define D2rad(X)	PI*X/180.0f		//度°转为弧度rad
//#define SIN(X)		sin(D2rad(X))	// 重新定义sin(X),单位为度，不是弧度
//#define COS(X)		cos(D2rad(X))	// 重新定义cos(X),单位为度，不是弧度
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
//GLuint texture[10];
//
//float angle = 0.0f;
//
//butterflyManager* butt;
//
//float eyex, eyey, eyez, lookx, looky, lookz;
//
//bool drawSkyBox = 1, drawBook = 0, drawButt = 0, drawRoom = 0, drawSward = 0, drawBomb = 0, drawBuddha = 0, buttToRoom = 0;
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
//CjySkyBox *mSkyBox;
//
//float bombY = 3.0f, bombZ = 12.0f, spinX = 45;
//float bombVy = 0.05f, bombAy = -0.001f, bombVz = -0.08f, spinVx = -1;
//
//int flash_count = 0;
//float full_light = 1.0f;
//
//void myDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(eye[0], eye[1], eye[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
//	
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
//	if (drawBook)
//	{
//		glPushMatrix();
//		glTranslated(-0.5f, -1, -8);
//		//glRotated(-90, 0, 1, 0);
//		glPushMatrix();
//		glRotated(angle, 0, 1, 0);
//		angle -= 0.01f;
//
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[0]);
//		//画书封面
//		/*glBegin(GL_POLYGON);
//		glTexCoord2f(0, 0);
//		glNormal3f(0, 0, 1);
//		glVertex3f(0, 0, 0);
//
//		glTexCoord2f(1, 0);
//		glNormal3f(0, 0, 1);
//		glVertex3f(1, 0, 0);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(0, 0, 1);
//		glVertex3f(1, 2, 0);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(0, 0, 1);
//		glVertex3f(0, 2, 0);*/
//
//		//画书内容
//		glEnd();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();
//
//		glBegin(GL_POLYGON);
//		glNormal3f(0, 0, 1);
//		glVertex3f(0, 0, 0);
//
//		glNormal3f(0, 0, 1);
//		glVertex3f(1, 0, 0);
//
//		glNormal3f(0, 0, 1);
//		glVertex3f(1, 2, 0);
//
//		glNormal3f(0, 0, 1);
//		glVertex3f(0, 2, 0);
//
//		glEnd();
//		glPopMatrix();
//
//		flash_count++;
//		if (flash_count > 10000)
//		{
//			drawButt = 1;
//		}
//	}
//	
//	if (drawButt)
//	{
//		AngleXZ -= 0.005f;
//		look[0] = eye[0] + 100 * COS(AngleXZ);
//		look[2] = eye[2] + 100 * SIN(AngleXZ);
//		glPushMatrix();
//		glTranslated(-0.5f, -1, -8);
//		glEnable(GL_BLEND);
//		butt->show();
//		glDisable(GL_BLEND);
//		glPopMatrix();
//		/*if (flash_count == 10005)
//		{
//			glEnable(GL_FOG);
//		}*/
//		//用环境光变暗来实现消失在迷雾中
//		if (flash_count > 20000)
//		{
//			//由1变0
//			full_light -= 0.0001f;
//			GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
//			// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//		}
//		if (flash_count == 30000)
//		{
//			drawBook = 0;
//			drawSkyBox = 0;
//			drawButt = 0;
//			AngleXZ = -90;
//			look[0] = eye[0] + 100 * COS(AngleXZ);
//			look[2] = eye[2] + 100 * SIN(AngleXZ);
//			buttToRoom = 1;
//			drawRoom = 1;
//			drawSward = 1;
//			flash_count = 0;
//			//还应加入消失在迷雾中
//		}
//	}
//
//	if (buttToRoom)
//	{
//		flash_count++;
//		full_light += 0.00003f;
//		GLfloat ambientLight[] = { full_light, full_light, full_light, 1.0f };
//		// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//		if (flash_count==10000)
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
//		//glEnable(GL_LIGHT1);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[9]);
//		glPushMatrix();
//		glTranslatef(0.0, -3, -10);
//		//画左面
//		glBegin(GL_QUADS);
//		glTexCoord2f(0, 0);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, 0, 10);
//
//		glTexCoord2f(0, 1);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, 10, 10);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(1, 0, 0);
//		glVertex3f(-5, 10, -5);
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
//		glVertex3f(5, 10, 10);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(-1, 0, 0);
//		glVertex3f(5, 10, -5);
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
//		glVertex3f(-5, 10, -5);
//
//		glTexCoord2f(1, 1);
//		glNormal3f(0, 0, 1);
//		glVertex3f(5, 10, -5);
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
//	if (torch_on)
//	{
//		float y = AngleYZ / 180.0f;
//		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
//		GLfloat spot_pos[] = { eye[0]- COS(AngleXZ), -y, eye[2]- SIN(AngleXZ), 0.0f };
//		glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//		GLfloat  spot_direction[] = { 100*COS(AngleXZ),y-3, 100*SIN(AngleXZ) };
//		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//		glEnable(GL_LIGHT0);
//	}
//	else
//	{
//		glDisable(GL_LIGHT0);
//	}
//
//	if (drawSward && torch_on)
//	{
//		glPushMatrix();
//		glTranslatef(0.0, -3, -10);
//		glPushMatrix();
//		glRotated(-45, 0, 1, 0);
//		glScaled(0.01, 0.01, 0.01);
//		glEnable(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, texture[8]);
//		sward.drawMesh();
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();
//		glPopMatrix();
//	}
//
//	if (drawBomb)
//	{
//		glPushMatrix();
//		glTranslatef(0.0, -3, -12);
//		if (bombZ > 2)
//		{
//			glPushMatrix();
//			//抛物线运动
//			glTranslatef(0.0f, bombY, bombZ);
//			glRotatef(spinX, 1, 0, 0);
//			glScaled(0.2f, 0.2f, 0.2f);
//			glEnable(GL_TEXTURE_2D);
//			glBindTexture(GL_TEXTURE_2D, texture[1]);
//			bomb.drawMesh();
//			glBindTexture(GL_TEXTURE_2D, texture[2]);
//			fuse.ignite();
//			glPopMatrix();
//			bombY += bombVy;
//			bombVy += bombAy;
//			bombZ += bombVz;
//			spinX += spinVx;
//			glDisable(GL_TEXTURE_2D);
//		}
//		else if (flash_count < 5000)
//		{
//			//爆炸出石块
//			torch_on = 0;
//			flash_count++;
//			blocks->update();
//			drawSward = 0;
//		}
//		else
//		{
//			flash_count = 0;
//			drawBomb = 0;
//			drawBuddha = 1;
//		}
//		glPopMatrix();
//	}
//
//	if (drawBuddha)
//	{
//		glPushMatrix();
//		glTranslatef(0.0, -3, -10);
//		glEnable(GL_LIGHT1);
//		glPushMatrix();
//		glTranslatef(0.0f, -1.0f, 0.0f);
//		glScalef(10.0f, 10.0f, 10.0f);
//		glEnable(GL_TEXTURE_2D);
//		//if (torch_on)
//		//{
//		//	flash_count++;
//		//	cout << flash_count << endl;
//		//	//材质逐渐变银最后变金色
//		//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//		//	if (flash_count==100)
//		//	{
//		//		cout << "buddha load res3" << endl;
//		//		buddha.reReadFile("obj\\happy_vrip_res3.obj");
//		//		cout << "buddha finish res3" << endl;
//		//	}
//		//	else if(flash_count == 120)
//		//	{
//		//		cout << "buddha load res2" << endl;
//		//		buddha.reReadFile("obj\\happy_vrip_res2.obj");
//		//		cout << "buddha finish res2" << endl;
//		//	}
//		//	else if(flash_count == 140)
//		//	{
//		//		cout << "buddha load res1" << endl;
//		//		buddha.reReadFile("obj\\happy_vrip.obj");
//		//		cout << "buddha finish res1" << endl;
//		//	}
//		//}
//		//else
//		//{
//		//	if (flash_count!=0)
//		//	{
//		//		flash_count = 0;
//		//		cout << "buddha load res4" << endl;
//		//		buddha.reReadFile("obj\\happy_vrip_res4.obj");
//		//		cout << "buddha finish res4" << endl;
//		//	}
//		//	//绑定粗糙纹理,设置灰色石质
//		//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//		//}
//		//buddha.drawMesh();
//		if (torch_on)
//		{
//			flash_count++;
//			if (flash_count>= 100&&flash_count<200)
//			{
//				buddha3.drawMesh();
//			}
//			if (flash_count >= 200 && flash_count < 240)
//			{
//				buddha2.drawMesh();
//			}
//			if (flash_count >= 240)
//			{
//				buddha1.drawMesh();
//			}
//		}
//		else
//		{
//			flash_count = 0;
//			buddha4.drawMesh();
//		}
//		glDisable(GL_TEXTURE_2D);
//		glPopMatrix();
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
//		break;
//	case 'b':
//		drawBomb = 1;
//		break;
//	case 'g':
//		drawBook = 1;
//		break;
//	case 's':
//		drawSkyBox = !drawSkyBox;
//		break;
//	default:
//		break;
//	}
//}
//
//void specialKey(int key, int xx, int yy)
//{
//	float speed = 1.0f;
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
//	float size = rand() % 10;
//	float color[] = { 226 / 255.0f, 17 / 255.0f, 12 / 255.0f };
//	particle3d* p = new particle3d(size, x, y, z,
//		(rand() % 10 - 5) / 100.0, (rand() % 10 - 5) / 100.0, (rand() % 10 - 5) / 100.0,
//		(rand() % 10 - 5) / 1000.0, (rand() % 10 - 5) / 1000.0, (rand() % 10 - 5) / 1000.0,
//		rand() % 50, color);
//	return p;
//}
//
//void myInit()
//{
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
//	//float pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//	//float white[] = { 255,255,255 };
//	//float dimwhite[] = { 0.2 * 255,0.2 * 255,0.2 * 255 };
//	////Set up light
//	//glLightfv(GL_LIGHT1, GL_POSITION, pos);
//	//glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
//	//glLightfv(GL_LIGHT1, GL_AMBIENT, dimwhite);
//	//glLightfv(GL_LIGHT1, GL_SPECULAR, white);
//	//glEnable(GL_LIGHT1);
//	
//	//手电筒的光
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60);
//	GLfloat spot_pos[] = { 0, -1, 2, 0.0f };
//	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
//	GLfloat  spot_direction[] = { 0, 0.0, -1.0 };
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//
//	//照着buddha的光
//	float light1_pos[] = { 0, 3, 2, 0.0f };
//	float light1_diffuse[] = { 5,5,5 };
//	float light1_specular[] = { 10,10,10 };
//	float dimwhite[] = { 2,2,2 };
//	//Set up light
//	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//	//glLightfv(GL_LIGHT1, GL_AMBIENT, dimwhite);
//	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular);
//	
//	glEnable(GL_LIGHTING);
//	 // 指定全局环境光的RGBA强度值,照亮书和蝴蝶，后面可以换成光源，让字体发光
//	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	// 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
//
//	//迷雾
//	// 启用雾化功能-----------------
//	//glEnable(GL_FOG);
//	//GLfloat fogColor[] = { 0.6, 0.6, 0.6, 0.0 };
//	//glFogi(GL_FOG_MODE, GL_EXP2  /*GL_EXP	GL_EXP2	GL_LINEAR*/);
//	//glFogfv(GL_FOG_COLOR, fogColor);
//	//glFogf(GL_FOG_DENSITY, 0.15f);
//	//glFogf(GL_FOG_START, 5.0);
//	//glFogf(GL_FOG_END, 200.0);
//	//glHint(GL_FOG_HINT, GL_NICEST);
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
//	cout << "ok0" << endl;
//	TCHAR filename5[] = L"tex\\Sword_roughness.jpg";  //这里应该用好的mapping
//	BuildTexture(filename5, texture[8]);
//	cout << "ok" << endl;
//	sward.readFile("obj\\sword2.obj");
//
//	TCHAR filename6[] = L"tex\\th.jpg";  //这里应该用好的mapping
//	BuildTexture(filename6, texture[9]);
//
//	//炸弹
//	TCHAR filename7[] = L"tex\\bomb5.jpg";
//	BuildTexture(filename7, texture[1]);
//	TCHAR filename8[] = L"tex\\string.jpg";
//	BuildTexture(filename8, texture[2]);
//	TCHAR filename9[] = L"tex\\spark.bmp";
//	BuildTexture(filename9, texture[3]);
//
//	bomb.readFile("obj\\new_bomb.obj");
//	fuse.readFile("obj\\new_fuse.obj");
//
//	blocks = new emitter(200, 0.0f, 2.0f, 2.0f);
//	blocks->emit(init_block);
//
//	buddha4.readFile("obj\\happy_vrip_res4.obj");
//	cout << "load buddha4 finish" << endl;/*
//	buddha3.readFile("obj\\happy_vrip_res3.obj");
//	cout << "load buddha3 finish" << endl;
//	buddha2.readFile("obj\\happy_vrip_res2.obj");
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
