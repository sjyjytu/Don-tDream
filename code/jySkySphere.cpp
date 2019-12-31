#include "jySkySphere.h"

CjySkySphere::CjySkySphere(float skyX, float skyY, float skyZ, float skyR, CString strTextrueFilePath)
{
	X = skyX;
	Y = skyY;
	Z = skyZ;
	R = skyR;

	GetSkyTexture(strTextrueFilePath);
	
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricTexture(qobj, GL_TRUE);
}

void CjySkySphere::GetSkyTexture(CString strTextrueFilePath)
{
	CjyImage mTexturePic(strTextrueFilePath);
	glGenTextures(1, & nTextureNum);

	// 说明映射方式
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	//  启动纹理映射
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 改成GL_LINE 纹理就全没了！
	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_COLOR_MATERIAL);


	glPixelStorei(GL_UNPACK_ALIGNMENT, mTexturePic.GetAlignment()); // 4字节对齐
	glBindTexture(GL_TEXTURE_2D, nTextureNum);

	//gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pImage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 修改 试一下
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + mTexturePic.CheckAlpha(), mTexturePic.GetWidth(), mTexturePic.GetHeight(), 0, mTexturePic.GetImageType(), GL_UNSIGNED_BYTE, mTexturePic.GetImagePt());

}

void CjySkySphere::ShowSky()
{
//	static float r = 0.0;
//	r += 0.08;
//	glEnable(GL_TEXTURE_2D);
//	glPushMatrix();
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, nTextureNum);
//	glTranslatef(X, Y, Z);
//	glRotatef(r, 0.0f, 1.0f, 0.0f); //天空慢慢旋转,模拟云流动
	glRotatef(90, 1, 0, 0);
//	glColor4f(1, 1, 1, 1);
	gluSphere(qobj, R, 32, 32);
//	glPopMatrix();
//	glDisable(GL_TEXTURE_2D);
}
float CjySkySphere::GetSkyR()
{
	return R;
}
float CjySkySphere::GetSkyX()
{
	return X;
}
float CjySkySphere::GetSkyY()
{
	return Y;
}
float CjySkySphere::GetSkyZ()
{
	return Z;
}