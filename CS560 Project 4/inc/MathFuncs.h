// MathFuncs.h
// header file containing vector functions that will
// be useful moving forward

#include <glm/glm.hpp>
#include "Vector.h"
#include <stdio.h>

// additional fuctions, the pointer to result is where the answer is stored
// subtract two vectors
void Subtract(Vec3* result, Vec3 v1, Vec3 v2);
// cross product
void CrossProduct(Vec3* result, Vec3 v1, Vec3 v2);
// dot product
float DotProduct(Vec3 v1, Vec3 v2);
// multiply a vector by a scalar value
void MultiplicationByScalar(Vec3* result, Vec3 v1, float scalar);