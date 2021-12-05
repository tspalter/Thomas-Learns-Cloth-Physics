// Wire.cpp
// source file for the Wire object class
// represents all of the points, springs, and triangles in the wireframe

#include "../inc/Wire.h"
#include <iostream>

Wire::Wire(int resolution_, int size) {
	// think of resolution of length of one side of square cloth
	resolution = resolution_;
	delta = (float)size / ((float)resolution_ * 1.0f);
	numTriangles = (resolution_ - 1) * (resolution_ - 1) * 2;
	numSprings = ((((2 * resolution_) - 1) + ((resolution_ - 1) * 2)) * (resolution_ - 1)) + (resolution_ - 1);
	// points should be resolution*resolution
	points = new Point*[resolution_];
	triangles = new Triangle*[numTriangles];
	springs = new Spring*[numSprings];

	// initialize the point rows
	for (int i = 0; i < resolution_; i++) {
		*(points + i) = new Point[resolution_];
	}

	// initialize the point values
	for (int i = 0; i < resolution_; i++) {
		for (int j = 0; j < resolution_; j++) {
			// create temporary particle
			Point* tmpPt = new Point();
			// set positions iteratively
			tmpPt->SetPosition((i - resolution_ / 2) * delta, 100, ((j - resolution / 2) * delta) + 100, i, j);
			// makes sure that this edge is anchored
			if (i == 0)
				tmpPt->isFixed = true;

			AddPoint(tmpPt, i, j);
		}
	}

	GenerateTriangles(resolution_);
	GenerateSprings();
}

Wire::~Wire() { }

void Wire::AddPoint(Point* point, int i, int j) {
	points[i][j] = *point;
}

void Wire::GenerateTriangles(int resolution) {
	// index to iterate through triangles
	int trianglesIndex = 0;

	for (int i = 0; i < resolution - 1; i++) {
		for (int j = 0; j < resolution - 1; j++) {
			// create a temp triangle to add to triangles
			Triangle* tmpTri = new Triangle();
			// Set value to triangle points
			tmpTri->SetTriangle(&points[i][j], &points[i][j + 1], &points[i + 1][j]);

			// add the index of adjacent triangles to each point
			// point 1
			int currentIndex = points[i][j].numOfAdjTriangles;
			points[i][j].adjTriangles[currentIndex] = trianglesIndex;
			points[i][j].numOfAdjTriangles++;

			// point 2
			currentIndex = points[i][j + 1].numOfAdjTriangles;
			points[i][j + 1].adjTriangles[currentIndex] = trianglesIndex;
			points[i][j + 1].numOfAdjTriangles++;

			// point 3
			currentIndex = points[i + 1][j].numOfAdjTriangles;
			points[i + 1][j].adjTriangles[currentIndex] = trianglesIndex;
			points[i + 1][j].numOfAdjTriangles++;

			// now add the tmpTri value into our triangles
			triangles[trianglesIndex] = tmpTri;
			trianglesIndex++;

			// repeat the process for the triangle that would complete
			// the rectangle
			tmpTri = new Triangle();
			// Set value to triangle points
			tmpTri->SetTriangle(&points[i][j + 1], &points[i + 1][j + 1], &points[i + 1][j]);

			// add the index of adjacent triangles to each point
			// point 2
			currentIndex = points[i][j + 1].numOfAdjTriangles;
			points[i][j + 1].adjTriangles[currentIndex] = trianglesIndex;
			points[i][j + 1].numOfAdjTriangles++;

			// point 4
			currentIndex = points[i + 1][j + 1].numOfAdjTriangles;
			points[i + 1][j + 1].adjTriangles[currentIndex] = trianglesIndex;
			points[i + 1][j + 1].numOfAdjTriangles++;

			// point 3
			currentIndex = points[i + 1][j].numOfAdjTriangles;
			points[i + 1][j].adjTriangles[currentIndex] = trianglesIndex;
			points[i + 1][j].numOfAdjTriangles++;

			// now add the tmpTri value into our triangles
			triangles[trianglesIndex] = tmpTri;
			trianglesIndex++;
		}
	}
}

