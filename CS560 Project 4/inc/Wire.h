// Wire.h
// header file for the Wire object class
// represents all of the points, springs, and triangles in the wireframe

#ifndef WIRE_H
#define WIRE_H

#include <Windows.h>
#include <GL/glut.h>
#include "Point.h"
#include "Triangle.h"
#include "Spring.h"

class Wire {
public:
	// index of points
	Point** points;
	int numPoints;
	// index of triangles
	Triangle** triangles;
	int numTriangles;
	// index of springs
	Spring** springs;
	int numSprings;

	// other important vars
	float delta;
	int resolution;

	// ctor and dtor
	Wire(int resolution_, int size);
	virtual ~Wire();

	// add a new point to the wire at index [i, j]
	void AddPoint(Point* p, int i, int j);
	// generates the triangles at the specified resolution
	void GenerateTriangles(int resolution);
	
	// debug draw functions
	void DrawPoints();
	void DrawTriangles(bool showWireframe, bool flatShade);
	void DrawSprings();

	// update the wire based on gravity
	void Update(int sphereRadius, float gravForce, Vec3 gravDirection, float ks, float kd, float pointRadius, Vec3 objPos, bool useRungeKutta, float mass);
	// generates the springs of the wire object
	void GenerateSprings();
	// calculates the normal of a specific point at column c and row r
	void CalculatePointNormal(int c, int r);

};

#endif
