// Vector.h
// header file for the Vec3 object class
// Created this with necessary functions, for whatever reason, my program
// was struggling with using glm::vec3, so I'm using a more hard-coded method

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdio.h>

class Vec3 {
public:
	// 3 vector values
	float x;
	float y;
	float z;

	// ctors and dtor
	Vec3();
	Vec3(float x_, float y_, float z_);
	virtual ~Vec3();

	// Find the scalar length of the vector
	float GetLength();
	// Normalize the vector
	void Normalize();

};



#endif