// MathFuncs.cpp
// source file containing vector functions that will
// be useful moving forward

#include "../inc/MathFuncs.h"

float GetLength(glm::vec3 v) {
	float x = v.x;
	float y = v.y;
	float z = v.z;

	return (sqrtf((x * x) + (y * y) + (z * z)));
}

void Normalize(glm::vec3 v) {
	float length = GetLength(v);

	v.x = v.x / length;
	v.y = v.y / length;
	v.z = v.z / length;
}

void Subtract(glm::vec3* result, glm::vec3 v1, glm::vec3 v2) {
	result->x = v2.x - v1.x;
	result->y = v2.y - v1.y;
	result->z = v2.z - v1.z;
}

void CrossProduct(glm::vec3* result, glm::vec3 v1, glm::vec3 v2) {
	result->x = v1.y * v2.z - v1.z * v2.y;
	result->y = v1.z * v2.x - v1.x * v2.z;
	result->z = v1.x * v2.y - v1.y * v2.x;
}

float DotProduct(glm::vec3 v1, glm::vec3 v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

void MultiplicationByScalar(glm::vec3* result, glm::vec3 v1, float scalar) {
	result->x = v1.x * scalar;
	result->y = v1.y * scalar;
	result->z = v1.z * scalar;
}