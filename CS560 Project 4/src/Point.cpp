// Point.h
// header file for the Point object class
// designed to represent a given mass point

#include "../inc/Point.h"

float FRAMERATE = 60.0f;

Point::Point() {
	totalForce = new glm::vec3();
	velocity = new glm::vec3();
	normal = new glm::vec3();
	radius = 5;
	numOfAdjTriangles = 0;
}

Point::~Point() { }

void Point::SetPosition(float pX, float pY, float pZ, int i, int j) {
	// position relative to the mesh index
	posI = i;
	posJ = j;

	// position variables
	position = new glm::vec3(pX, pY, pZ);
	prevPosition = new glm::vec3(pX, pY, pZ);
}

void Point::ClearForces() {
	totalForce->x = 0.0f;
	totalForce->y = 0.0f;
	totalForce->z = 0.0f;
}

void Point::AddForce(float x, float y, float z) {
	totalForce->x += x;
	totalForce->y += y;
	totalForce->z += z;
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

glm::vec3* Point::VerletIntegrationToPosition() {
	// create vector for the resulting position
	glm::vec3* nextPos = new glm::vec3();

	// use Verlet integration to calculate each vector value
	// next = 2*curr - prev + force*dt
	nextPos->x = (2 * position->x) - prevPosition->x + totalForce->x * (1.0f / FRAMERATE);
	nextPos->y = (2 * position->y) - prevPosition->y + totalForce->y * (1.0f / FRAMERATE);
	nextPos->z = (2 * position->z) - prevPosition->z + totalForce->z * (1.0f / FRAMERATE);

	// now return the new position
	return nextPos;
}

void Point::Update(int sphereRadius, glm::vec3 objPos) {
	// update velocity value
	velocity->x = totalForce->x * 0.1f;
	velocity->y = totalForce->y * 0.1f;
	velocity->z = totalForce->z * 0.1f;

	// set up temp positions to save for prev position
	float tempX = position->x;
	float tempY = position->y;
	float tempZ = position->z;

	// update the positions
	glm::vec3* nextPos = VerletIntegrationToPosition();

	if (!isFixed) {
		position->x = nextPos->x;
		position->y = nextPos->y;
		position->z = nextPos->z;
	}

	// set prev position
	prevPosition->x = tempX;
	prevPosition->y = tempY;
	prevPosition->z = tempZ;

	// now check for collision
	CheckCollision(sphereRadius, objPos);
}

void Point::CheckCollision(int sphereRadius, glm::vec3 objPos) {
	float ptDist; // used to compare radius to point-sphere distance
	glm::vec3* dist = new glm::vec3(); // represents difference between point and sphere center
	Subtract(dist, *position, objPos);
	ptDist = GetLength(*dist) - (sphereRadius + radius); // counts as a sphere-sphere collision

	// normalize distance
	Normalize(*dist);

	glm::vec3* p = new glm::vec3(); // to determine where point should be if collision is detected
	MultiplicationByScalar(p, *dist, ptDist);

	// check for collision, adjust position if so
	if (ptDist < 0) {
		position->x += p->x;
		position->y += p->y;
		position->z += p->z;
	}
}