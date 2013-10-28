#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H

#include "Shape.h"
#include "BRDF.h"
#include "LocalGeo.h"
#include "Ray.h"
#include "Matrix4.h"

class GeometricPrimitive {
public:
	Shape* shape;
	BRDF* brdf;
	Matrix4* worldToObj;
	Matrix4* objToWorld;
	GeometricPrimitive(Shape* s, BRDF* b, Matrix4* oTW, Matrix4* wTO);	
	GeometricPrimitive();	
	bool intersect(Ray& ray, float* thit, LocalGeo* l, GeometricPrimitive* s);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif