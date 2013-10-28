#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h"
#include "Vertex.h"
#include "LocalGeo.h"
#include "Ray.h"

class Light {
public:
	// 0 for directional
	// 1 for point
	int type;
	Color* color;
	Vertex* pos;
	Vertex* dir;
	Light(int t, Vertex* v, Color* c);
	void generateLightRay(LocalGeo& local, Ray* ray, Color* color);
};

#endif