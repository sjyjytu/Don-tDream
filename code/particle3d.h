#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>
#include <vector>

using namespace std;

class my_vec3
{
public:
	my_vec3();
	my_vec3(float _x, float _y, float _z);
	~my_vec3();
	float x, y, z;
	my_vec3& operator=(const my_vec3& cls);
	void add(const my_vec3& cls);
};

class particle3d
{
public:
	particle3d();
	~particle3d();
	particle3d(float size,
		float _x, float _y, float _z,
		float _speed_x, float _speed_y, float _speed_z,
		float _acc_x, float _acc_y, float _acc_z,
		float _life, float* _color);

protected:
	float size;  //大小
	my_vec3 pos, speed, acc;  //位置、速度、加速度
	float life;  //生命
	float color[3];
	friend class emitter;
	virtual void show();
};

class chip_particle : public particle3d
{
public:
	chip_particle(float size,
		float _x, float _y, float _z,
		float _speed_x, float _speed_y, float _speed_z,
		float _acc_x, float _acc_y, float _acc_z,
		float angle_x, float angle_y, float angle_z,
		float theta_x, float theta_y, float theta_z,
		float _life, float* _color, int vertex_num);
	~chip_particle() {};
	void show();
private:
	my_vec3 angle, theta;  //角度、角速度
	int vertex_num;
	vector<my_vec3> vertexes;

};

class flame_particle : public particle3d
{
public:
	flame_particle(float size_x, float size_y, float size_z,
		float _x, float _y, float _z,
		float _speed_x, float _speed_y, float _speed_z,
		float _acc_x, float _acc_y, float _acc_z,
		float angle_x, float angle_y, float angle_z,
		float _life, GLuint _texture);
	~flame_particle() {};
	void show();
	void draw(GLuint texture);
private:
	my_vec3 flame_size;
	my_vec3 angle;  //角度
	GLuint texture;

};

class emitter {
	int particle_num;	//有多少个粒子
	particle3d** p;//管理所有粒子
	particle3d* (*f)(float, float, float); //初始化粒子的函数指针
public:
	float x, y, z; //发射器位置
	void emit(particle3d* (init)(float, float, float));
	void update();
	emitter(int _particle_num, float _x,
		float _y, float _z);
};