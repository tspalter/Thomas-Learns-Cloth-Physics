// MathFuncs.h
// header file containing vector functions that will
// be useful moving forward

#include <glm/glm.hpp>
#include <stdio.h>

// returns the length of a given vector
float GetLength(glm::vec3 v);
// normalize a given vector
void Normalize(glm::vec3 v);

// additional fuctions, the pointer to result is where the answer is stored
// subtract two vectors
void Subtract(glm::vec3* result, glm::vec3 v1, glm::vec3 v2);
// cross product
void CrossProduct(glm::vec3* result, glm::vec3 v1, glm::vec3 v2);
// dot product
float DotProduct(glm::vec3 v1, glm::vec3 v2);
// multiply a vector by a scalar value
void MultiplicationByScalar(glm::vec3* result, glm::vec3 v1, float scalar);