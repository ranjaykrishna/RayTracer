#include <iostream>
#include <math.h>
#include "Camera.h"

Camera::Camera(Vertex* _eye, Vertex* _center, Vertex* _up, float _fovy, Vertex* uu, Vertex* vv, Vertex* ww) {
	u_vec = uu;
	v_vec = vv;
	w_vec = ww;
	eye = _eye;
	center = _center;
	up = _up;
	fovy = _fovy;
}

Camera::Camera() {

}

void Camera::generateRay(Sample& sample, Ray* ray, int width, int height, float fovx, float fovy) {
	float w_float = (float) width;
	float h_float = (float) height;
	const float pi = 3.14159265f;
	float fovy_rad = fovy * pi/180.f;
	float fovx_rad = fovx * pi/180.f;

	float alpha = tan(fovx_rad/2.f)*(((float)sample.x) + 0.5f - w_float/2.f)/(w_float/2.f);
	float beta = tan(fovy_rad/2.f)*(((float)sample.y) + 0.5f - h_float/2.f)/(h_float/2.f);
	Vertex alpha_u = Vertex::multiply(alpha, *u_vec);
	Vertex beta_v = Vertex::multiply(beta, *v_vec);
	Vertex alpha_u_plus_beta_v = Vertex::add(alpha_u, beta_v);
	Vertex total = Vertex::subtract(alpha_u_plus_beta_v, *w_vec);

	float tmin = sqrt(pow(total.x, 2) + pow(total.y, 2) + pow(total.z, 2));
	total = Vertex::normalize(total);
	Vertex* dir = new Vertex::Vertex(total.x, total.y, total.z);
	Vertex* pos = new Vertex::Vertex(eye->x, eye->y, eye->z);
	Ray* r = new Ray::Ray(pos, dir, 0.1f, 100.f);
	*ray = *r;
}