void Wire::DrawPoints() {
	glPointSize(4);

	// make sure to disable texture so it's not drawn on the points
	glDisable(GL_TEXTURE_2D);

	// draw all points
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			CalculatePointNormal(i, j);
			points[i][j].DebugDraw();
		}
	}

	// re-enable texture
	glEnable(GL_TEXTURE_2D);
	glPointSize(1);
}

void Wire::DrawTriangles(bool showWireframe, bool flatShade) {
	// draw all triangles
	for (int i = 0; i < numTriangles; i++) {
		triangles[i]->DebugDraw(resolution, showWireframe, flatShade);
	}
}

void Wire::DrawSprings() {
	// draw all springs
	for (int i = 0; i < numSprings; i++) {
		springs[i]->DebugDraw();
	}
}

void Wire::Update(int sphereRadius, float gravForce, glm::vec3 gravDirection, float ks, float kd, float pointRadius, glm::vec3 objPos) {
	// update forces on each point
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			points[i][j].radius = pointRadius;
			// to make sure forces aren't additive
			points[i][j].ClearForces();
			points[i][j].AddForce(gravDirection.x * gravForce, gravDirection.y * gravForce, gravDirection.z * gravForce);
		}
	}

	// update the springs
	for (int i = 0; i < numSprings; i++) {
		springs[i]->Update(ks, kd);
	}

	// update point positions and check for collisions
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			points[i][j].Update(sphereRadius, objPos);
		}
	}
}

void Wire::GenerateSprings() {
	// index to iterate through springs
	int springIndex = 0;
	// find the hypotenuse of a triangle to determine diagonal distance
	float diagonalDelta = sqrt((delta * delta) + (delta * delta));

	// iterate through all points to create springs
	// check for all cases as to where springs will be created
	for (int i = 0; i < resolution; i++) {
		for (int j = 0; j < resolution; j++) {
			// if we are on the right-most border of the cloth and not on the bottom
			if (i == resolution - 1 && j < resolution - 1) {
				springs[springIndex] = new Spring(&points[i][j], &points[i][j + 1], delta);
				springIndex++;
			}
			else if (j == 0) {  // At the top of the cloth, we'll create two perpendicular springs
				springs[springIndex] = new Spring(&points[i][j], &points[i + 1][j], delta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j], &points[i][j + 1], delta);
				springIndex++;
			}
			else if (j < resolution - 1) { // We are between the top and bottom borders of the cloth
				springs[springIndex] = new Spring(&points[i][j], &points[i + 1][j - 1], diagonalDelta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j - 1], &points[i + 1][j], diagonalDelta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j], &points[i + 1][j], delta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j], &points[i][j + 1], delta);
				springIndex++;
			}
			else if (i == resolution - 1 && j == resolution - 1) { // at the end of the cloth, just move on
				continue;
			}
			else { // we're at the bottom of the cloth
				springs[springIndex] = new Spring(&points[i][j], &points[i + 1][j - 1], diagonalDelta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j], &points[i + 1][j], delta);
				springIndex++;

				springs[springIndex] = new Spring(&points[i][j - 1], &points[i + 1][j], diagonalDelta);
				springIndex++;
			}
		}
	}

	std::cout << "Springs: " << springIndex << ", expected springs is " << numSprings << std::endl;
}

void Wire::CalculatePointNormal(int c, int r) {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float length = 0.0f;

	for (int i = 0; i < points[c][r].numOfAdjTriangles; i++) {
		x += triangles[points[c][r].adjTriangles[i]]->normal->x;
		y += triangles[points[c][r].adjTriangles[i]]->normal->y;
		z += triangles[points[c][r].adjTriangles[i]]->normal->z;

		length += GetLength(*(triangles[points[c][r].adjTriangles[i]]->normal));
	}

	// update the normal values of the point
	points[c][r].normal->x = x / length;
	points[c][r].normal->y = y / length;
	points[c][r].normal->z = z / length;
}