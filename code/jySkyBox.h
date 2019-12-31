
#ifndef _jySKYBOX_H
#define _jySKYBOX_H
#include <gl\glut.h>
#include "jyImage.h"

class CjySkyBox
{
private:
	GLfloat fSky_W;
	GLfloat fSky_H;
	GLuint  nPic_W; // 天空盒子图片为单一图片形式，图片宽度
	GLuint  nPic_H; // 天空盒子图片为单一图片形式，图片高度
	GLuint  nTextureNum[6]; // 采用5张（缺地面图象）或6张图片来绘制Skybox,保存5或6个图片。如果采用单图片方式，则图片保存在nTextureNum[0]中。
	GLuint  nPicStyle; //表明是单图片方式，还是多图片方式。有的天空采用5张图片(则，设置nPicStyle=0)，有的把所有图片放到单一文件。单图片形式也有多种格式，横竖、格式，这里针对的是横排单图片文件是“-+--”格式(nPicStyle=1)。
	void SetTex(GLuint texNum);
public:
	CjySkyBox(GLfloat SkyWidth, CString Lpic, CString Rpic, CString Fpic, CString Bpic, CString Tpic, CString Dpic = ""); // 6张图片方式的初始化函数,5张就是没地面的形式
	CjySkyBox(GLfloat SkyWidth, CString OnePicFilePath); // 1张图片的初始化函数。
	void ShowSky(void);
};

#endif