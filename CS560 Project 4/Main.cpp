// main.cpp
// main file that displays window and compiles project


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdio.h>
#include "inc/Wire.h"
#include "inc/Light.h"
#include "inc/Texture.h"

#include <iostream>
#include <string>
#include <imgui.h>


// GLOBAL VARS
// resolution vars
#define MAX_RESOLUTION 80
#define MIN_RESOLUTION 20
#define RESOLUTION_DELTA 10

// determine the size of the wireframe
#define WIRE_SIZE 600

// sphere vars
#define SPHERE_RADIUS 100
#define SPHERE_SLICES 20

// refresh rate
#define REFRESH_RATE 10

// IDs used for callbacks and UI
#define MESH_RESOLUTION_ID 100
#define TEXTURE_ENABLED_ID 200
#define SHOW_WIRE_FRAME_ID 201
#define FLAT_SHADE_ID 202
#define SHOW_POINTS_ID 203
#define ENABLE_LIGHT_ID 300
#define LIGHT_LEVEL_ID 301
#define LIGHT_RED_COMPONENT_ID 302
#define LIGHT_GREEN_COMPONENT_ID 303
#define LIGHT_BLUE_COMPONENT_ID 304
#define GRAVITY_CONSTANT_ID 400
#define GRAVITY_DIRECTION_ID 401
#define KS_ID 402
#define KD_ID 403
#define POINT_RADIUS_ID 404
#define START_ID 500
#define PAUSE_ID 501
#define RESTART_ID 502
#define FIGURE_ID 600

// Some additional global vars
Wire* wireFrame;
Light* dirLight;
Texture* texture;

// Flags to show/hide elements
bool showPoints = true;
bool showTexture = true;
bool showWireframe = false;
bool flatShade = false;
bool lightEnabled = true;
bool figure = false;
bool isPaused = true;

// this defaults the system to 30x30 (900) mass points
// but can be adjusted by the user
int resolution = 30;

// orientation vars
float rotationX = 0.0f;
float rotationY = 0.0f;
float prevX = 0.0f;
float prevY = 0.0f;
bool mouseDown = false;

// Gravitational force variables
float gravForce = 10.0f;
glm::vec3* gravDirection;

// spring coefficients
float ks = 20.0f;
float kd = 0.2f;

float pointRadius = 5.0f;

unsigned int TextureFromFile(const char* path)
{
    // load and create a texture 
    unsigned int texture1;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture1;
}

int main() {

	return 0;
}