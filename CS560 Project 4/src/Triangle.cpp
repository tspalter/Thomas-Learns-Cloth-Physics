// Triangle.cpp
// header file for the Triangle object class
// handles individual triangles needed to build a full mesh
// a triangle can be thought of as having 3 Point objects

#include "../inc/Triangle.h"

Triangle::Triangle() {
	normal = new Vec3();
}

Triangle::~Triangle() {

}

void Triangle::SetTriangle(Point* p1, Point* p2, Point* p3) {
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
}

void Triangle::DebugDraw(int resolution, bool showWireframe, bool flatShade) {
	// set u and v values for texture coordinates
	float u = 1.0f / ((float)resolution - 1.0f);
	float v = 1.0f / ((float)resolution - 1.0f);

	// calculate the normal of the triangle
	CalculateNormal();

	// check if we are using the wireframe
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// check if we are using flat shading
	if (flatShade) {
		glNormal3f(normal->x, normal->y, normal->z);
	}

	// draw the triangle
	glBegin(GL_POLYGON);
		for (int i = 0; i < 3; i++) {
			// set texture coordinates
			glTexCoord2f(points[i]->posI * u, (resolution - 1.0f - points[i]->posJ) * v);
			// determine if we need to use the points normal (no flat shading)
			if (!flatShade) {
				glNormal3f(points[i]->normal->x, points[i]->normal->y, points[i]->normal->z);
			}
			glVertex3f(points[i]->position->x, points[i]->position->y, points[i]->position->z);
		}
	glEnd();
}

void Triangle::CalculateNormal() {
	Vec3* v1 = new Vec3();
	Vec3* v2 = new Vec3();

	// v1 and v2 are the differences between the position of point[0]
	// with the triangle's other two points
	Subtract(v1, *points[1]->position, *points[0]->position);
	Subtract(v2, *points[2]->position, *points[0]->position);

	// the cross product of v1 and v2 will give us the normal
	CrossProduct(normal, *v1, *v2);
}