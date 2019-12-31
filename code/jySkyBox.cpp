#include "jySkyBox.h"


CjySkyBox::CjySkyBox(GLfloat SkyWidth, CString OnePicFilePath)
{
	nPicStyle = 1;
	fSky_W = SkyWidth;
	glGenTextures(1, & nTextureNum[0]);
	// 说明映射方式
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  启动纹理映射
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 改成GL_LINE 纹理就全没了！
	glEnable(GL_DEPTH_TEST);
	CjyImage mPic(OnePicFilePath);

	fSky_H = fSky_W * mPic.GetHeight()*4.0f / (3.0f * mPic.GetWidth()); // 保证天空盒子和图片尺寸成比例，否则图象变形失真！
	glPixelStorei(GL_UNPACK_ALIGNMENT, mPic.GetAlignment()); // 4字节对齐
	glBindTexture(GL_TEXTURE_2D, nTextureNum[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + mPic.CheckAlpha(), mPic.GetWidth(), mPic.GetHeight(), 0, mPic.GetImageType(), GL_UNSIGNED_BYTE, mPic.GetImagePt());
}


CjySkyBox::CjySkyBox(GLfloat SkyWidth, CString Lpic, CString Rpic, CString Fpic, CString Bpic, CString Tpic, CString Dpic)
{
	nPicStyle = 0;
	fSky_W = SkyWidth;
	//fSky_H = fSky_W / 2;
	glGenTextures(5, nTextureNum);

	// 说明映射方式
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  启动纹理映射
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 改成GL_LINE 纹理就全没了！
	glEnable(GL_DEPTH_TEST);
	Dpic = Dpic.IsEmpty() ? Tpic : Dpic;
	CjyImage mPic[6]={Lpic,Rpic,Fpic,Bpic,Tpic,Dpic};
	for(int i=0; i<6; i++)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, mPic[i].GetAlignment()); // 4字节对齐
		glBindTexture(GL_TEXTURE_2D, nTextureNum[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + mPic[i].CheckAlpha(), mPic[i].GetWidth(), mPic[i].GetHeight(), 0, mPic[i].GetImageType(), GL_UNSIGNED_BYTE, mPic[i].GetImagePt());
	}
	fSky_H = fSky_W * mPic[0].GetHeight() /  mPic[0].GetWidth(); // 保证天空盒子和图片尺寸成比例，否则图象变形失真！
}
/*
使用天空盒时常遇到缝隙无法消除的问题，最简单的方法是使用边缘截取（GL_CLAMP_TO_EDGE）：总是忽略边界。处于纹理边缘或者靠近纹理边缘的纹理单元都用作纹理计算，但是不包括边界上的纹理单元。
但这一参数只出现在OpenGL1.2及其后续版本中，而我们使用的VC中的opengl开发包仅为1.1,所以编译时VC会报错:GL_CLAMP_TO_EDGE没有声明。
事实上由于我们目前系统中使用的opengl库文件均为最新版本，只是VC附带开发包为1.1，而GL_CLAMP_TO_EDGE本质上仅为一个宏定义，所以我们可以在代码中不使用该宏定义而直接使用数值0x812F来替代，同样可以设置成边缘截取的这一个功能。
即使用：
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812F);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812F);
作为如下代码的替代品。
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
*/
void CjySkyBox::SetTex(GLuint texNum)
{
	glBindTexture(GL_TEXTURE_2D, texNum);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void CjySkyBox::ShowSky()
{
	if (nPicStyle == 0) // 6个单独图片形式
	{
		SetTex(nTextureNum[0]); //LEFT
		glBegin(GL_QUADS); // 左
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[1]); //right
		glBegin(GL_QUADS); // 右侧
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[2]);
		glBegin(GL_QUADS); // 前
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[3]);
		glBegin(GL_QUADS); // 后
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[4]);
		glBegin(GL_QUADS); // 上
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[5]);
		glBegin(GL_QUADS); // 下
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glEnd();
	}
	else // 单一图片形式
	{
		GLfloat W = 0.25f;
		GLfloat H = (float)1 / 3;

		SetTex(nTextureNum[0]); //前后左右上下纹理图象都在一张图片中
		glBegin(GL_QUADS); // 左
		glTexCoord2f(0.0f,	H  );	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(W,		H  );	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(W,		2*H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f,	2*H);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // 右侧
		glTexCoord2f(2*W,	H	);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(3*W,	H	);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(3*W,	2 * H);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(2*W,	2 * H);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // 前
		glTexCoord2f(W,		H);		glVertex3f(-fSky_W / 2., 0,		-fSky_W / 2.);
		glTexCoord2f(2 * W,	H);		glVertex3f( fSky_W / 2., 0,		-fSky_W / 2.);
		glTexCoord2f(2 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(W,		2 * H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // 后
		glTexCoord2f(3 * W, H);		glVertex3f( fSky_W / 2., 0,			fSky_W / 2.);
		glTexCoord2f(4 * W, H);		glVertex3f(-fSky_W / 2., 0,			fSky_W / 2.);
		glTexCoord2f(4 * W, 2 * H);	glVertex3f(-fSky_W / 2., fSky_H,	fSky_W / 2.);
		glTexCoord2f(3 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H,	fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // 上
		glTexCoord2f(W,		2*H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(2 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H ,-fSky_W / 2.);
		glTexCoord2f(2 * W, 1.0f);	glVertex3f( fSky_W / 2., fSky_H , fSky_W / 2.);
		glTexCoord2f(W, 1.0f);		glVertex3f(-fSky_W / 2., fSky_H , fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // 下
		glTexCoord2f(W,			0);	glVertex3f(-fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(2 * W,		0);	glVertex3f( fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(2 * W,		H);	glVertex3f( fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(W,			H);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glEnd();
	}
}