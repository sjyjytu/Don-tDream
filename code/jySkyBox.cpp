#include "jySkyBox.h"


CjySkyBox::CjySkyBox(GLfloat SkyWidth, CString OnePicFilePath)
{
	nPicStyle = 1;
	fSky_W = SkyWidth;
	glGenTextures(1, & nTextureNum[0]);
	// ˵��ӳ�䷽ʽ
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  ��������ӳ��
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // �ĳ�GL_LINE �����ȫû�ˣ�
	glEnable(GL_DEPTH_TEST);
	CjyImage mPic(OnePicFilePath);

	fSky_H = fSky_W * mPic.GetHeight()*4.0f / (3.0f * mPic.GetWidth()); // ��֤��պ��Ӻ�ͼƬ�ߴ�ɱ���������ͼ�����ʧ�棡
	glPixelStorei(GL_UNPACK_ALIGNMENT, mPic.GetAlignment()); // 4�ֽڶ���
	glBindTexture(GL_TEXTURE_2D, nTextureNum[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + mPic.CheckAlpha(), mPic.GetWidth(), mPic.GetHeight(), 0, mPic.GetImageType(), GL_UNSIGNED_BYTE, mPic.GetImagePt());
}


CjySkyBox::CjySkyBox(GLfloat SkyWidth, CString Lpic, CString Rpic, CString Fpic, CString Bpic, CString Tpic, CString Dpic)
{
	nPicStyle = 0;
	fSky_W = SkyWidth;
	//fSky_H = fSky_W / 2;
	glGenTextures(5, nTextureNum);

	// ˵��ӳ�䷽ʽ
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  ��������ӳ��
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // �ĳ�GL_LINE �����ȫû�ˣ�
	glEnable(GL_DEPTH_TEST);
	Dpic = Dpic.IsEmpty() ? Tpic : Dpic;
	CjyImage mPic[6]={Lpic,Rpic,Fpic,Bpic,Tpic,Dpic};
	for(int i=0; i<6; i++)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, mPic[i].GetAlignment()); // 4�ֽڶ���
		glBindTexture(GL_TEXTURE_2D, nTextureNum[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + mPic[i].CheckAlpha(), mPic[i].GetWidth(), mPic[i].GetHeight(), 0, mPic[i].GetImageType(), GL_UNSIGNED_BYTE, mPic[i].GetImagePt());
	}
	fSky_H = fSky_W * mPic[0].GetHeight() /  mPic[0].GetWidth(); // ��֤��պ��Ӻ�ͼƬ�ߴ�ɱ���������ͼ�����ʧ�棡
}
/*
ʹ����պ�ʱ��������϶�޷����������⣬��򵥵ķ�����ʹ�ñ�Ե��ȡ��GL_CLAMP_TO_EDGE�������Ǻ��Ա߽硣���������Ե���߿��������Ե������Ԫ������������㣬���ǲ������߽��ϵ�����Ԫ��
����һ����ֻ������OpenGL1.2��������汾�У�������ʹ�õ�VC�е�opengl��������Ϊ1.1,���Ա���ʱVC�ᱨ��:GL_CLAMP_TO_EDGEû��������
��ʵ����������Ŀǰϵͳ��ʹ�õ�opengl���ļ���Ϊ���°汾��ֻ��VC����������Ϊ1.1����GL_CLAMP_TO_EDGE�����Ͻ�Ϊһ���궨�壬�������ǿ����ڴ����в�ʹ�øú궨���ֱ��ʹ����ֵ0x812F�������ͬ���������óɱ�Ե��ȡ����һ�����ܡ�
��ʹ�ã�
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,0x812F);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,0x812F);
��Ϊ���´�������Ʒ��
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
	if (nPicStyle == 0) // 6������ͼƬ��ʽ
	{
		SetTex(nTextureNum[0]); //LEFT
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[1]); //right
		glBegin(GL_QUADS); // �Ҳ�
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[2]);
		glBegin(GL_QUADS); // ǰ
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[3]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[4]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		SetTex(nTextureNum[5]);
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f, 0.0f);	glVertex3f(-fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glEnd();
	}
	else // ��һͼƬ��ʽ
	{
		GLfloat W = 0.25f;
		GLfloat H = (float)1 / 3;

		SetTex(nTextureNum[0]); //ǰ��������������ͼ����һ��ͼƬ��
		glBegin(GL_QUADS); // ��
		glTexCoord2f(0.0f,	H  );	glVertex3f(-fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(W,		H  );	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(W,		2*H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(0.0f,	2*H);	glVertex3f(-fSky_W / 2., fSky_H, fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // �Ҳ�
		glTexCoord2f(2*W,	H	);	glVertex3f(fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(3*W,	H	);	glVertex3f(fSky_W / 2., 0, fSky_W / 2.);
		glTexCoord2f(3*W,	2 * H);	glVertex3f(fSky_W / 2., fSky_H, fSky_W / 2.);
		glTexCoord2f(2*W,	2 * H);	glVertex3f(fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // ǰ
		glTexCoord2f(W,		H);		glVertex3f(-fSky_W / 2., 0,		-fSky_W / 2.);
		glTexCoord2f(2 * W,	H);		glVertex3f( fSky_W / 2., 0,		-fSky_W / 2.);
		glTexCoord2f(2 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(W,		2 * H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // ��
		glTexCoord2f(3 * W, H);		glVertex3f( fSky_W / 2., 0,			fSky_W / 2.);
		glTexCoord2f(4 * W, H);		glVertex3f(-fSky_W / 2., 0,			fSky_W / 2.);
		glTexCoord2f(4 * W, 2 * H);	glVertex3f(-fSky_W / 2., fSky_H,	fSky_W / 2.);
		glTexCoord2f(3 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H,	fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // ��
		glTexCoord2f(W,		2*H);	glVertex3f(-fSky_W / 2., fSky_H, -fSky_W / 2.);
		glTexCoord2f(2 * W, 2 * H);	glVertex3f( fSky_W / 2., fSky_H ,-fSky_W / 2.);
		glTexCoord2f(2 * W, 1.0f);	glVertex3f( fSky_W / 2., fSky_H , fSky_W / 2.);
		glTexCoord2f(W, 1.0f);		glVertex3f(-fSky_W / 2., fSky_H , fSky_W / 2.);
		glEnd();
		glBegin(GL_QUADS); // ��
		glTexCoord2f(W,			0);	glVertex3f(-fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(2 * W,		0);	glVertex3f( fSky_W / 2., 0,  fSky_W / 2.);
		glTexCoord2f(2 * W,		H);	glVertex3f( fSky_W / 2., 0, -fSky_W / 2.);
		glTexCoord2f(W,			H);	glVertex3f(-fSky_W / 2., 0, -fSky_W / 2.);
		glEnd();
	}
}