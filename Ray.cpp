#include <iostream>
#include "Ray.h"

Ray::Ray() {

}

Ray::Ray(Vertex* p, Vertex* d, float min, float max) {
	pos = p;
	dir = d;
	t_min = min;
	t_max = max;
}

void Ray::print(Ray& ray) {
	printf("POS: %f, %f, %f. DIR: %f, %f, %f.\n", 
		ray.pos->x, ray.pos->y, ray.pos->z, 
		ray.dir->x, ray.dir->y, ray.dir->z);
}