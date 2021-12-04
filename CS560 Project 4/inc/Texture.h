// Texture.h
// header file for the Texture object class

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glm/glm.hpp>

class Texture {
	// basic Texture variables
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	float shininess;

	// set functions
	void SetAmbient(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetShininess(float shine);

	// ctor and dtor
	Texture();
	virtual ~Texture();
};

#endif