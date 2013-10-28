#ifndef CAMERA_H
#define CAMERA_H

#include "Vertex.h"
#include "Sample.h"
#include "Ray.h"

class Camera {
public:
	Vertex* eye;
	Vertex* center;
	Vertex* up;
	Vertex* u_vec;
	Vertex* v_vec;
	Vertex* w_vec;
	float fovy;
	Camera(Vertex* _eye, Vertex* _center, Vertex* _up, float _fovy, Vertex* uu, Vertex* vv, Vertex* ww);
	Camera();
	void generateRay(Sample& sample, Ray* ray, int w, int h, float fovx, float fovy);
};

#endif 