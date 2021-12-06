// Vector.h
// header file for the Vec3 object class
// Created this with necessary functions, for whatever reason, my program
// was struggling with using glm::vec3, so I'm using a more hard-coded method

#include "../inc/Vector.h"

Vec3::Vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3::Vec3(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

Vec3::~Vec3() { }

float Vec3::GetLength() {
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	return sqrtf(x2 + y2 + z2);
}

void Vec3::Normalize() {
	float length = GetLength();

	x = x / length;
	y = y / length;
	z = z / length;
}