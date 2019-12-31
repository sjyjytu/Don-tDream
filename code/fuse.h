#pragma once

#include "mesh.h"

class Fuse :public Mesh
{
public:
	bool ignited;
	bool burn_out;
	int counter;
	void ignite();
	Fuse();
};

Fuse::Fuse()
{
	burn_out = 0;
	ignited = 0;
	counter = 0;
}

void Fuse::ignite()
{
	if (vFace.empty())
	{
		burn_out = 1;
		return;
	}
	head.y -= 0.0004f;

	// ������
	if (vText.size() > 0)
	{
		for (int f = 0; f < vFace.size(); f++)  // ����ÿ����Ƭ
		{
			int n = vFace[f].vertex.size();    // ��Ķ�����
			glBegin(GL_POLYGON);
			for (int v = 0; v < n; v++)
			{
				int it = vFace[f].vertex[v].textIndex;
				int in = vFace[f].vertex[v].normIndex;
				int iv = vFace[f].vertex[v].vertIndex;
				if (vVertex[iv].y > head.y)
				{
					head.x = vVertex[iv].x;
					head.z = vVertex[iv].z;
					vFace.erase(vFace.begin() + f);
					break;
				}

				glTexCoord2f(vText[it].x, vText[it].y);
				glNormal3f(vNorm[in].x, vNorm[in].y, vNorm[in].z);
				glVertex3f(vVertex[iv].x, vVertex[iv].y, vVertex[iv].z);
			}
			glEnd();
		}
	}
	// û������
	else
	{
		for (int f = 0; f < vFace.size(); f++)  // ����ÿ����Ƭ
		{
			int n = vFace[f].vertex.size();    // ��Ķ�����
			glBegin(GL_POLYGON);
			for (int v = 0; v < n; v++)
			{
				int in = vFace[f].vertex[v].normIndex;
				int iv = vFace[f].vertex[v].vertIndex;
				if (vVertex[iv].y > head.y)
				{
					head.x = vVertex[iv].x;
					head.z = vVertex[iv].z;
					vFace.erase(vFace.begin() + f);
					break;
				}

				glNormal3f(vNorm[in].x, vNorm[in].y, vNorm[in].z);
				glVertex3f(vVertex[iv].x, vVertex[iv].y, vVertex[iv].z);
			}
			glEnd();
		}
	}
}