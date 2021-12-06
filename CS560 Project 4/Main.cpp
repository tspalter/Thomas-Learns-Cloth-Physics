// main.cpp
// main file that displays window and compiles project


// #include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdio.h>
#include "inc/Wire.h"
#include "inc/Light.h"
#include "inc/Texture.h"

#include <iostream>
#include <string>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>


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
bool showTriangles = true;
bool showSprings = false;
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
Vec3* gravDirection;

// spring coefficients
float ks = 20.0f;
float kd = 0.2f;

float pointRadius = 5.0f;

// Camera vars
glm::vec4 globalAmbient = glm::vec4(0.0f);
glm::vec3 eye = glm::vec3(0.0f, 0.0f, 1000.0f);
glm::vec4 lookAt = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

int window;

// these must be float arrays rather than mat4 vars
// for GLUT functions
float viewRotation[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
float lightRotation[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

// object position
Vec3* objPos = new Vec3();

float fovy = 45.0f;
float dNear = 100.0f;
float dFar = 2000.0f;

float intensity = 1.0f;

void LoadTextureFromFile(const char* path)
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
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 480, 480, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Resize(int w, int h) {
    // resize the projected perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, (double)w / (double)h, dNear, dFar);
    // set viewport
    glViewport(0, 0, w, h);
}

// display function for GLUT
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // handle the light
    glMultMatrixf(lightRotation);
    float lightPos[4] = {
        dirLight->position.x,
        dirLight->position.y,
        dirLight->position.z,
        dirLight->position.w
    };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // handle LookAt function
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z, lookAt.x, lookAt.y, lookAt.z, Up.x, Up.y, Up.z);

    // handle view rotation
    glMultMatrixf(viewRotation);

    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // enable features based on flags
    // triangles, also handles texture
    if (showTriangles) {
        wireFrame->DrawTriangles(showWireframe, flatShade);
    }
    // lighting
    if (lightEnabled) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    // mass points
    if (showPoints) {
        wireFrame->DrawPoints();
    }
    // call diffuse for textures
    float lightDiffuse[3] = {
        dirLight->diffuse.x,
        dirLight->diffuse.y,
        dirLight->diffuse.z
    };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    // textures
    if (showTexture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
    }
    else {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    }
    // flat shading
    if (flatShade) {
        glShadeModel(GL_FLAT);
    }
    else {
        glShadeModel(GL_SMOOTH);
    }
    // springs
    if (showSprings) {
        wireFrame->DrawSprings();
    }
    // push matrix for the position and drawing of the sphere
    glPushMatrix();
    glTranslatef(objPos->x, objPos->y, objPos->z);
    glutSolidSphere(SPHERE_RADIUS, SPHERE_SLICES, SPHERE_SLICES); // draws a sphere
    glPopMatrix();

    glutSwapBuffers();
}

// GLUT init function
void init() {
    // initialize rotations to flat
    rotationX = 0.0f;
    rotationY = 0.0f;

    // set gravity direction to down
    gravDirection = new Vec3(0.0f, -1.0f, 0.0f);

    // set up the directional light values
    dirLight = new Light();
    dirLight->SetPosition(0.0f, 300.0f, 100.0f);
    dirLight->SetAmbient(0.0f, 0.0f, 0.0f);
    dirLight->SetDiffuse(0.8f, 0.0f, 0.8f);
    dirLight->SetSpecular(0.0f, 0.8f, 0.0f);

    // set up texture values
    texture = new Texture();
    texture->SetAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    texture->SetDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
    texture->SetSpecular(0.01f, 0.01f, 0.01f, 1.0f);
    texture->SetShininess(32);

    // enable normalizing and set up GLUT functions
    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    LoadTextureFromFile("Mantel.ppm");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // set up directional light values to be used by GLUT
    float lightPos[4] = {
        dirLight->position.x,
        dirLight->position.y,
        dirLight->position.z,
        dirLight->position.w
    };
    float lightAmb[3] = {
        dirLight->ambient.x,
        dirLight->ambient.y,
        dirLight->ambient.z
    };
    float lightSpec[3] = {
        dirLight->specular.x,
        dirLight->specular.y,
        dirLight->specular.z
    };
    float lightDiff[3] = {
        dirLight->diffuse.x,
        dirLight->diffuse.y,
        dirLight->diffuse.z
    };
    // now implement GLUT light with our directional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);

    float globalAmb[4] = {
        globalAmbient.x,
        globalAmbient.y,
        globalAmbient.z,
        globalAmbient.w
    };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);
}

void MouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // save data to allow mouse to rotate
        mouseDown = true;
        prevX = x - rotationY;
        prevY = y - rotationX;
    }
    else {
        mouseDown = false;
    }
}

void MouseMotionCallback(int x, int y) {
    if (mouseDown) {
        rotationX = y - prevY;
        rotationY = x - prevX;
        glutPostRedisplay();
    }
}

// initialize the wireframe to set up points, triangles, and springs
void InitWireframe() {
    wireFrame = new Wire(resolution, WIRE_SIZE);
}

// check for control callback change certain values
void ControlCallback(int control) {
    if (control == MESH_RESOLUTION_ID) {
        InitWireframe();
    }
    else if (control == LIGHT_LEVEL_ID) {
        // set new diffuse value
        float diff1 = dirLight->diffuse.x + intensity;
        float diff2 = dirLight->diffuse.y + intensity;
        float diff3 = dirLight->diffuse.z + intensity;

        dirLight->SetDiffuse(diff1, diff2, diff3);
    }
    // start simulation
    else if (control == START_ID) {
        isPaused = false;
    }
    // pause simulation
    else if (control == PAUSE_ID) {
        isPaused = true;
    }
    // restart simulation
    else if (control == RESTART_ID) {
        InitWireframe();
    }

    glutPostRedisplay();
}

// values that change on key press
void KeyFunctions(unsigned char key, int x, int y) {
    // simple input controls
    if (key == 'a' || key == 'A') // left
        eye.x -= 50.0f;
    if (key == 'd' || key == 'D') // right
        eye.x += 50.0f;
    if (key == 's' || key == 'S') // down
        eye.y -= 50.0f;
    if (key == 'w' || key == 'W') // up
        eye.y += 50.0f;
    if (key == 'q' || key == 'Q') // out
        eye.z += 50.0f;
    if (key == 'e' || key == 'E') // in
        eye.z -= 50.0f;
    if (key == 'p' || key == 'P') // toggle points
        showPoints = !showPoints;
    if (key == 't' || key == 'T') // toggle texture
        showTexture = !showTexture;
    if (key == 'r' || key == 'R') // toggle wireframe
        showWireframe = !showWireframe;
    if (key == 'f' || key == 'F') // toggle flat shade
        flatShade = !flatShade;
    if (key == 'b' || key == 'B') // toggle springs
        showSprings = !showSprings;
    if (key == '1')               // start simulation
        ControlCallback(START_ID);
    if (key == '2')               // pause simulation
        ControlCallback(PAUSE_ID);
    if (key == '3')               // restart simulation
        ControlCallback(RESTART_ID);
    if (key == '+') { // increase resolution if possible
        if (resolution < MAX_RESOLUTION) {
            resolution += RESOLUTION_DELTA;
            InitWireframe();
        }
    }
    if (key == '-') { // decrease resolution if possible
        if (resolution > MIN_RESOLUTION) {
            resolution -= RESOLUTION_DELTA;
            InitWireframe();
        }
    }

    glutPostRedisplay();
}

void Update(int i) {
    // check if system should be paused
    if (!isPaused) {
        wireFrame->Update(SPHERE_RADIUS, gravForce, *gravDirection, ks, kd, pointRadius, *objPos);
        glutPostRedisplay();
    }

    // apply GLUT timer function and call recursively
    glutTimerFunc(20, Update, 1);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(800, 600);

    window = glutCreateWindow("CS560 Project 4");

    init();

    // call all GLUT functions
    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);
    glutMouseFunc(MouseCallback);
    glutKeyboardFunc(KeyFunctions);
    glutTimerFunc(20, Update, 1);
    glutMotionFunc(MouseMotionCallback);
    

    glutMotionFunc(MouseMotionCallback);

    InitWireframe();

    glutMainLoop();

	return 0;
}