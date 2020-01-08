#include<stdlib.h>
#include "particle3d.h"

particle3d::particle3d()
{
}

particle3d::~particle3d()
{
}

particle3d::particle3d(float _size, float _x, float _y, float _z, float _speed_x, float _speed_y, float _speed_z, float _acc_x, float _acc_y, float _acc_z, float _life, float* _color)
{
	size = _size;
	pos = my_vec3(_x, _y, _z);
	speed = my_vec3(_speed_x, _speed_y, _speed_z);
	acc = my_vec3(_acc_x, _acc_y, _acc_z);
	life = _life;
	color[0] = _color[0];
	color[1] = _color[1];
	color[2] = _color[2];
}

void particle3d::show(Mesh &block)
{
	if (life > 0)
	{
		glColor3f(color[0], color[1], color[2]);
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glutSolidSphere(0.2, 5, 5);
		glPopMatrix();

		pos.add(speed);

		speed.add(acc);

		life -= 0.2f;
		glColor3f(1, 1, 1);
	}
}

void emitter::emit(particle3d* (init)(float, float, float))
{
	for (int i = 0; i < particle_num; i++) {
		f = init;
		p[i] = f(x, y, z);
	}
}

void emitter::update() {
	for (int i = 0; i < particle_num; i++) {
		p[i]->show(block);
		if (p[i]->life <= 0) {
			delete p[i];
			p[i] = f(x, y, z);
		}
	}
}

emitter::emitter(int _particle_num, float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	particle_num = _particle_num;
	p = new particle3d * [_particle_num];
}


flame_particle::flame_particle(float size_x, float size_y, float size_z, float _x, float _y, float _z, float _speed_x, float _speed_y, float _speed_z, float _acc_x, float _acc_y, float _acc_z, float angle_x, float angle_y, float angle_z, float _life, GLuint _texture)
{
	flame_size = my_vec3(size_x, size_y, size_z);
	pos = my_vec3(_x, _y, _z);
	speed = my_vec3(_speed_x, _speed_y, _speed_z);
	acc = my_vec3(_acc_x, _acc_y, _acc_z);
	life = _life;
	texture = _texture;
	angle = my_vec3(angle_x, angle_y, angle_z);
}

void flame_particle::show(Mesh &block)
{
	if (life > 0)
	{
		glDepthMask(GL_FALSE);
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glRotatef(angle.x, 1, 0, 0);
		glRotatef(angle.y, 0, 1, 0);
		glRotatef(angle.z, 0, 0, 1);
		glScalef(flame_size.x, flame_size.y, flame_size.z);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);  //—°‘ÒŒ∆¿Ìtexture[status]       
		block.drawMesh();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		pos.add(speed);

		speed.add(acc);

		life -= 0.2f;
		glDepthMask(GL_TRUE);
	}
}

my_vec3::my_vec3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

my_vec3::my_vec3(float _x, float _y, float _z) :x(_x), y(_y), z(_z)
{
}

my_vec3::~my_vec3()
{
}

my_vec3& my_vec3::operator=(const my_vec3& cls)
{
	// ±‹√‚◊‘∏≥÷µ
	if (this != &cls)
	{
		// ±‹√‚ƒ⁄¥Ê–π¬∂
		x = cls.x;
		y = cls.y;
		z = cls.z;
	}
	return *this;
}

void my_vec3::add(const my_vec3& cls)
{
	x += cls.x;
	y += cls.y;
	z += cls.z;
}