#ifndef BRDF_H
#define BRDF_H

#include "Color.h"

class BRDF {
public:
	Color* kd;
	Color* ks;
	Color* ka;
	Color* ke;
	float shininess;
	BRDF(Color* diffusion, Color* specular, Color* ambient, Color* emission, float s);
	BRDF();
};

#endif