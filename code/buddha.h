#pragma once

#include<stdlib.h>
#include "mesh.h"
#include <time.h>

class Buddha : public Mesh
{
public:
	bool reReadFile(const char* path);
};

bool Buddha::reReadFile(const char* path)
{
	ifstream file(path);
	if (!file)
	{
		cerr << "Error::ObjLoader, could not open obj file:"
			<< path << " for reading." << std::endl;
		return false;
	}

	vVertex.clear();
	vText.clear();
	vFace.clear();
	vNorm.clear();

	string line;
	while (getline(file, line))
	{
		if (line.substr(0, 2) == "vt")     // 顶点纹理坐标数据
		{
			istringstream s(line.substr(2));
			vec2 v;
			s >> v.x; s >> v.y;
			//cout << "vt " << v.x << " " << v.y << endl;
			v.y = -v.y;                     // 注意这里加载的dds纹理 要对y进行反转
			vText.push_back(v);
		}
		else if (line.substr(0, 2) == "vn") // 顶点法向量数据
		{
			istringstream s(line.substr(2));
			vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			//cout << "vn " << v.x << " " << v.y << " " << v.z << endl;
			vNorm.push_back(v);
		}
		else if (line.substr(0, 1) == "v")  // 顶点位置数据
		{
			istringstream s(line.substr(1));
			vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			//cout << "v " << v.x << " " << v.y << " " << v.z << endl;
			vVertex.push_back(v);
			if (v.y > head.y)
			{
				head.y = v.y;
			}
		}
		else if (line.substr(0, 1) == "f")  // 面数据
		{
			Face face;
			//cout << "f ";
			istringstream vtns(line.substr(1));
			string vtn;
			while (vtns >> vtn)             // 处理一行中多个顶点属性
			{
				Vertex vertex;
				replace(vtn.begin(), vtn.end(), '/', ' ');
				istringstream ivtn(vtn);
				if (vtn.find("  ") != string::npos) // 没有纹理数据，注意这里是2个空格
				{
					ivtn >> vertex.vertIndex
						>> vertex.normIndex;

					vertex.vertIndex--;     //使得下标从0开始
					vertex.normIndex--;
				}
				else
				{
					ivtn >> vertex.vertIndex
						>> vertex.textIndex
						>> vertex.normIndex;

					//cout <<  vertex.vertIndex << "/" << vertex.textIndex << "/" << vertex.normIndex << " ";
					vertex.vertIndex--;
					vertex.textIndex--;
					vertex.normIndex--;
				}
				face.vertex.push_back(vertex);
			}
			vFace.push_back(face);
			//cout << endl;
		}
		else if (line[0] == '#')            // 注释忽略
		{
		}
		else
		{
			// 其余内容 暂时不处理
		}
	}

	return true;
}