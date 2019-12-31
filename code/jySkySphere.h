
#ifndef _jySKYSPHERE_H
#define _jySKYSPHERE_H

#include <gl\glut.h>
#include "jyImage.h"

class CjySkySphere
{
public:
	CjySkySphere(float skyX, float skyY, float skyZ, float skyR, CString strTextrueFilePath);
	//显示天空
	void ShowSky(void);
	//获得天空的属性
	float GetSkyX(void);
	float GetSkyY(void);
	float GetSkyZ(void);
	float GetSkyR(void);

private:
	float X;
	float Y;
	float Z;
	float R;
	GLuint  nTextureNum;
	GLUquadricObj* qobj;
	void GetSkyTexture(CString strTextrueFilePath);

};
#endif