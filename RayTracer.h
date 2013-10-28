#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Color.h"
#include "Ray.h"
#include "GeometricPrimitive.h"
#include "Light.h"

class RayTracer {	
public:
	static bool getIntersect(Ray& ray,float* thit,LocalGeo* localGeo, GeometricPrimitive* primitive, int numPrimitives, GeometricPrimitive* primitives[], int* primitiveIndex);
	static void trace(Ray& ray, int depth, Color* color, int maxdepth, int numPrimitives, GeometricPrimitive* primitives[], int numused, Light* lights[], float attenuation[]);
	static bool getIntersectP(Ray& ray, int numPrimitives, GeometricPrimitive* primitives[], int primitiveIndex);
};

#endif