#include <cmath>
#include <iostream>
#include <math.h>
#include "Shape.h"

Shape::Shape(Vertex* c, float r) {
	type = 0;
	center = c;
	radius = r;
}

Shape::Shape(Vertex* _a, Vertex* _b, Vertex* _c) {
	type = 1;
	a = _a;
	b = _b;
	c = _c;
}

bool Shape::intersectCircle(Ray& ray, float* thit, LocalGeo* local) {
	Vertex pos_center = Vertex::subtract(*(ray.pos), *center);
	float pos_center_dot = Vertex::dot(pos_center, pos_center);
	float b = 2 * Vertex::dot(*(ray.dir), pos_center);
	float a = Vertex::dot(*(ray.dir), *(ray.dir));
	float c = pos_center_dot - radius * radius;
	float t;

	float root = b * b - 4 * a * c;
	if (root <= 0.f) {
		return false;
	}

	float t1 = (-b + sqrt(root))/(2.f * a);
	float t2 = (-b - sqrt(root))/(2.f * a);
	
	float small_error = 0.1f;

	if (t1 < 0.f && t2 < 0.f) return false;

	if (std::abs(t1) < small_error && std::abs(t2) < small_error) {
		return false;
	}
	if (std::abs(t1) < small_error) {
		return false;
	}
	if (std::abs(t2) < small_error) {
		return false;
	}

	if (t1 < ray.t_min || t1 > ray.t_max) {
		if (t2 < ray.t_min || t2 > ray.t_max) {
			return false;
		} else {
			t = t2;
		}
	}
	else if (t2 < ray.t_min || t2 > ray.t_max) {
		t = t1;
	}

	else if (t1 < t2) t = t1;
	else t = t2;
	Vertex t_time_raydir = Vertex::multiply(t, *(ray.dir));
	Vertex pos = Vertex::add(*(ray.pos), t_time_raydir);
	Vertex nor = Vertex::subtract(pos, *center);
	nor = Vertex::normalize(nor);

	Vertex* posptr = new Vertex::Vertex(pos.x, pos.y, pos.z);
	Vertex* norptr = new Vertex::Vertex(nor.x, nor.y, nor.z);
	LocalGeo* l = new LocalGeo::LocalGeo(posptr, norptr);
	*local = *l;
	*thit = t;
	return true;
}

bool Shape::intersectTriangle(Ray& ray, float* thit, LocalGeo* local) {
	Vertex u = Vertex::subtract(*c, *a);
	Vertex v = Vertex::subtract(*b, *a);
	Vertex normal = Vertex::cross(v, u);
	normal = Vertex::normalize(normal);
	float a_n = Vertex::dot(*a, normal);
	float p_n = Vertex::dot(*ray.pos, normal);
	float d_n = Vertex::dot(*ray.dir, normal);
	if (d_n == 0.f) {
		return false;
	}
	*thit = (a_n - p_n)/d_n;
	if (*thit < ray.t_min || *thit > ray.t_max) {
		return false;
	}

	Vertex dir_thit = Vertex::multiply(*thit, *ray.dir);
	Vertex dir_thit_plus_pos = Vertex::add(dir_thit, *ray.pos);

	float uu = Vertex::dot(u,u);
    float uv = Vertex::dot(u,v);
    float vv = Vertex::dot(v,v);
    Vertex w = Vertex::subtract(dir_thit_plus_pos, *a);
    float wu = Vertex::dot(w,u);
    float wv = Vertex::dot(w,v);
    float D = uv * uv - uu * vv;

    // get and test parametric coords
    float s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)
        return false;
    float t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)
        return false;

	Vertex* pos = new Vertex::Vertex(dir_thit_plus_pos.x, dir_thit_plus_pos.y, dir_thit_plus_pos.z);
	Vertex* n = new Vertex::Vertex(normal.x, normal.y, normal.z);
	LocalGeo* l = new LocalGeo(pos, n);
	*local = *l;
	return true;
}

bool Shape::intersect(Ray& ray, float* thit, LocalGeo* local) {
	if (type == 0) return intersectCircle(ray, thit, local);
	else if (type == 1) return intersectTriangle(ray, thit, local);
	else return false;
}

bool Shape::intersectP(Ray& ray) {
	float thit;
	LocalGeo local;
	bool ret = intersect(ray, &thit, &local);
	if (ret) {
		// printf("THIT: %f\n", thit);
		// Vertex::print(*local.pos);
		// Vertex::print(*local.normal);
		// Vertex::print(*ray.pos);
		// printf("NEW DIR:"); Vertex::print(*ray.dir);
	}

	return ret;
}