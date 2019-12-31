
#ifndef _jySKYBOX_H
#define _jySKYBOX_H
#include <gl\glut.h>
#include "jyImage.h"

class CjySkyBox
{
private:
	GLfloat fSky_W;
	GLfloat fSky_H;
	GLuint  nPic_W; // ��պ���ͼƬΪ��һͼƬ��ʽ��ͼƬ���
	GLuint  nPic_H; // ��պ���ͼƬΪ��һͼƬ��ʽ��ͼƬ�߶�
	GLuint  nTextureNum[6]; // ����5�ţ�ȱ����ͼ�󣩻�6��ͼƬ������Skybox,����5��6��ͼƬ��������õ�ͼƬ��ʽ����ͼƬ������nTextureNum[0]�С�
	GLuint  nPicStyle; //�����ǵ�ͼƬ��ʽ�����Ƕ�ͼƬ��ʽ���е���ղ���5��ͼƬ(������nPicStyle=0)���еİ�����ͼƬ�ŵ���һ�ļ�����ͼƬ��ʽҲ�ж��ָ�ʽ����������ʽ��������Ե��Ǻ��ŵ�ͼƬ�ļ��ǡ�-+--����ʽ(nPicStyle=1)��
	void SetTex(GLuint texNum);
public:
	CjySkyBox(GLfloat SkyWidth, CString Lpic, CString Rpic, CString Fpic, CString Bpic, CString Tpic, CString Dpic = ""); // 6��ͼƬ��ʽ�ĳ�ʼ������,5�ž���û�������ʽ
	CjySkyBox(GLfloat SkyWidth, CString OnePicFilePath); // 1��ͼƬ�ĳ�ʼ��������
	void ShowSky(void);
};

#endif