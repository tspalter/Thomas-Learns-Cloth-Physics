// MathFuncs.cpp
// source file containing vector functions that will
// be useful moving forward

#include "../inc/MathFuncs.h"

void Subtract(Vec3* result, Vec3 v1, Vec3 v2) {
	result->x = v2.x - v1.x;
	result->y = v2.y - v1.y;
	result->z = v2.z - v1.z;
}

void CrossProduct(Vec3* result, Vec3 v1, Vec3 v2) {
	result->x = v1.y * v2.z - v1.z * v2.y;
	result->y = v1.z * v2.x - v1.x * v2.z;
	result->z = v1.x * v2.y - v1.y * v2.x;
}

float DotProduct(Vec3 v1, Vec3 v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

void MultiplicationByScalar(Vec3* result, Vec3 v1, float scalar) {
	result->x = v1.x * scalar;
	result->y = v1.y * scalar;
	result->z = v1.z * scalar;
}

void LinearMomentum(Vec3* result, Point p1) {
	result->x = p1.m * p1.velocity->x;
	result->y = p1.m * p1.velocity->y;
	result->z = p1.m * p1.velocity->z;
}

void AngularMomentum(Vec3* result, Point p1) {
	result->x = p1.m * p1.velocity->x * p1.radius;
	result->y = p1.m * p1.velocity->y * p1.radius;
	result->z = p1.m * p1.velocity->z * p1.radius;
}