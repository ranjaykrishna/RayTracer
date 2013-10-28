#ifndef RAY_H
#define RAY_H

#include "Vertex.h"

class Ray {
	public:
		Vertex* pos;
		Vertex* dir;
		float t_min;
		float t_max;
		Ray(Vertex* p, Vertex* d, float min, float max);
		Ray();
		static void print(Ray& ray);
};

#endif