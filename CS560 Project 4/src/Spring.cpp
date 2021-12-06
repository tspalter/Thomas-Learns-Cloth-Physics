// Spring.cpp
// source file for the Spring object class
// represents a spring that exists between two mass points

#include "../inc/Spring.h"

Spring::Spring(Point* p1_, Point* p2_, float normalLength_) {
	p1 = p1_;
	p2 = p2_;

	// initial coefficient variables
	ks = 20;
	kd = 0.2f;

	normalLength = normalLength_;
}

Spring::~Spring() {

}

void Spring::Update(float ks_, float kd_) {
	ks = ks_;
	kd = kd_;

	// call force function with new coefficient values
	ApplySpringForce();
}

void Spring::DebugDraw() {
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw the line
	glBegin(GL_LINES);
		glVertex3f(p1->position->x, p1->position->y, p1->position->z);
		glVertex3f(p2->position->x, p2->position->y, p2->position->z);
	glEnd();
}

void Spring::ApplySpringForce() {
	// distance between both points in the spring
	// We could also create a temporary vec3, but
	// it's a bit easier access to the values we're 
	// looking for by using them separately
	float eX = p2->position->x - p1->position->x;
	float eY = p2->position->y - p1->position->y;
	float eZ = p2->position->z - p1->position->z;

	// use these variables to calculate the length
	float length = sqrt((eX * eX) + (eY * eY) + (eZ * eZ));

	// normalize the values
	eX = eX / length;
	eY = eY / length;
	eZ = eZ / length;

	// calculate velocity scalar values (dot product)
	float v1 = eX * p1->velocity->x + eY * p1->velocity->y + eZ * p1->velocity->z;
	float v2 = eX * p2->velocity->x + eY * p2->velocity->y + eZ * p2->velocity->z;

	// use these scalars to find the value of the spring force scalar
	float force = -ks * (normalLength - GetDistance()) - kd * (v1 - v2);

	// create values for the scalar force on the spring
	float fX = force * eX;
	float fY = force * eY;
	float fZ = force * eZ;

	// apply the forces to the two points
	// notice that the 2nd point receives the opposite force
	p1->AddForce(fX, fY, fZ);
	p2->AddForce(-fX, -fY, -fZ);
}

float Spring::GetDistance() {
	Vec3* dist = new Vec3();
	Subtract(dist, *(p1->position), *(p2->position));
	return dist->GetLength();
}