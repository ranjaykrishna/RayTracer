#include <math.h>
#include <iostream>
#include "Light.h"

Light::Light(int t, Vertex* v, Color* c) {
	color = c;
	if (t == 0.f) dir = v;
	else if (t == 1.f) pos = v;
	type = t;
}

void Light::generateLightRay(LocalGeo& local, Ray* ray, Color* c) {
	Vertex* d;
	float t_max = 1000.f;
	if (type == 0) {
		d = new Vertex::Vertex(-dir->x, -dir->y, -dir->z);
	} else {		
		Vertex d_temp = Vertex::subtract(*pos, *local.pos);
		t_max = sqrt(pow(d_temp.x, 2) + pow(d_temp.y, 2) + pow(d_temp.z, 2));
		d_temp = Vertex::normalize(d_temp);
		d = new Vertex::Vertex(d_temp.x, d_temp.y, d_temp.z);
	}
	float ratio = 0.0f;
	Vertex* p = new Vertex::Vertex(local.pos->x + ratio*d->x, local.pos->y + ratio*d->y, local.pos->z + ratio*d->z);
	Ray* r = new Ray::Ray(p, d, 0.1f, t_max);
	*ray = *r;
	*c = *color;
}