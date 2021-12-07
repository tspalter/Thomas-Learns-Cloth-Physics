// Point.h
// header file for the Point object class
// designed to represent a given mass point

#ifndef POINT_H
#define POINT_H

#include <Windows.h>
#include <GL/glut.h>
#include "MathFuncs.h"

class Point {
public:
	// point mass
	float m;

	// index variables for the point in the mesh of the cloth
	int posI, posJ;
	// radius of the point
	float radius;

	// variables dealing with triangles
	int numOfAdjTriangles;
	int adjTriangles[6]; // all triangles touching the point, up to 6 total

	// vector pointer values
	Vec3* position;
	Vec3* prevPosition;
	Vec3* totalForce;
	Vec3* velocity;
	Vec3* normal;
	// check if point is anchored
	bool isFixed;

	// set position of point at index [i][j]
	void SetPosition(float pX, float pY, float pZ, int i, int j);

	// ctor and dtor
	Point();
	virtual ~Point();

	// set accumulated forces to 0
	void ClearForces();
	// add a force to the point's current force
	void AddForce(float mass, float x, float y, float z);
	// Debug Draw
	void DebugDraw();

	// Verlet Integration function
	Vec3* VerletIntegrationToPosition();

	// 2nd Order Runge-Kutta function
	Vec3* RK2();

	// Update point values
	void Update(int sphereRadius, Vec3 objPos, bool useRungeKutta, float mass);

	// Collision check with a sphere object
	void CheckCollision(int radius, Vec3 objPos);

};

// get the linear momentum of a given mass point
void LinearMomentum(Vec3* result, Point* p1);
// get the angular momentum of a given mass point
void AngularMomentum(Vec3* result, Point* p1);

#endif