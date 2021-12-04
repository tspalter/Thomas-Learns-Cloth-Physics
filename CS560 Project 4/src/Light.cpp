// Light.cpp
// source file for the Light object class

#include "../inc/Light.h"

Light::Light() {
	position = glm::vec4(0.0f);
	ambient = glm::vec3(0.0f);
	diffuse = glm::vec3(0.0f);
	specular = glm::vec3(0.0f);
}

Light::~Light() { }

void Light::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	position.w = 0.0f;
}

void Light::SetAmbient(float x, float y, float z) {
	ambient.x = x;
	ambient.y = y;
	ambient.z = z;
}

void Light::SetDiffuse(float x, float y, float z) {
	diffuse.x = x;
	diffuse.y = y;
	diffuse.z = z;
}

void Light::SetSpecular(float x, float y, float z) {
	specular.x = x;
	specular.y = y;
	specular.z = z;
}