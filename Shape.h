#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"
#include "LocalGeo.h"

class Shape {
public:
	Vertex* center;
	float radius;
	Vertex* a;
	Vertex* b;
	Vertex* c;

	// 0 for circle
	// 1 for triangle
	int type;

	Shape(Vertex* c, float r);
	Shape(Vertex* _a, Vertex* _b, Vertex* _c);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray); 
private:
	bool intersectCircle(Ray& ray, float* thit, LocalGeo* local);
	bool intersectTriangle(Ray& ray, float* thit, LocalGeo* local);
};

#endif