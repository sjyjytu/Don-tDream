#pragma once

#include "vector"
#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include "algorithm"
#include "assert.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#pragma comment(lib, "glut.lib")

using namespace std;

struct vec3
{
	float x, y, z;
};

struct vec2
{
	float x, y;
};

class Vertex
{
public:
	int vertIndex;     // �˶����ڶ����б��е�����
	int normIndex;     // ����ķ�������
	int textIndex;     // �������������
};

class Face
{
public:
	vector<Vertex> vertex; // ����ͷ���������ɵ��б�

	Face() {}
	~Face() {}
};

class Mesh
{
protected:
	vector<vec3> vVertex;  // ��������
	vector<vec2> vText;    // ��������
	vector<vec3> vNorm;    // ��������
	vector<Face> vFace;    // ��Ƭ����

public:
	vec3 head;  //��¼��ߵĶ����yֵ
	Mesh() { head.x = 0; head.y = 0; head.z = 0; };
	~Mesh() {};

	bool readFile(const char* path);
	void drawMesh();
};
