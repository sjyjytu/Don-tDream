#pragma once
#include <math.h>
#include <iostream>

using namespace std;

const float PI = 3.1415926f;

class Vector3f {
public:
	float x, y, z, * array;

	Vector3f(float x = 0.0, float y = 0.0, float z = 0.0)
		: x(x), y(y), z(z) {
		array = new float[3];
	}

	Vector3f operator * (const float lambda) {
		return Vector3f(x * lambda, y * lambda, z * lambda);
	}

	Vector3f operator + (const Vector3f& tempVector3f) {
		return Vector3f(x + tempVector3f.x, y + tempVector3f.y,
			z + tempVector3f.z);
	}

	Vector3f operator - (const Vector3f& tempVector3f) {
		return Vector3f(x - tempVector3f.x, y - tempVector3f.y,
			z - tempVector3f.z);
	}

	Vector3f operator * (const Vector3f& tempVector3f) {
		return Vector3f(y * tempVector3f.z - z * tempVector3f.y,
			z * tempVector3f.x - x * tempVector3f.z,
			x * tempVector3f.y - y * tempVector3f.x);
	}

	Vector3f& operator = (const Vector3f& tempVector3f) {
		x = tempVector3f.x;
		y = tempVector3f.y;
		z = tempVector3f.z;

		return (*this);
	}

	~Vector3f() {
		delete[] array;
	}

	float Modulus() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector3f& Unitization() {
		float modulus = Modulus();
		x /= modulus;
		y /= modulus;
		z /= modulus;

		return (*this);
	}

	float* operator () () {
		array[0] = x;
		array[1] = y;
		array[2] = z;
		return array;
	}

	friend ostream& operator << (ostream& out, const Vector3f& vec) {
		return out << vec.x << " " << vec.y << " " << vec.z;
	}
};
