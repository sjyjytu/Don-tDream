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
	int vertIndex;     // 此顶点在顶点列表中的索引
	int normIndex;     // 顶点的法线索引
	int textIndex;     // 顶点的纹理索引
};

class Face
{
public:
	vector<Vertex> vertex; // 顶点和法线索引组成的列表

	Face() {}
	~Face() {}
};

class Mesh
{
protected:
	vector<vec3> vVertex;  // 顶点数组
	vector<vec2> vText;    // 纹理数组
	vector<vec3> vNorm;    // 法线数组
	vector<Face> vFace;    // 面片数组

public:
	vec3 head;  //记录最高的顶点的y值
	Mesh() { head.x = 0; head.y = 0; head.z = 0; };
	~Mesh() {};

	bool readFile(const char* path);
	void drawMesh();
};
