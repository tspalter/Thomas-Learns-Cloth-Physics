// Spring.h
// header file for the Spring object class
// represents a spring that exists between two mass points

#ifndef SPRING_H
#define SPRING_H

#include "Point.h"

class Spring {
public:
	// two points connected by the spring
	Point* p1;
	Point* p2;

	// important vars
	float ks; // hook coefficient
	float kd; // elasticity coefficient
	float normalLength; // resting distance of the spring


	// ctor and dtor
	Spring(Point* p1_, Point* p2_, float normalLength_);
	virtual ~Spring();

	// update based on hook and elasticity coefficients
	void Update(float ks_, float kd_);
	// debug draw
	void DebugDraw();
	// application of force by the spring
	void ApplySpringForce();
	// find the distance between the spring's two points
	float GetDistance();
};

#endif
