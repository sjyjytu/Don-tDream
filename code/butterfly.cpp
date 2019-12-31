#include <stdlib.h>  
#include "butterfly.h"
#include <time.h>
#include <iostream>

spline* butterfly::line;
int butterfly::texture[3];
butterfly::butterfly(int i)
{
	id = i;
}

void butterfly::show()
{

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef((spinz), 0.0f, 0.0f, 1.0f);
	glScaled(0.2, 0.2, 0.2);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, flap);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, flap);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void butterfly::update()
{
	//printf("%d:%f %f\n",id, x, y);
	if (index < line->size())index++;
	spinz += spinzi;
	flap += fi;
	x = line->getX(index) + dx;
	y = line->getY(index) + dy;
	if (index >= line->size()) {
		set(0);
	}
	/*if (index >= 100) {
		set(0);
	}*/

	if ((flap > 1.0f) || (flap < -1.0f))
	{
		fi = -fi;
	}

}

void butterfly::set(int _index)
{
	tex = texture[rand() % 3];
	//z = rand() % 20  - 10;
	z = (rand() % 20) / 10.0;
	spinzi = (rand() % 10000) / 5000.0f - 1.0f;
	flap = 0.0f;
	fi = 0.05f + (rand() % 100) / 1000.0f;
	index = _index;
	x = line->getX(index);
	y = line->getY(index);
	dx = (rand() % 10 - 5) * 0.1;
	dy = (rand() % 10 - 5) * 0.1;
}

butterflyManager::butterflyManager(int* tex)
{
	isDraw = false;
	genPath();
	isGen = false;
	butterfly butt(0);
	obj.push_back(butt);
	int id;

	for (int i = 0; i < 3; i++) {
		butterfly::texture[i] = tex[i];
	}
	for (int i = 0; i < obj.size(); i++) {
		id = rand() % 3;
		obj[i].set(0);
	}
}

void butterflyManager::show()
{
	if (!isDraw)return;
	static int count[20] = { 0 };
	static int count2 = 0;
	count2++;
	for (int i = 0; i < obj.size(); i++) {
		count[i]++;
		obj[i].show();
		if (count[i] == 80) {
			count[i] = 0;
			obj[i].update();
		}
		if (count2 == 100 && obj.size() < 20) {

			count2 = 0;
			//		printf("size = %d\n", obj.size());
			butterfly butt(obj.size());
			butt.set(0);
			obj.push_back(butt);
		}
	}
}

void butterflyManager::genPath()
{
	p = new point[20];
	/*p[0].setPoint(-100, 5);
	p[1].setPoint(-90, 7);
	p[2].setPoint(-80, 3);
	p[3].setPoint(-70, 0);
	p[4].setPoint(-60, 2);
	p[5].setPoint(-50, 4);
	p[6].setPoint(-40, 5);
	p[7].setPoint(-30, 7);
	p[8].setPoint(-20, 5);
	p[9].setPoint(-10, 8);
	p[10].setPoint(0, 5);
	p[11].setPoint(10, 5);
	p[12].setPoint(20, 8);
	p[13].setPoint(30, 9);
	p[14].setPoint(40, 10);
	p[15].setPoint(50, 11);
	p[16].setPoint(60, 13);
	p[17].setPoint(70, 14);
	p[18].setPoint(80, 13);
	p[19].setPoint(90, 10);*/
	float t = 0.2;
	p[0].setPoint(0 * t, 5 * t);
	p[1].setPoint(-10 * t, 7 * t);
	p[2].setPoint(-15 * t, 3 * t);
	p[3].setPoint(-20 * t, 0 * t);
	p[4].setPoint(-25 * t, 2 * t);
	p[5].setPoint(-30 * t, 4 * t);
	p[6].setPoint(-35 * t, 5 * t);
	p[7].setPoint(-40 * t, 7 * t);
	p[8].setPoint(-45 * t, 5 * t);
	p[9].setPoint(-50 * t, 8 * t);
	p[10].setPoint(-55 * t, 5 * t);
	p[11].setPoint(-60 * t, 5 * t);
	p[12].setPoint(-65 * t, 8 * t);
	p[13].setPoint(-70 * t, 9 * t);
	p[14].setPoint(-75 * t, 10 * t);
	p[15].setPoint(-80 * t, 11 * t);
	p[16].setPoint(-85 * t, 13 * t);
	p[17].setPoint(-90 * t, 14 * t);
	p[18].setPoint(-95 * t, 13 * t);
	p[19].setPoint(-100 * t, 10 * t);
	line = new spline(p, 20, 20, 0.6);
	butterfly::line = line;
}