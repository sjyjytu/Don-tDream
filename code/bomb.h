#pragma once

#include<stdlib.h>
#include "mesh.h"
#include <time.h>

class Bomb :public Mesh
{
public:
	vector<vec3> fragment_v;
	bool has_initialize;
	bool ready_to_explode;
	int counter;
	Bomb();
	void before_explode();//炸弹裂开
	void explode();//炸弹爆炸
};

Bomb::Bomb()
{
	ready_to_explode = 0;
	has_initialize = 0;
	counter = 0;
	srand(unsigned(time(nullptr)));
}

inline void Bomb::before_explode()
{
	if (counter <= 1300)
	{
		float alpha = 1.2f;
		float beta = 0.06f;
		glPushMatrix();
		glRotatef((rand() % 2 - 0.5) * alpha, 1, 0, 0);
		glRotatef((rand() % 2 - 0.5) * alpha, 0, 1, 0);
		glRotatef((rand() % 2 - 0.5) * alpha, 0, 0, 1);
		glTranslatef((rand() % 2 - 0.5) * beta, (rand() % 2 - 0.5) * beta, (rand() % 2 - 0.5) * beta);
		drawMesh();
		glPopMatrix();
		counter++;
	}
	else
	{
		ready_to_explode = 1;
		counter = 0;
	}
}

void Bomb::explode()
{
	if (!has_initialize)
	{
		has_initialize = 1;
		float alpha = 0.01f;
		for (int v = 0; v < vVertex.size(); v++)
		{
			fragment_v.push_back({ alpha * (vVertex[v].x - 0), alpha * (vVertex[v].y - 0), alpha * (vVertex[v].z - 0) });
		}
	}
	if (counter <= 2000)
	{
		counter++;
		for (int v = 0; v < vVertex.size(); v++)  // 每个顶点都当作一个碎片
		{
			vVertex[v].x += fragment_v[v].x;
			vVertex[v].y += fragment_v[v].y;
			vVertex[v].z += fragment_v[v].z;

			glBegin(GL_QUADS);

			glVertex3f(vVertex[v].x - 0.05, vVertex[v].y - 0.05, vVertex[v].z);
			glVertex3f(vVertex[v].x + 0.05, vVertex[v].y - 0.05, vVertex[v].z);
			glVertex3f(vVertex[v].x + 0.05, vVertex[v].y + 0.05, vVertex[v].z);
			glVertex3f(vVertex[v].x - 0.05, vVertex[v].y + 0.05, vVertex[v].z);
			glEnd();
		}
	}

}