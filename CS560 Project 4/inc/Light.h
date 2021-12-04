// Light.h
// header for the Light class that creates a Light object

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
	// basic variables for light
	glm::vec4 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// set functions
	void SetPosition(float x, float y, float z);
	void SetAmbient(float x, float y, float z);
	void SetDiffuse(float x, float y, float z);
	void SetSpecular(float x, float y, float z);

	// ctor and dtor
	Light();
	virtual ~Light();
};



#endif