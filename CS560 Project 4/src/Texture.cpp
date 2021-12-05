// Texture.cpp
// source file for the Texture object class

#include "../inc/Texture.h"

Texture::Texture() {
	ambient = glm::vec4(0.0f);
	diffuse = glm::vec4(0.0f);
	specular = glm::vec4(0.0f);
	shininess = 0.0f;
}

Texture::~Texture() { }

void Texture::SetAmbient(float r, float g, float b, float a) {
	ambient = glm::vec4(r, g, b, a);
}

void Texture::SetSpecular(float r, float g, float b, float a) {
	specular = glm::vec4(r, g, b, a);
}

void Texture::SetDiffuse(float r, float g, float b, float a) {
	diffuse = glm::vec4(r, g, b, a);
}

void Texture::SetShininess(float shine) {
	shininess = shine;
}