// Point.h
// header file for the Point object class
// designed to represent a given mass point

#ifndef POINT_H
#define POINT_H

#include <glm/glm.hpp>

class Point {
public:
	// mass of point
	float mass;

	// index variables for the point in the mesh of the cloth
	int posI, posJ;
	// radius of the point
	float radius;

	// variables dealing with triangles
	int numOfAdjTriangles;
	int adjTriangles[6]; // all triangles touching the point, up to 6 total

	// vector pointer values
	glm::vec3* position;
	glm::vec3* prevPosition;
	glm::vec3* totalForce;
	glm::vec3* velocity;
	glm::vec3* normal;
	// check if point is anchored
	bool isFixed;

	// set function
	void SetPosition(float pX, float pY, float pZ);

	// ctor and dtor
	Point();
	virtual ~Point();

	// set accumulated forces to 0
	void ClearForces();
	// add a force to the point's current force
	void AddForce(float x, float y, float z);
	// Debug Draw
	void DebugDraw();

	// Verlet Integration function
	glm::vec3* VerletIntegrationToPosition();

	// Update point values
	void Update(int sphereRadius, glm::vec3 objPos);

	// Collision check
	void CheckCollision(int radius, glm::vec3 objPos);

};

#endif