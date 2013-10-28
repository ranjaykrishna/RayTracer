#include "BRDF.h"

BRDF::BRDF(Color* diffusion, Color* specular, Color* ambient, Color* emission, float s) {
	kd = diffusion;
	ks = specular;
	ka = ambient;
	ke = emission;
	shininess = s;
}

BRDF::BRDF() {
	
}