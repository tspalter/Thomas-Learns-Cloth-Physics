// Point.h
// header file for the Point object class
// designed to represent a given mass point

#include "../inc/Point.h"

float FRAMERATE = 60.0f;

Point::Point() {
	m = 0.0f;
	totalForce = new Vec3();
	velocity = new Vec3();
	normal = new Vec3();
	radius = 5;
	numOfAdjTriangles = 0;
}

Point::~Point() {
	delete totalForce;
	delete velocity;
	delete normal;
	delete position;
	delete prevPosition;
}

void Point::SetPosition(float pX, float pY, float pZ, int i, int j) {
	// position relative to the mesh index
	posI = i;
	posJ = j;

	// position variables
	position = new Vec3(pX, pY, pZ);
	prevPosition = new Vec3(pX, pY, pZ);
}

void Point::ClearForces() {
	totalForce->x = 0.0f;
	totalForce->y = 0.0f;
	totalForce->z = 0.0f;
}

void Point::AddForce(float mass, float x, float y, float z) {
	totalForce->x += mass * x;
	totalForce->y += mass * y;
	totalForce->z += mass * z;
}

void Point::DebugDraw() {
	// draw point based on the point's radius
	glPointSize((int)radius);

	// check if the point is anchored
	if (isFixed)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);

	// draw the point
	glBegin(GL_POINTS);
		glVertex3f(position->x, position->y, position->z);
	glEnd();
}

Vec3* Point::VerletIntegrationToPosition() {
	// create vector for the resulting position
	Vec3* nextPos = new Vec3();

	// use Verlet integration to calculate each vector value
	// next = 2*curr - prev + force*dt
	nextPos->x = (2 * position->x) - prevPosition->x + totalForce->x / m * 0.1f * 0.1f;
	nextPos->y = (2 * position->y) - prevPosition->y + totalForce->y / m * 0.1f * 0.1f;
	nextPos->z = (2 * position->z) - prevPosition->z + totalForce->z / m * 0.1f * 0.1f;

	// now return the new position
	return nextPos;
}

Vec3* Point::RK2() {
	// create vector for the resulting position and velocity values that we'll need
	Vec3* nextPos = new Vec3();
	Vec3* nextVelocity = new Vec3();
	Vec3* midVelocity = new Vec3();

	// find the value of the explicit next velocity using explicity Euler method
	nextVelocity->x = 10 * velocity->x + 10 * totalForce->x * 0.1f * 0.1f;
	nextVelocity->y = 10 * velocity->y + 10 * totalForce->y * 0.1f * 0.1f;
	nextVelocity->z = 10 * velocity->z + 10 * totalForce->z * 0.1f * 0.1f;

	// determine the "mid" velocity as an average of the current velocity and the explicit next velocity
	midVelocity->x = (velocity->x + nextVelocity->x) / 2;
	midVelocity->y = (velocity->x + nextVelocity->y) / 2;
	midVelocity->z = (velocity->x + nextVelocity->z) / 2;

	// finally, get the next position based on the 2nd order Runge-Kutta method
	nextPos->x = (position->x) + midVelocity->x * 0.1f * 0.1f;
	nextPos->y = (position->y) + midVelocity->y * 0.1f * 0.1f;
	nextPos->z = (position->z) + midVelocity->z * 0.1f * 0.1f;

	delete midVelocity;
	delete nextVelocity;

	return nextPos;
}

void Point::Update(int sphereRadius, Vec3 objPos, bool useRungeKutta, float mass) {
	m = mass;
	// update velocity value
	velocity->x = totalForce->x * 0.1f;
	velocity->y = totalForce->y * 0.1f;
	velocity->z = totalForce->z * 0.1f;

	// set up temp positions to save for prev position
	float tempX = position->x;
	float tempY = position->y;
	float tempZ = position->z;

	// update the positions
	Vec3* nextPos = new Vec3();
	if (useRungeKutta) {
		nextPos = RK2();
	}
	else {
		nextPos = VerletIntegrationToPosition();
	}

	if (!isFixed) {
		position->x = nextPos->x;
		position->y = nextPos->y;
		position->z = nextPos->z;
	}

	// set prev position
	prevPosition->x = tempX;
	prevPosition->y = tempY;
	prevPosition->z = tempZ;

	delete nextPos;

	// now check for collision
	CheckCollision(sphereRadius, objPos);
}

void Point::CheckCollision(int sphereRadius, Vec3 objPos) {
	float ptDist; // used to compare radius to point-sphere distance
	Vec3* dist = new Vec3(); // represents difference between point and sphere center
	Subtract(dist, *position, objPos);
	ptDist = dist->GetLength() - (sphereRadius + radius); // counts as a sphere-sphere collision

	// normalize distance
	dist->Normalize();

	Vec3* p = new Vec3(); // to determine where point should be if collision is detected
	MultiplicationByScalar(p, *dist, ptDist);

	// check for collision, adjust position if so
	if (ptDist < 0) {
		position->x += p->x;
		position->y += p->y;
		position->z += p->z;
	}

	delete p;
	delete dist;
}