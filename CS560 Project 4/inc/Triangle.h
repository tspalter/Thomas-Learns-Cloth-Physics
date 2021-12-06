// Triangle.h
// header file for the Triangle object class
// handles individual triangles needed to build a full mesh

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdio.h>
#include "Point.h"

class Triangle {
public:
	// Pointers to the points of the individual triangle
	Point* points[3];
	// normal vec
	Vec3* normal;

	// ctor and dtor
	Triangle();
	virtual ~Triangle();

	// set triangle points
	void SetTriangle(Point* p1, Point* p2, Point* p3);
	// calculate the normal of the Triangle
	void CalculateNormal();
	// debug draw
	void DebugDraw(int resolution, bool showWireframe, bool flatShade);
	
};


#endif